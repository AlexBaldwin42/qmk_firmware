---
name: qmk-dev
description: Working in the BastardKB family — this is upstream QMK code in a fork, what may be edited here, the board/variant matrix, and where scylla changes actually belong
---

# BastardKB boards

You are in `~/qmk_firmware/keyboards/bastardkb/` on the `simian_main` fork.

**This tree documents hardware Alex physically owns.** His builds use BastardKB PCBs —
scylla is a BastardKB board outright, and simityl is a custom build on BastardKB PCBs
(skeletyl chassis lineage, charybdis trackball, Splinky/blackpill adapter boards). So these
files are not foreign code to skim past: they are the **authoritative description of the
physical hardware**, including pin assignments, matrix wiring, LED geometry, and sensor
mounting angles that were determined by the PCB layout, not by preference.

When debugging a hardware symptom on simityl, the corresponding BastardKB definition is the
closest thing to a datasheet you have.

For fleet-wide architecture invoke the global `/qmk-dev`. For build and flash, `/qmk`. For
sensors and controllers, the `qmk-hardware` skill scoped to this directory.

## Read freely, edit reluctantly

Everything here is still **upstream QMK code**, tracked against `origin`. Reading it is the
point; editing it carries a permanent rebase burden.

Only **scylla** is built from this tree, and its keymap lives in the userspace at
`~/source/qmk_userspace/keyboards/bastardkb/scylla/keymaps/simian/`. Board definitions
here need no changes to support it.

Editing upstream files creates a permanent rebase burden against `origin` (qmk/qmk_firmware)
for no benefit. Before changing anything here, check the change can't be made in:

1. The userspace keymap's `config.h` / `rules.mk` — covers nearly everything.
2. `users/simian/` — for behavior shared with the other boards.

If a change genuinely belongs upstream, make it here and **PR it to `origin`** rather than
carrying it on `simian_main` indefinitely.

## Board and variant matrix

Five boards, each with controller variants:

| Board | Variants | Pointing device | Built here? |
|---|---|---|---|
| **scylla** | `blackpill`, `promicro` | none | **Yes** — `bastardkb/scylla/blackpill` + `simian` |
| **skeletyl** | `blackpill`, `promicro` | none | No — but simityl's chassis derives from it |
| **tbkmini** | `blackpill`, `promicro` | none | No |
| **charybdis** | `3x5`, `3x6`, `4x6` | PMW3360/3389 trackball | No — but it's the trackball reference |
| **dilemma** | `3x5_2`, `3x5_3`, `4x6_4` | Cirque trackpad | No |

The build target in `qmk.json` is `bastardkb/scylla/blackpill`, not bare `scylla` — the
variant is part of the path. Shared board config sits at `scylla/info.json`; the variant
directories carry the controller-specific `keyboard.json`, `config.h`, `mcuconf.h`, and
`halconf.h`.

## Why this directory matters beyond scylla

**simityl was derived from here** — chassis and matrix from `skeletyl`, trackball and
config-sync from `charybdis`. That's why simityl's files carry Quentin Lebastard's and
Charly Delay's copyright headers, and why `CHARYBDIS_CONFIG_SYNC` appears in simityl's
`config.h`.

So this tree is the **reference implementation** to read when extending simityl:

- `charybdis/charybdis.c` — EEPROM DPI/sniping persistence, the pattern simityl's TODO
  item 14 copied.
- `charybdis/post_config.h` — the mousekey defaults simityl inherited.
- `skeletyl/` — matrix and LED geometry lineage.

Read them; don't modify them.

## The scylla keymap uses the shared 36-key core

scylla is 58 keys (4x6+5). Its keymap wraps the same `users/simian/` core as the 36-key
boards, supplying the number row and outer columns around the wrapper rather than
duplicating the alphas. Its `rules.mk` is intentionally near-empty — no pointing device, no
encoder. See the global `/qmk-dev` for the `wrappers.h` pattern.

## Never enumerate the keyboards tree

`~/qmk_firmware/keyboards/` holds **1101 entries across ~13,000 directories**. A recursive
glob or `find` there will flood context and may time out. Address boards by exact path and
scope every search with `--include` or a specific directory argument. Even
`keyboards/bastardkb/` alone spans five boards × three variants — target the one you mean.
