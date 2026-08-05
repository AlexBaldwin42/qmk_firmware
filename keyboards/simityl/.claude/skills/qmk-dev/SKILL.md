---
name: qmk-dev
description: Editing the simityl keyboard definition — what lives in this directory, the keyboard.json vs config.h split, upstream provenance, and what belongs in the userspace instead
---

# simityl keyboard definition

You are in `~/qmk_firmware/keyboards/simityl/` — the **keyboard definition**, in the
`simian_main` fork. This is one of the few boards Alex owns outright; it is not upstream
QMK code, so editing here is expected.

For fleet-wide architecture and the shared keymap, invoke the global `/qmk-dev`. For build
and flash, `/qmk`. For pins and sensors, the `qmk-hardware` skill scoped to this directory.

## What belongs here vs. the userspace

| Here (`keyboards/simityl/`) | Userspace (`~/source/qmk_userspace`) |
|---|---|
| Matrix pins, diode direction, layouts | Keymaps, layers, keycodes |
| SPI / pointing device / encoder pin config | Per-unit driver + resolution choices |
| RGB matrix LED positions and flags | RGB behavior and layer indicators |
| Board-level `shutdown_kb`, EEPROM config | `process_record_user`, shared behavior |

**Default to the userspace.** Only edit here when the change is genuinely about the
physical board — pins, matrix, LED geometry. Behavior belongs in `users/simian/`.

Note the per-unit variations (encoder resolution, PMW3360 vs PMW3389) live in the
*keymap's* `config.h` and `rules.mk` in the userspace, **not here** — they differ between
physical units, so hardcoding one here would break the others.

## File map

| File | Holds |
|---|---|
| `keyboard.json` | Matrix pins, split serial, ws2812, rgblight, processor/bootloader, `LAYOUT_split_3x5_3` |
| `config.h` | SPI pins, `POINTING_DEVICE_CS_PIN`, encoder pads, handedness, auto-mouse, RGB matrix modes |
| `post_config.h` | Mousekey defaults, `SPLIT_TRANSACTION_IDS_KB` for config sync |
| `mcuconf.h` | ChibiOS peripheral enables (SPI) |
| `simityl.c` | `shutdown_kb` (red LEDs on bootloader jump), RGB LED index map |
| `simityl.h` | Thin — just `#include "quantum.h"` |
| `TODO.md` | Improvement log: completed, rejected, and deferred items |

### The keyboard.json / config.h split is deliberate

TODO item 9 moved RGB matrix settings, split config, and ws2812 into `keyboard.json`.
**Encoder and pointing device settings stayed in `config.h`** because they need formats
that `keyboard.json` cannot express. Don't "finish the migration" — it was stopped on
purpose.

### Read TODO.md before proposing improvements

It records what was already done, what was **rejected** (Achordion, `QK_REP`, tri-layer,
layer lock, per-combo timing, firmware size reduction), and what was deferred (post_config
cleanup). Re-proposing a rejected item wastes everyone's time.

## Provenance and licensing

simityl is derived from BastardKB's **skeletyl** (chassis, matrix) and **charybdis**
(trackball, config sync). Files here carry original copyright headers:

```
Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
```

Preserve those. Note `simityl.c` is GPL-**2**-or-later while `simityl.h` is GPL-**3**-or-later
— inherited inconsistency from upstream, not worth "fixing" unilaterally.

`CHARYBDIS_CONFIG_SYNC` in `config.h` gates the split transaction ID in `post_config.h`.
The EEPROM DPI/sniping persistence follows the charybdis pattern — see
`keyboards/bastardkb/charybdis/charybdis.c` for the reference implementation.

The physical build uses **BastardKB PCBs**, so `keyboards/bastardkb/` is effectively the
datasheet for this hardware, not just lineage trivia. See the `qmk-hardware` skill scoped
to that directory.

## Two known inherited-config problems

**`CHARYBDIS_DRAGSCROLL_REVERSE_Y` is dead config — but drag scroll itself works fine.**

Drag scroll is fully functional: `DRGSCRL` is bound to **U** on the pointer layer
(`users/simian/wrappers.h`, `LAYOUT_LAYER_POINTER` row 0, index 6), with `DRG_TOG` on the
adjust layer. `simian.c` dispatches both, and `users/simian/simian_pointing.c` implements
the behavior — buffering x/y and emitting h/v past a ±6 threshold.

It is a **hand-rolled** implementation built on QMK hooks, not a QMK feature — there is no
built-in drag scroll anywhere in `quantum/`. `TODO.md` item 10 records that investigation
and conclusion (though it says the code is in `simityl.c`; it now lives in the userspace).

The exit policy in `simian.c` is a deliberate custom design, and is the part most likely to
be mistaken for a bug:

- `DRGSCRL` momentary (tracks `record->event.pressed`), `DRG_TOG` latches
- `MS_BTN*` / `MS_WHL*` pass through **without** cancelling drag scroll
- `KC_ESC` cancels it and swallows the press
- **any other keypress cancels it**, via the `default:` branch

So a latched drag scroll silently drops the moment you type. That's intended.

What's inert is only the **define**. `CHARYBDIS_DRAGSCROLL_REVERSE_Y` is set in the
keymap's `config.h`, but the only readers in the entire QMK tree are
`keyboards/bastardkb/charybdis/charybdis.c` and
`keyboards/handwired/tractyl_manuform/tractyl_manuform.c` — neither of which simityl
compiles. `simian_pointing.c` hardcodes its scroll direction and never checks it.

So: to reverse vertical scroll direction, edit `simian_pointing.c`. Toggling the define
does nothing, and it should not be used to diagnose a scroll-direction complaint.

**A stale keymap lives in the fork.** `keyboards/simityl/keymaps/simian_legacy/` still
exists here, while the live keymap is in the userspace at
`keyboards/simityl/keymaps/simian/`. Edits to `simian_legacy` do nothing for normal builds.
Confirm which one you're in before editing — the paths differ only by repo and suffix.

## Never enumerate the keyboards tree

`~/qmk_firmware/keyboards/` holds **1101 entries across ~13,000 directories**. A recursive
glob or `find` there will flood context and may time out. Address boards by exact path
(`keyboards/simityl/`, `keyboards/bastardkb/scylla/`) and scope every search with
`--include` or a specific directory argument.
