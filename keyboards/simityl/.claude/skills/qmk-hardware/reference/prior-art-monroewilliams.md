# Prior art — monroewilliams/trackball

<https://github.com/monroewilliams/trackball> — a from-scratch dual-sensor trackball with
Kensington-SlimBlade-style Z-twist scroll. 278 stars, last pushed 2026-04. Author reports it
as his daily driver. [Video demo](https://www.youtube.com/watch?v=PVdwrbiuzwA),
[assembly guide](https://github.com/monroewilliams/trackball/blob/HEAD/hardware/Assembly.md).

This is the same problem, solved and shipped. Read it before committing the v7 shell.

## Its geometry, in our coordinates

Author's convention (`src/trackball.cpp`): azimuth = clockwise from 12 o'clock (away from
the user), elevation = degrees **down from horizontal**. So his elevation 30° = our θ 60°
from the bottom pole. `hardware/trackball.scad` confirms with `sensor_angle = 60`.

```c
#define S1A 180          // toward the user
#define S1E 30           // -> theta = 60
#define S2A (270 + 45)   // 315, left-front
#define S2E 30           // -> theta = 60
```

Scored with `../dual_sensor_geometry.py`:

| geometry | γ | cond | gx | gy | gz | leak CPI | leak ROT |
|---|---|---|---|---|---|---|---|
| **monroe shipping: θ=60 @180 / θ=60 @315** | 106.3 | 1.67 | 0.839 | 1.128 | 0.834 | 1.56 % | 3.03 % |
| monroe *original*: θ=90 @180 / θ=90 @270 | 90.0 | 1.41 | 1.000 | 1.000 | 0.707 | 0.00 % | 2.62 % |
| our symmetric optimum θ=90, α=±45 | 90.0 | 1.41 | 1.000 | 1.000 | 0.707 | 0.00 % | 2.62 % |
| our v7 as read (A θ=15 front, B θ=80 back) | 95.0 | 1.48 | 0.707 | 1.022 | 0.985 | 0.84 % | 5.07 % |

**The headline result: his commented-out original layout is bit-for-bit our theoretical
optimum** — two sensors at the equator, 90° apart in azimuth, cond 1.41, zero CPI leakage.
He abandoned it for mechanical reasons, moved 30° below the equator and opened the azimuth
to 135°, and ships happily at cond 1.67 with 1.56 % CPI leak.

That is the strongest evidence available that **the geometry budget is generous**. It
independently confirms the "take the mechanically easiest θ_B" conclusion in
`v7-shell-fitness.md`: our v7 read is *better* conditioned than a build its author prefers
to every commercial trackball he owns.

## What it validates in our design

- **55 mm ball** (`ball_diameter = 55` in the scad; 57 mm billiard and 52.5 mm are
  commented alternatives). Same size, same gesture, independently arrived at.
- **3 bearings at 120°**, 1/8" (3.175 mm), `ball_clearance = 1`. Matches our 3-point support.
- **Scroll is a SUM of the two sensors' azimuthal axes**, not a difference:
  `{0, -0.5, 0, -0.5}` — "Z is the average of the two sensors' y components." Exactly the
  trap flagged in SKILL.md, confirmed by a working build.
- **Sensors mounted "sideways" for mechanical reasons** — ψ = 90°, folded into the transform
  matrix rather than a rotation register. Same conclusion we reached about
  `ROTATIONAL_TRANSFORM_ANGLE` being global and therefore useless here.
- **Standoff**: `sensor_clearance = 2` with the sensor origin at the *lens surface*. Our
  proven 2.96 mm is measured PCB-face-to-ball, a different datum — the two are consistent if
  the lens protrudes ~1 mm past the board face, which is what our working v2 build implies.

## What it does differently, and what to steal

**Cross-talk handling is much simpler than we budgeted for.** The whole mitigation is a
ratio gate plus a hard mode lockout:

```c
if ((fabs(delta.z) > (fabs(delta.x) * 2)) && (fabs(delta.z) > (fabs(delta.y) * 2))) {
    scroll_accum += delta.z;              // accumulate, scroll_tick = 64
    delta.x = 0; delta.y = 0;             // suppress cursor entirely while scrolling
} else {
    delta.z = 0;                          // otherwise suppress scroll entirely
}
```

No deadzone, no hysteresis latch, no calibration pass — and he lives with 1.56 % CPI leak
and 3.03 % rotation leak. **Start with the 2× ratio gate alone** and only add the rest if
phantom scroll actually shows up. Our v7 numbers are in the same band, so it should hold.

**Where we are ahead:** his transform is hand-tuned, with `// TODO: build a transform from
the azimuth/elevation constants` sitting above it. Our `dual_sensor_geometry.py` already
generates it from (θ, φ, ψ) and emits Q16 constants. We are ahead on the math and behind on
the mechanics — his printed shell, bearing pockets, and sensor cutouts are all solved.

**Also worth stealing:** the piezo speaker producing SlimBlade-style clicks on each scroll
detent, and `scroll_tick = 64` as a starting quantization.

## Caveats

- Standalone Arduino/PlatformIO firmware on a XIAO/QT Py, **not QMK** — the fusion logic
  transfers, the driver plumbing does not.
- Built for ADNS-9800 and PMW3360; ADNS-9800 boards read inverted relative to the others in
  his mounting. We are on PMW3389.
- His shell is a standalone trackball, not a keyboard-integrated socket, so hand clearance
  and ball retention constraints differ from ours.
