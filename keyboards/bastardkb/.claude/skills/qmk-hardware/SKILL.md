---
name: qmk-hardware
description: BastardKB hardware — blackpill vs promicro controllers, DFU flashing, the charybdis trackball reference implementation, and dilemma's Cirque trackpad
---

# BastardKB hardware

You are in `~/qmk_firmware/keyboards/bastardkb/`. **Alex's builds use these PCBs** — scylla
is a BastardKB board, and simityl is a custom build on BastardKB PCBs (charybdis trackball,
skeletyl lineage, Splinky/blackpill adapters). The config values here therefore describe
*physical facts about hardware he owns*, not upstream preferences.

That distinction matters most for the trackball, below.

For simityl's own pins and sensors, use the `qmk-hardware` skill scoped to
`keyboards/simityl/`. For build and flash, `/qmk`.

## Controllers

Every board here ships in two controller variants, and they are **not interchangeable**:

| Variant | MCU | Flashing |
|---|---|---|
| `blackpill` | STM32F411 | **DFU** — `dfu-util`, boot jumper. Not UF2. |
| `promicro` | atmega32u4 | Caterina, or a converter via `CONVERT_TO` |

The built target is **`bastardkb/scylla/blackpill`** — STM32F411, so flashing is DFU, not
the double-tap-to-`RPI-RP2` flow the RP2040 boards use. The blackpill variant carries its
own `mcuconf.h` and `halconf.h` for ChibiOS peripheral setup; the promicro variant is just
a `keyboard.json`.

## Pointing devices in this family

| Board | Device | Driver |
|---|---|---|
| **charybdis** | PMW3360 / PMW3389 trackball | `pmw33xx_common.c` |
| **dilemma** | Cirque trackpad | `cirque_pinnacle_spi` |
| scylla, skeletyl, tbkmini | none | — |

**scylla has no trackball.** Its userspace `rules.mk` is near-empty for exactly this
reason. Don't add pointing device config to the scylla keymap expecting it to do something.

Cirque and PMW33xx are entirely different drivers with different config surfaces — dilemma
is not a useful reference for trackball work despite also being a pointing device.

## charybdis is the trackball reference

simityl inherited its trackball implementation from charybdis. When extending simityl's
pointing device, read these first:

- **`charybdis/charybdis.c`** — EEPROM persistence for DPI levels and sniping mode. This is
  the pattern simityl's TODO item 14 implemented; match it rather than inventing a new one.
- **`charybdis/post_config.h`** — mousekey and scroll defaults, inherited wholesale.
- **`charybdis/config.h`** — `CHARYBDIS_CONFIG_SYNC` and the split transaction ID setup
  that simityl reuses for syncing pointer config across halves.

Read these; don't modify them — see the `qmk-dev` skill scoped to this directory.

### The sensor is mounted at an angle — that's a PCB fact

`charybdis/config.h` sets:

```c
#define ROTATIONAL_TRANSFORM_ANGLE -25
```

This is not a taste setting. The sensor sits **rotated 25° on the trackball PCB**, and the
define writes `REG_Angle_Tune` to correct it in hardware. Any build using that PCB
inherits the physical rotation.

**The `-25` is not transferable.** It encodes the sensor's rotation *in the charybdis
shell*. Alex's simityl uses the same PCB family but mounts the trackball in a different
orientation in a different body, so it needs its own measured angle — or none, if the
rotation happens to fall on a 90° multiple that `INVERT_X` / `INVERT_Y` already covers.

Never copy a rotation constant between bodies. Measure it — see the `qmk-hardware` skill
scoped to `keyboards/simityl/` for the procedure.

### MOUSE_EXTENDED_REPORT

The charybdis readme documents `#define MOUSE_EXTENDED_REPORT`, which widens mouse X/Y from
±127 to ±32767. The readme notes these sensors can genuinely saturate ±127. Relevant to any
high-CPI or multi-sensor work. Requires reflashing **both** halves.

`CHARYBDIS_CONFIG_SYNC` carries the same both-halves reflash requirement.

## PMW33xx multi-sensor note

The driver supports multiple sensors on one SPI bus natively (`PMW33XX_CS_PINS { a, b }`,
shared SCK/MOSI/MISO, one CS GPIO each, MISO tri-stated when CS is high). charybdis uses a
single sensor and its stock wrappers only touch sensor 0. Full multi-sensor detail and the
dual-sensor yaw-scroll design live in the `qmk-hardware` skill scoped to
`keyboards/simityl/`, since that's the board being modified.

## Never enumerate the keyboards tree

`~/qmk_firmware/keyboards/` holds **1101 entries across ~13,000 directories**. A recursive
glob or `find` will flood context and may time out. Address boards by exact path and scope
searches with `--include` or a directory argument.
