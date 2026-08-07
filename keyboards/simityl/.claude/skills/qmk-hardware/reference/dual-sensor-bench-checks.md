# Dual-sensor bench checks — multimeter procedure

Settles the physical open items from [`dual-sensor-wiring-feasibility.md`](dual-sensor-wiring-feasibility.md)
before anything gets soldered. Written to be used at the bench, one box at a time.

**Tools:** multimeter (continuity, resistance, DC volts). A logic analyzer is *not* needed for
any of this — see the last section for what it is needed for.

> **Note on the feasibility report's open item 3.** It asks for "logic-high level on MISO during
> a read." **A DMM cannot do that** — a toggling SPI line reads as a meaningless average. The
> float test in Phase 2 answers the same question (does each sensor release the bus?) and is
> decisive. Don't waste time on item 3 as written.

---

## Phase 1 — Unpowered breakout checks

**Power off, cable out.** Resistance on a live board reads garbage and can damage the meter.

Do both boards and **record side by side** — the comparison matters as much as the absolute
values. The boards are pre-wired and were *not* the units verified against the jkicklighter
design, so a mismatch between them is the most likely real finding.

| # | probe | expect | board A | board B | failure means |
|---|---|---|---|---|---|
| 1 | SS ↔ GD | open | | | CS strapped — that board **cannot** be multi-dropped |
| 2 | SS ↔ VI | open | | | same |
| 3 | VI ↔ GD | open (no short) | | | supply short; stop, do not power |
| 4 | MI ↔ VI | ≥ tens of kΩ | | | few kΩ = pull-up fighting the other sensor's high-Z |
| 5 | MI ↔ GD | ≥ tens of kΩ | | | few kΩ = pull-down, same problem |

- [ ] Board A recorded
- [ ] Board B recorded
- [ ] **Readings match between boards** — a meaningful difference means different designs or
      revisions, and every pin-level detail in the feasibility report has to be re-checked for
      the odd one out.

Low readings on 4/5 are only fatal if they differ between boards *or* are low enough to hold the
bus; identical high-kΩ readings on both are the chip's internal ESD structures and are fine.

---

## Phase 2 — The float test (decisive)

**This is the test that proves multi-drop works.** One board at a time.

1. Power a single board.
2. Hold its **SS high** — tie to 3V3 through a resistor, or leave it pulled up.
3. Meter on **MI → GND, DC volts**.

| reading | verdict |
|---|---|
| drifting, unstable, wandering | **PASS** — line is floating, sensor is releasing the bus |
| rock-steady at 0 V or 3.3 V | **FAIL** — board drives MISO with CS high; cannot share a bus |

- [ ] Board A floats with CS high
- [ ] Board B floats with CS high

A DMM's ~10 MΩ input makes a genuinely floating line drift and wander. Steady-at-a-rail is the
signature of something actively driving. Both boards must float or the shared-bus plan is dead
and each sensor needs its own SPI peripheral.

---

## Phase 3 — Splinky GP12 (functional, not continuity)

Do **not** try to buzz the pad through to the RP2040 — probing a QFN pin is a bad time and a
failed continuity test would tell you nothing useful.

Test it functionally. Three lines, rebuilt twice:

```c
void keyboard_post_init_user(void) {
    gpio_set_pin_output(GP12);
    gpio_write_pin_high(GP12);   // rebuild with _low and re-measure
}
```

Meter on the GP12 pad, DC volts:

- [ ] high build reads ~3.3 V
- [ ] low build reads ~0 V

That proves pad-to-MCU connectivity **and** that nothing else is fighting the pin — which plain
continuity could not show.

Then check for solder bridges on that bottom edge, the realistic failure mode:

- [ ] GP12 ↔ GP13 open
- [ ] GP12 ↔ GP14 open
- [ ] GP12 ↔ GND open

Also worth confirming physically:

- [ ] the GP12 pad is actually reachable with the controller mounted in the simityl case

---

## Phase 4 — After wiring both sensors

- [ ] **VI on board A and board B read the same voltage** (expect 3.3 V). The jkicklighter boards
      auto-detect 3.3 V/5 V, so feeding them from different rails gives the two sensors different
      VDDIO and therefore different MISO high levels on a shared bus. This produces intermittent
      garbage rather than clean failure, which is the worst kind. Feed both from the same 3V3 rail.
- [ ] Ground: each sensor's ground lead paired with its own signal bundle, starred at the
      controller.
- [ ] Neither SS tied to the other — only one CS may be low at a time.

---

## What the meter cannot do

Once both sensors are live on the bus, verifying the **handoff** — that sensor 1 has released
MISO before sensor 2 drives it — means seeing the transitions. The datasheet allows 500 ns
(`tNCS-MISO`) for that release, far too fast for a DMM.

That is a logic analyzer's job. A cheap 8-channel clone (~$10, works with sigrok/PulseView) turns
dual-sensor bring-up from guesswork into a picture. Worth having *before* soldering rather than
after, since the failure modes here are intermittent by nature.
