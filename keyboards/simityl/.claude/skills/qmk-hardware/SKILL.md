---
name: qmk-hardware
description: simityl hardware — Splinky v3 pin budget, the encoder/SPI collision, PMW33xx trackball wiring, and the dual-sensor yaw-scroll design
---

# simityl hardware

RP2040 on a **Splinky v3**, split, PMW3389 trackball on the right half, encoder on the
left. You are in the keyboard definition directory, where the pin config actually lives
(`config.h`).

For fleet-wide hardware notes invoke the global `/qmk-hardware`. For build/flash, `/qmk`.

## Pin budget

Claimed in `config.h` and `keyboard.json`:

| Function | Pins |
|---|---|
| Matrix cols | GP28, GP21, GP6, GP7, GP8 |
| Matrix rows | GP26, GP5, GP4, GP9 |
| Split serial | GP1 |
| WS2812 | GP0 |
| SPI SCK / MISO / MOSI | GP22 / GP20 / GP23 |
| Trackball CS | GP16 |
| Split handedness | GP15 (`SPLIT_HAND_PIN_LOW_IS_LEFT`) |
| Bootloader activity LED | GP17 |

### Free pins — resolved against the real Splinky v3.x pad map

The authoritative pad map lives in a *different* project:
`~/source/broc/make-it-blink/docs/HARDWARE.md`. On the Splinky, **silk `Dn` = `GPIOn`**
exactly, and the extra pads are labelled by GPIO number.

| | |
|---|---|
| Broken out | GP0–9 (left edge), GP12–16 (bottom), GP20–23 (right, SPI), GP26–29 (right, ADC) |
| Reserved | **GP17** onboard user LED, **GP19** VBUS sense |
| Claimed by simityl | GP0,1,4,5,6,7,8,9,15,16,17,20,21,22,23,26,28 |
| **Free and broken out** | **GP2, GP3, GP12, GP13, GP14, GP27, GP29** |

**For a second sensor CS pin, use GP12, GP13, or GP14** — bottom edge, plain GPIO, no
alternate function. GP2/GP3 double as I²C; GP27/GP29 are among the only ADC-capable pins
and are worth reserving.

> GP10, GP11 and GP18 are **not broken out** on the Splinky v3.x — they are unclaimed in
> firmware but physically unreachable. Do not offer them as candidates.
> GP13 appears in simityl's `config.h` only inside a commented-out Splinky **v2** handedness
> line; that is not a claim, and GP13 is free.
> All Splinky GPIOs are PWM-capable. Verify against the assembled board before soldering —
> the pad map is per-controller, not per-build.

## The encoder/SPI collision

GP22 and GP23 are **both** SPI SCK/MOSI and the left half's encoder pads. The right half
declares decoy encoder pads so the encoder driver doesn't steal the SPI pins:

```c
#define ENCODERS_PAD_A_RIGHT { GP15 }   // handedness pin, doubling as a decoy
#define ENCODERS_PAD_B_RIGHT { GP16 }   // real trackball CS, doubling as a decoy
```

This works but is fragile. Any new pin assignment must avoid colliding with it, and GP16's
double duty is worth remembering when debugging either subsystem. Handedness comes from
`SPLIT_HAND_PIN`, which needs resistors installed on the adapter PCB.

## Trackball

Most units carry a **PMW3389**; one has a **PMW3360**. Same
`drivers/sensors/pmw33xx_common.c` either way — only `POINTING_DEVICE_DRIVER` differs, and
it's set per-unit in the *userspace keymap's* `rules.mk`, not here. Wrong driver = failed
signature check = silently dead pointer.

`POINTING_DEVICE_TASK_THROTTLE_MS` is 1, so there's a ~1000 µs budget per poll.

### Multiple sensors on one MCU

Natively supported — SPI is a bus, and `spi_start(pin_t slavePin, ...)` takes chip select
per transaction. The driver already indexes `cs_pins[sensor]`.

- **SCK, MOSI, MISO shared.** Only CS is per-sensor — one extra GPIO each.
- No contention: the PMW33xx tri-states MISO whenever its CS is high.
- MOTION interrupt pin not needed. ~15–20 mA per sensor. 2 MHz bus tolerates flying leads.
- **Both sensors must be the same part** — `POINTING_DEVICE_DRIVER` is singular, and the
  signature check and CPI limits compile per type.

```c
#define PMW33XX_CS_PINS { GP16, GP<new> }   // count via ARRAY_SIZE
```

Per-sensor API: `pmw33xx_init(n)`, `pmw33xx_read_burst(n)`, `pmw33xx_set_cpi(n, cpi)`,
`pmw33xx_set_cpi_all_sensors(cpi)`.

**Catch 1:** stock wrappers only touch sensor 0 — `pmw33xx_init_wrapper` calls
`pmw33xx_init(0)` and `pmw33xx_get_report` bursts sensor 0 only. Sensor 1 is addressable
but ignored until you supply `POINTING_DEVICE_DRIVER = custom` with your own
`pointing_device_driver_t`.

**Catch 2 — `ROTATIONAL_TRANSFORM_ANGLE` is global, not per-sensor.** `pmw33xx_init` writes
it inside a per-sensor loop, but from one `#define`:

```c
pmw33xx_write(sensor, REG_Angle_Tune, CONSTRAIN(ROTATIONAL_TRANSFORM_ANGLE, -127, 127));
```

Every sensor gets the *same* angle. Two sensors mounted at different azimuths need
*different* corrections, so this define cannot express the geometry. Either write
`REG_Angle_Tune` per sensor manually after init, or leave it at 0 and fold the rotation
into the fusion matrix — the latter is cleaner, since the matrix already encodes each
sensor's orientation.

### The mounting angle is a property of the body, not the PCB

charybdis sets `ROTATIONAL_TRANSFORM_ANGLE -25` — but that number describes how the sensor
sits **in the charybdis shell**. simityl's trackball is in a different orientation in a
different body, so **-25 is not transferable**. Do not copy it across, and do not treat
simityl's absence of the define as a missing correction.

simityl currently corrects with `POINTING_DEVICE_INVERT_X` / `INVERT_Y`, which can only
express 90° multiples. If the true mounting rotation isn't a multiple of 90°, inverts
cannot remove the residual skew — the symptom is a pointer that tracks correctly on the
cardinal directions but drifts off-axis on diagonals.

### Measuring the actual angle

Don't assume it — measure it, per sensor:

1. Print raw `delta_x` / `delta_y` from `pmw33xx_read_burst` with the transform at 0 and
   both inverts off.
2. Roll the ball along the user's straight-forward axis.
3. The angle is `atan2(delta_x, delta_y)` over the accumulated deltas. Average several
   rolls — single strokes are noisy.

For a dual-sensor build this is mandatory, not optional: each sensor's angle is an
independent input to the fusion matrix, and a wrong assumed angle poisons both the cursor
and the scroll channel. Measure both sensors separately with the same procedure.

**Catch 3 — mouse report width.** `#define MOUSE_EXTENDED_REPORT` widens HID mouse X/Y from
±127 to ±32767. The charybdis readme notes these sensors can genuinely saturate ±127, so
this is worth enabling for multi-sensor work. It does not remove the need to fuse on raw
int16 deltas first, but it stops the *fused* result from being clipped on fast motion.
Requires reflashing both halves.

## Dual-sensor yaw scroll (designed, not built)

Spin the ball about its vertical axis to scroll, modelessly, alongside cursor motion.

### Parts on hand — sourcing is NOT the blocker

- **2× PMW3389 on separate sensor boards, already wired.** Two independent boards, so each
  sensor is freely positionable in (θ, φ) and `ball_socket.scad` applies as written.
- **4× PMW3360** spare.
- **Build target: the PMW3389 pair.**

Consequences:

- **Bench testing is possible today**, before any shell exists. Flying leads are fine at the
  2 MHz bus speed. The firmware — not the hardware — is the critical path.
- 3389 needs **no SROM upload** (`pmw3360.h` defines `PMW33XX_FIRMWARE_LENGTH 4094`, the
  3389 defines none), so init is fast and no blob lands in flash. A 3360 build would add
  ~60 ms per sensor at boot.
- CPI ranges differ: **3389 = 50–16000 step 50**, 3360 = 100–12000 step 100.
- **Never match the two sensors via the CPI register.** One 3389 step at 800 CPI is 6.25 %
  — coarser than the ~5 % mismatch being corrected. Do gain matching in the fusion matrix,
  where Q16 constants give effectively arbitrary precision and empirical calibration handles
  it automatically. (Moot in the asymmetric layout, where CPI mismatch can't reach scroll.)
- All-3389 or all-3360, **never mixed** — `POINTING_DEVICE_DRIVER` is singular, and the
  signature check and CPI limits compile per sensor type.

### There is a working single-sensor 55 mm trackball ALREADY

Fusion design **`Top55mmTrackball v2`** (bodies: Base, TrackBall, Bearing1/2/3, Back) is in
daily use. It is the reference for this project — prefer its measured values over datasheet
figures.

- **Ball is exactly 55.0 mm.** Fusion reports the TrackBall body area as 9503.318 mm²;
  4π(27.5)² = 9503.3 mm². Not nominal — exact.
- **Sensor standoff: 2.96 mm from the PCB face to the ball surface. PROVEN, in use.**
  Do **not** "correct" this toward the 2.4 mm datasheet number — that spec is
  lens-bottom-to-surface and requires a lens-protrusion assumption this working part already
  resolves. The lens protrudes into the 2.96 mm gap.
- **3 bearings**, matching the SlimBlade's 3-point support approach.
- The document opens **read-only**; needs "Make Editable" before changes.

**Therefore the safest way to add sensor 2 is to duplicate the existing sensor pocket
feature and re-place the copy at the equatorial position.** Proven geometry, no new
dimensions to get wrong, and it appends to the end of the timeline so the under-constrained
upstream sketches never rebuild. See [[fusion360-is-the-cad-tool]].

### Existing holders — already in the right band

Alex has **2 spare 3D-printed ball holders**, each covering ~**40 % of the ball**. For a
spherical cap, surface-area fraction and height fraction are both `(1 − cos θ)/2`, so:

**40 % coverage → rim at θ = 78.5°, cap height 22.0 mm on the 55 mm ball.**

That sits inside the recommended 75–85° sensor band. **A sensor at the existing rim gives
gain_z 1.041 and 1.02 % CPI leak — near-recommended performance with no turret required.**
Check the existing part before printing anything; `ball_socket.scad`'s turret exists for
sensors *above* the rim and may be unnecessary here.

Cost of cutting the holder down for hand clearance:

| coverage | rim θ | cap height | gain_z | CPI leak |
|---|---|---|---|---|
| 50 % | 90.0° | 27.5 mm | 1.000 | 0.00 % |
| **40 % (current)** | **78.5°** | **22.0 mm** | **1.041** | **1.02 %** |
| 35 % | 72.5° | 19.2 mm | 1.094 | 1.57 % |
| 30 % | 66.4° | 16.5 mm | 1.175 | 2.18 % |
| 25 % | 60.0° | 13.8 mm | 1.291 | 2.89 % |
| 20 % | 53.1° | 11.0 mm | 1.458 | 3.75 % |

**Cut asymmetrically.** The asymmetric sensor layout needs only *one* sensor high up, on the
far side; the hand approaches from the near side. Cut the near side and flanks for clearance
and leave the far side at full height to carry the equatorial sensor — full hand access and
full scroll performance, no trade. Subtractive work on a spare, with the second holder kept
intact as reference.

The rim at 78.5° is below the equator, so the ball still lifts straight out for cleaning.

### Prior art and ball size — read this first

**The Kensington SlimBlade already ships this gesture, and Alex has used one extensively and
rates it highly** ("loved it, used it constantly"). The keyboard has been **redesigned around
the SlimBlade's 55 mm ball**, not the 34 mm charybdis ball.

Consequences:

- **The feel question is already answered.** Any plan whose main purpose is validating
  whether modeless twist-scroll is pleasant is solving a retired problem. Bench work should
  target cross-talk and calibration, which are engineering unknowns, not ergonomics.
- **Ergonomic transfer risk is gone.** Twist leverage scales hard with diameter; a 55 mm
  palm-driven ball is exactly the geometry the proven gesture came from. The "can you twist
  a small ball without rolling it" concern applies to 34 mm builds, not this one.
- **All geometry recommendations hold unchanged.** Conditioning and cross-talk percentages
  are scale-invariant — `A` scales uniformly with R, so κ and leakage ratios don't move.
- **Everything absolute gets better by 1.62×**: twist resolution (15.1 counts/° at 800 CPI,
  ~454 counts per 30° twist) and angular SNR, since `pinv(A)` scales as 1/R.
- **The ball is locally flatter** — 4.5 µm sag across a 1 mm imaging window versus 7.4 µm at
  34 mm — marginally kinder to the sensor's fixed 2.4 mm focus.
- **Equatorial mounting gets far easier.** A 55 mm ball stands much higher above any socket
  rim, which is exactly what the high-θ placements need.

**Cheapest high-value action available: measure the SlimBlade's own sensor geometry.** It is
a shipping product that solved this problem at this ball diameter with a gesture already
known to be good. Determining its θ and α — and how it handles ball retention alongside
sensor placement — is free ground truth that no amount of modelling replaces. Do this before
committing to a shell.

Known so far, from the [iFixit teardown](https://www.ifixit.com/Guide/Kensington+Slimblade+Trackball+Disassembly/149565):

- **Two optical sensors**, described as "horizontal" and "vertical", each on a **ZIF flex
  connector** — so at least one sits on a daughterboard off the main PCB.
- Ball rides on **3 steel points** (large flathead screws through the housing).
- Main PCB sits beneath the ball, 3× PH0 screws. Case is 7 screws, clamshell.

If "horizontal/vertical" denotes *mounting orientation*, Kensington shipped the **pole +
equator asymmetric layout** documented above — which would make it the production-proven
choice at this ball size. Treat as unconfirmed: the naming may instead describe which axis
each sensor contributes. **FCC internal photos settle it**: FCC ID **GV3B/GV3M01002**,
`fccid.io/GV3M01002` (blocks automated fetches; open in a browser).

Note the asymmetry in what transfers: a manufacturer bolts sensors to moulded bosses at
known angles, so the layout's CPI-immunity means shipping without per-unit calibration. A
printed shell has worse angular tolerance, and this layout's rotation-error leakage is 2×
the symmetric pair's — so **calibration is mandatory here even though Kensington skips it**.

**3D models on the usual sites are all exterior accessories** (stands, wedges, bases) and
contain no sensor geometry. Photogrammetry is the wrong tool twice over: sensors are
internal, and glossy black plastic with a mirror ball is near worst-case for feature
matching. Open the unit and use calipers.

**Why two.** A single sensor aimed at the ball's centre is structurally blind to spin about
its own optical axis — pure rotational flow, zero net displacement under the lens. Two
sensors give 4 measurements for 3 rotational DOF, making ω fully observable including yaw.

**Math.** For a sensor at unit position **n̂** with tangent axes (û, v̂), surface velocity is
**v** = **ω** × R**n̂**. Using the triple product, its two readings are `R ω·v̂` and
`−R ω·û` — so each sensor contributes two rows of a 4×3 matrix, `m = A·ω`. Solve
`ω = pinv(A)·m`, ~12 MACs per poll. ωx/ωy → cursor, ωz → scroll.

The normal equations collapse to a closed form (verified numerically):

```
AᵀA = R²(2I − n̂₁n̂₁ᵀ − n̂₂n̂₂ᵀ)
```

Eigenvalues are `{1−c, 1+c, 2}` with `c = n̂₁·n̂₂`. Two consequences fall straight out:

- **Conditioning depends only on the sensor positions, never on the mounting rotations ψ.**
  So the shell geometry can be designed *before* any angle is measured. ψ only affects the
  matrix entries, not how well the solve behaves.
- **Optimal angular separation is exactly γ = 90°** (`c = 0`, eigenvalues `{1,1,2}`,
  κ = √2). Antipodal (`c = −1`) is singular — the pair shares a blind axis along the line
  joining them, which is why it must be avoided.

### Solved geometry

Coordinates: θ = polar angle from the ball's **bottom pole** (θ=0 is the conventional
single-sensor spot, θ=90° is the equator); α = azimuth either side of straight-forward.

| Geometry | cond | noise gain x / y / z | phantom scroll* |
|---|---|---|---|
| θ=90°, α=±45° — **optimum** | 1.41 | 1.00 / 1.00 / 0.71 | **0.0 %** |
| θ=80°, α=±45° — **recommended** | 1.44 | 0.99 / 1.00 / 0.73 | 0.6 % |
| θ=75°, α=±45° | 1.46 | 0.97 / 1.00 / 0.76 | 0.9 % |
| θ=35°, α=±45° — shallow | 2.20 | 0.79 / 1.00 / 1.59 | 5.0 % |
| θ=20°, α=±45° — conventional cup depth | 2.92 | 0.76 / 1.00 / 2.84 | **9.7 %** |

\* spurious scroll counts per 100 counts of cursor motion, at 5 % CPI mismatch between the
two sensors.

**Target θ as close to 90° as the shell allows, with α = ±45° (90° apart in azimuth).**
α=±45° is consistently optimal — wider spreads wreck the ωx channel (θ=75°, α=±90° gives
noise gain 2.73 on x). Yaw noise gain has a hard floor of 1/√2 ≈ 0.707; nothing does better.

**Cross-talk, not noise, is what rules out a retrofit.** At conventional cup depth the yaw
noise gain is only ~4× the floor — survivable on its own. What kills it is that a 5 % CPI
mismatch produces ~10 % phantom scroll during ordinary cursor movement. Cross-talk falls to
**exactly zero** at the equator, because yaw then lies along `n̂₁ × n̂₂` — the eigenvector
that carries no coupling to the roll subspace. That single fact is the strongest argument
for equatorial mounting, and it can't be recovered in firmware.

**At a good geometry, mounting-angle precision becomes the binding constraint.** A 3° ψ
error leaks ~2.6 % regardless of θ, so above θ≈75° it dominates the CPI term. Measure ψ per
sensor (procedure above) rather than trusting assembly tolerance.

### Asymmetric alternative: pole + equator

A second layout family satisfies the same optimality condition and may be the better build.
Keep the existing sensor at the bottom pole, add **one** sensor at the equator.

| | sep | cond | gx | gy | gz | leak CPI | leak ROT |
|---|---|---|---|---|---|---|---|
| symmetric θ=90, α=±45 | 90° | 1.41 | 1.000 | 1.000 | **0.707** | 0.00 % | **2.62 %** |
| asym pole+equator | 90° | 1.41 | **0.707** | 1.000 | 1.000 | 0.00 % | 5.23 % |
| asym pole + θ=80 | 80° | 1.56 | 0.707 | 1.000 | 1.031 | 0.88 % | 5.31 % |

Pole-to-equator **is** a 90° separation — identical conditioning to the symmetric optimum.
The fusion degenerates almost completely:

```
ωx = 0.5 · (s0_v + s1_v)
ωy = 1.0 ·  s0_u                  // pole sensor alone
ωz = 1.0 ·  s1_u                  // SCROLL: equator sensor alone, coefficient 1
```

**Scroll is a single-channel read**, so CPI mismatch between the sensors cannot produce
phantom scroll at all — structurally, not by tuning. Cost is a √2 penalty on scroll noise
(1.000 vs 0.707), which is irrelevant: scroll is detent-quantized and needs far less
resolution than the cursor. Cursor-x actually gets *better* (0.707 vs 1.000), since the pole
sensor reads roll optimally.

**The catch the CPI column hides: rotation-error leakage doubles (5.23 % vs 2.62 %).**
Scroll rides on one sensor's u-axis, so its mounting rotation error feeds roll straight into
scroll with no partner to cancel against. Since rotation error dominates at good geometries,
this layout is *worse* uncalibrated. It only wins once per-sensor ψ is empirically
calibrated — which absorbs static rotation error entirely and leaves drift as the residual
risk. **Do not choose this layout without committing to the calibration procedure.**

**Optional containment.** The pinv above couples cursor-x to the new sensor. You can decline
that redundancy and drive the cursor from the pole sensor alone (it reads both roll axes by
itself), trading gx 0.707 → 1.0 for a cursor path that is bit-for-bit what it is today.
Useful when the existing trackball is a daily driver and cursor regression is unacceptable.

Mechanical note: on an open cup the ball's equator often sits at or above the socket rim, so
an above-rim turret sidesteps the sensor-vs-retention conflict entirely. Its real enemies are
fingers, lint, and ambient light. Caliper the actual ball exposure before believing either
version of that claim.

### The fusion matrix is trivial at the optimum

θ=90°, α=±45°, inputs `[s0_u, s0_v, s1_u, s1_v]`:

```
ωx (cursor right)   = 0.70711 · (s0_v + s1_v)      // SUM of the v axes
ωy (cursor forward) = 0.70711 · (s0_v − s1_v)      // DIFFERENCE of the v axes
ωz (SCROLL)         = 0.5     · (s0_u + s1_u)      // SUM of the u axes
```

Note this is **not** the "cursor = sum, scroll = difference" shape it's tempting to assume.
Scroll is a *sum* of the azimuthal (u) axes — both sensors see yaw identically in u — while
cursor-forward is the *difference*. Getting this backwards produces a build that scrolls
when you move and moves when you twist.

Q16 constants (int32 accumulate, `>>16` at the end):

```c
// theta=80, alpha=+-45  — recommended practical geometry
static const int32_t FUSE_X[4] = { -7811, +44985,  +7811, +44985};
static const int32_t FUSE_Y[4] = {     0, +46341,      0, -46341};
static const int32_t FUSE_Z[4] = {+33273,  -5778, +33273,  +5778};
```

Regenerate for any other geometry rather than interpolating — the ωx row is sensitive to θ.

**Generators are bundled with this skill** (need numpy):

- `dual_sensor_geometry.py` — measurement model, structural self-checks, θ/α sweep,
  and Q16 constant emission for any geometry.
- `dual_sensor_crosstalk.py` — CPI-mismatch and mounting-rotation leakage, plus the
  sweet-spot search that produced the table above.

Run them from this directory. The self-checks at the top of the geometry script assert the
closed form, ψ-invariance, antipodal singularity, and single-sensor yaw blindness — if a
change breaks one of those, the model is wrong, not the hardware.

**Implementation.**

- Fuse on the raw **int16** deltas from `pmw33xx_read_burst`, *before* `CONSTRAIN_HID_XY`.
  Routing each sensor through the stock `get_report` clamps to ±127 per-sensor and destroys
  the precision the fusion needs.
- Fusion belongs in the custom driver **on the right half**, before the report crosses the
  split serial link — that's where int16 precision still exists.
- Two burst reads ≈ 300 µs against the 1 ms throttle budget. The ~150 µs skew between reads
  is irrelevant at hand speeds.

**Cross-talk is the whole ballgame.** Nobody produces pure translation. Mounting angle
error, unequal 2.4 mm lens gaps, CPI mismatch, or one sensor on a scuffed patch all leak
roll into the yaw channel — phantom scrolling during cursor movement is maddening. Budget
for a deadzone on ωz, a ratio gate (scroll only when |ωz| dominates |ωxy|), a short mode
latch with hysteresis, and a calibration pass measuring leakage during pure rolls. Write
the raw-delta debug dump first.

## Reference

- `~/qmk_firmware/drivers/sensors/pmw33xx_common.{c,h}` — authoritative driver source
- `~/qmk_firmware/quantum/pointing_device/pointing_device.h` — `pointing_device_driver_t`
- `~/qmk_firmware/keyboards/bastardkb/charybdis/charybdis.c` — EEPROM DPI/sniping reference

Prefer reading these over recalled API details; the pointing device API drifts between QMK
versions.
