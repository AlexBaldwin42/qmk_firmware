# Dual PMW3389 wiring feasibility — Splinky v3 and 0xCB Helios

Hardware feasibility investigation (2026-08-06): can two PMW3389 sensor breakout boards
hang off one controller on simityl? Firmware feasibility was already established
(`drivers/sensors/pmw33xx_common.c` indexes `cs_pins[sensor]`); this doc covers the
physical/electrical side only. Every claim is tagged **VERIFIED** (read from a datasheet,
schematic, or config file — source cited) or **INFERRED**.

## Verdicts

| Controller | Verdict | Second CS | 3V3 regulator |
|---|---|---|---|
| **Splinky v3** | **Possible, no caveats** | **GP12** (GP13/GP14 equal) | Torex XC6210B332MR-G, ~700 mA class |
| **0xCB Helios** | **Possible, more headroom** | **GP12** (parity with Splinky) | TI TLV75533PDQNR, 500 mA (behind 500 mA fuse) |

"bastardkb Helios" = the **0xCB Helios** by Conor Burns; BastardKB lists it as a
BKB-standard-pinout compatible controller
([docs.bastardkb.com/hw/rp2040-community.html](https://docs.bastardkb.com/hw/rp2040-community.html)).
It has **no dedicated trackball header** — it is a pro-micro drop-in; on BastardKB boards
the trackball connector lives on the keyboard shield PCB, not the controller.

## Splinky v3 — second CS pin

**GP12, GP13, GP14 are free, broken out (bottom edge), and plain GPIO.** VERIFIED:

- Broken out per the Splinky pad map (`~/source/broc/make-it-blink/docs/HARDWARE.md`,
  corroborated by the Splinky repo README: "GPIO 12-16: extra pins broken out on the lower
  edge", GP17 user LED, GP19 VBUS detect —
  [github.com/Bastardkb/Splinky](https://github.com/Bastardkb/Splinky)).
- Unclaimed: grep of `keyboards/simityl/config.h` + `keyboard.json` finds GP12–14 nowhere
  live; GP13 appears only in a commented-out Splinky-**v2** handedness line
  (`config.h:28`). The decoy-encoder trick uses GP15/GP16 only (`config.h:46-47`).
- No alternate-function conflict: RP2040 GPIO has **no fixed alternate functions** — every
  pin's function is mux-selected (FUNCSEL), with SIO (plain GPIO) available on all 30 pins
  (RP2040 datasheet §2.19.2 GPIO function table,
  [datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)).
  QMK drives CS as a plain software GPIO per transaction:
  `drivers/sensors/pmw33xx_common.c:51` — `spi_start(cs_pins[sensor], ...)`; the
  `PMW33XX_CS_PINS` array lives at `pmw33xx_common.h:71-95`.
- Regulator: **XC6210B332MR-G** — VERIFIED from the Splinky schematic
  (`pcb/0xB2.kicad_sch`, symbol U3's Value field overrides the AP2127K library symbol).
  Torex XC6210 series is a ~700 mA LDO.

Keep GP2/GP3 (I²C) and GP27/GP29 (two of the four ADC pins) in reserve.

## 0xCB Helios — pad map and second CS pin

VERIFIED from the **rev1.0 schematic** (`rev1.0/helios.pdf` in
[github.com/0xCB-dev/0xCB-Helios](https://github.com/0xCB-dev/0xCB-Helios), read directly):

- **Broken out on J2**: GP0–GP16 (GP0–9 left edge, **GP10/GP11 extra top pins**, GP12–16
  bottom edge), GP20–23 (SPI corner, same positions as Splinky: 20=SDI, 21=CS silk,
  22=SCK, 23=SDO), GP26–29 (ADC), plus a **RGB_5V pad = GP25 through a 74LVC1T45 level
  shifter** (output-only, 5 V logic — ideal WS2812 data pin).
- **Not broken out**: GP17 (user LED D2 — matches simityl's
  `RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17`, which therefore works unchanged), GP18
  (NC), GP19 (VBUS_DETECT divider, 5k1/10k), GP24 (NC), GP25 (only via shifter).
- **Power**: TLV75533PDQNR 3.3 V 500 mA LDO, behind a 500 mA fuse (F1) and PMEG2010BELD
  schottky on VBUS.
- simityl's existing pin config drops in unchanged. Silk "CS" on GP21 is just a label;
  simityl's use of GP21 as a matrix column engages no alternate function.
- **Spares after a simityl-equivalent build** (matrix 9 + serial + WS2812 + SPI 3 +
  2× CS + handedness): GP2, GP3, GP10, GP11, GP13, GP14, GP27, GP29 = **8 spares**
  (9 if WS2812 moves to the RGB_5V pad, freeing GP0).

Recommend **GP12** here too, deliberately — the same firmware config then works on either
controller with zero changes.

## Electrical multi-drop — two PMW3389 on one bus

Source: **PMW3389DM product datasheet v1.01, 03 Jan 2019, doc 11020AENW**
([gzhls.at mirror](https://gzhls.at/blob/ldb/a/0/f/6/3971c1b0ff98ce53e924c6ce3ffb16905172.pdf)).

- **MISO tri-state — VERIFIED.** Table 5 "AC Electrical Specifications" (pp. 16–17):
  **tNCS-MISO = 500 ns max, "From NCS rising edge to MISO high-Z state."** Two sensors can
  share MISO as long as only one NCS is low at a time; QMK's per-transaction
  spi_start/spi_stop gap is orders of magnitude longer than 500 ns. The companion prose
  "inputs are ignored while NCS is high" appears in the family's long-form datasheets but
  not in the 20-page product datasheet verified here — that phrasing is **INFERRED**
  (strongly, from tNCS-SCLK plus the tri-state spec).
- **Burst mode is CS-friendly — VERIFIED.** tBEXIT = 500 ns min "NCS inactive time after
  motion burst before next SPI usage" (Table 5): raising NCS to end each burst is the
  *designed* usage — exactly what QMK does.
- **Bus speed — VERIFIED.** fSCLK max **2.0 MHz**, 50 % duty (Table 4, p. 15). Flying
  leads are fine at 2 MHz; the binding constraint is the CL = 100 pF load spec on MISO —
  keep the combined MISO run well under ~0.5 m.
- **Supply — VERIFIED.** Chip VDD 1.8–2.1 V (core), VDDIO 1.8–3.6 V; 3.3 V RP2040 logic is
  directly legal, the breakout's onboard regulator handles the core rail.
- **The RMK docs claim** these sensors "can not share an SPI bus with each other or any
  other SPI device" ([rmk.rs](https://rmk.rs/main/docs/configuration/input_device/pmw33xx))
  — stated with no justification, and contradicted by the tri-state spec and by QMK's
  shipping driver architecture. Treat as an RMK firmware limitation, not silicon
  (**INFERRED** as to their motivation).

### Breakout boards

The jkicklighter Tindie PMW3389 breakout
([tindie.com/products/jkicklighter/pmw3389-motion-sensor](https://www.tindie.com/products/jkicklighter/pmw3389-motion-sensor/))
— VERIFIED from the product page:

- 8-pin 0.1" through-hole header: MI / MO / SC / **SS (separate chip select)** / MT / RS /
  VI / GD.
- Onboard regulator, "3.3 V or 5 V compatible (automatic detection)". No level shifter.
- 28 × 21 × 9.25 mm; 24 mm hole spacing, 2-56 screws.
- No mention of bus pull-ups; the datasheet reference schematic (Fig. 10, p. 14) has none
  on the SPI lines — paralleling two boards should be conflict-free, but this is
  **INFERRED until measured on the actual boards on hand** (they are pre-wired; confirm
  they are this design).

### Power budget

- IDDRUN = **21.0 mA typ per sensor** including LED at 1 ms polling; Rest1 = 3.1 mA
  (Table 6 "DC Electrical Specifications", p. 18 — VERIFIED). Two sensors ≈ 45–60 mA
  worst-case steady: trivial against either regulator, even alongside RP2040 + matrix +
  split link (48× WS2812 draw from 5 V, not 3V3).
- **Inrush**: IDDT up to **70 mA per sensor** during the VDD ramp (150 µs–20 ms window,
  Table 5 — VERIFIED). ~140 mA transient for two boards at plug-in; brief and within
  budget, but don't power them through a skinny trace.
- **Feed both breakouts from the same rail** (recommend 3V3) so both sensors' VDDIO — and
  thus MISO logic-high — match. Mixed 5 V/3V3 supply with auto-detect regulators risks two
  different logic highs on the shared bus.

## Bring-up gotchas

1. Only one CS low at a time — never tie the two SS pins together (they would fight on
   MISO, and every register write would hit both chips).
2. Pair each sensor's ground lead with its signal bundle back to the controller; star
   both bundles at the controller.
3. QMK stock wrappers only poll sensor 0 — a custom `pointing_device_driver_t` is needed
   for sensor 1 (see SKILL.md, "Catch 1").
4. Keep the MISO stubs short; the 100 pF CL spec is the real length limit, not the 2 MHz
   clock.

## Open items — settle with a multimeter on the physical hardware

1. Continuity from the Splinky's GP12 pad to the RP2040 on the **assembled** board, and
   whether that bottom-edge pad is reachable inside the simityl case.
2. On each breakout: resistance MI↔VI and MI↔GND (detect hidden pull resistors), and
   confirm SS is not strapped to GND/VI by a trace. Confirm both boards are the same
   design/revision — the jkicklighter design was verified, not necessarily these units.
3. Logic-high level on MISO during a read from each sensor (should match at ~3.3 V) once
   both share the bus.
4. If buying a Helios: confirm the physical unit is **rev1.0** — the pad map above is the
   rev1.0 schematic; check newer revisions against it before soldering.

## Sources

- PMW3389DM datasheet v1.01 (03 Jan 2019, 11020AENW) —
  [gzhls.at mirror](https://gzhls.at/blob/ldb/a/0/f/6/3971c1b0ff98ce53e924c6ce3ffb16905172.pdf)
- 0xCB Helios rev1.0 schematic + README —
  [github.com/0xCB-dev/0xCB-Helios](https://github.com/0xCB-dev/0xCB-Helios)
- Splinky schematic `pcb/0xB2.kicad_sch` —
  [github.com/Bastardkb/Splinky](https://github.com/Bastardkb/Splinky)
- BastardKB RP2040 controllers —
  [docs.bastardkb.com/hw/rp2040-community.html](https://docs.bastardkb.com/hw/rp2040-community.html)
- RP2040 datasheet §2.19.2 —
  [datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
- jkicklighter PMW3389 breakout —
  [Tindie product page](https://www.tindie.com/products/jkicklighter/pmw3389-motion-sensor/)
- RMK PMW33xx docs (the contradicted bus-sharing claim) —
  [rmk.rs/main/docs/configuration/input_device/pmw33xx](https://rmk.rs/main/docs/configuration/input_device/pmw33xx)
- Local: `keyboards/simityl/config.h`, `keyboards/simityl/keyboard.json`,
  `drivers/sensors/pmw33xx_common.{c,h}`,
  `~/source/broc/make-it-blink/docs/HARDWARE.md` (Splinky pad map)
