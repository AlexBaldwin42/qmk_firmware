# Simityl Keyboard Improvement TODO

## Approved for Implementation

### 5. DPI Management with Built-in Functions
- [x] Review current auto-layer activation behavior
- [x] Decision: Keep as-is - current AUTO_MOUSE feature works correctly
- [ ] Status: No changes needed

### 6. Deferred Execution for RGB Updates
- [x] Implement deferred execution for RGB indicator updates
- [x] Replace per-scan RGB updates with event-triggered updates
- [x] Enable DEFERRED_EXEC_ENABLE in rules.mk
- [x] Add trigger_rgb_update() calls on layer/mode changes
- [x] Test compile - SUCCESS
- [ ] Status: ✅ COMPLETED

### 7. ENCODER_MAP Feature
- [x] Convert from `encoder_update_user()` to `ENCODER_MAP`
- [x] Enable `ENCODER_MAP_ENABLE = yes` in rules.mk
- [x] Create encoder map for all 6 layers
- [x] Keep `encoder_update_user()` for special cases (5x scroll speed on RAISE, volume delay on ADJUST)
- [x] Test compile - SUCCESS
- [ ] Status: ✅ COMPLETED

### 8. HOLD_ON_OTHER_KEY_PRESS Per Key
- [x] Remove global PERMISSIVE_HOLD from config.h
- [x] Implement `get_hold_on_other_key_press()` function in keymap.c
- [x] Configure to match previous PERMISSIVE_HOLD behavior (all mod-tap and layer-tap keys)
- [x] Test compile - SUCCESS
- [ ] Status: ✅ COMPLETED

### 9. Consolidate info.json
- [x] Move RGB matrix settings from config.h to info.json (animations, defaults, LED count, split count)
- [x] Move basic split configuration to info.json
- [x] Move ws2812 configuration to info.json
- [x] Test compile - SUCCESS
- [ ] Status: ✅ COMPLETED (encoder and pointing device settings remain in config.h as they require specific format)

### 10. Use QMK's Built-in Drag Scroll
- [x] Research QMK built-in drag scroll features
- [x] Decision: No built-in drag scroll feature exists in QMK
- [x] Current implementation in simityl.c is the standard approach
- [ ] Status: ✅ NOT NEEDED - Keep existing drag scroll implementation

### 11. Update Custom Keycodes to SAFE_RANGE
- [x] Change custom keycodes enum to start at SAFE_RANGE
- [x] Update from QK_KB_3 to SAFE_RANGE pattern
- [x] Test compile - SUCCESS
- [ ] Status: ✅ COMPLETED

### 14. EEPROM Storage for DPI Level Persistence
- [x] Move DPI/sniping keycodes from keymap to keyboard level (simityl.h)
- [x] Implement EEPROM config structure in simityl.c
- [x] Implement DPI level persistence (5 levels: 400, 800, 1200, 1600, 2000)
- [x] Implement sniping DPI (200 DPI base)
- [x] Add EEPROM read/write functions
- [x] Add keyboard initialization functions (eeconfig_init_kb, matrix_init_kb, keyboard_post_init_kb)
- [x] Update process_record_kb to handle DPI/sniping keycodes
- [x] Update keymap to use keyboard-level keycodes (DPI_UP, DPI_DOWN, SNIPING, SNP_TOG)
- [x] Test compile - SUCCESS
- [ ] Status: ✅ COMPLETED

## Not Implementing

### 1. Achordion for Better Home Row Mods
- Status: Rejected - not implementing at this time

### 2. Repeat Key (QK_REP)
- Status: Rejected - not implementing at this time

### 3. Tri-Layer for Auto Adjust Layer
- Status: Rejected - keeping current Q and / triggers

### 4. Layer Lock
- Status: Rejected - already have this functionality, no other use case

### 12. Per-Combo Timing
- Status: Rejected - not needed at this time

### 13. Reduce Firmware Size
- Status: Rejected - RP2040 has enough space, not a concern

### 15. Post Config Cleanup
- Status: Deferred - can come back to this later

## Resolved Questions

1. ✓ **Item 5 (DPI/Auto-layer):** Keep as-is - current AUTO_MOUSE feature works correctly
2. ✓ **Item 8 (HOLD_ON_OTHER_KEY_PRESS):** Match current global PERMISSIVE_HOLD behavior
3. ✓ **Item 14 (EEPROM DPI):** Yes, implement using charybdis pattern from bastardkb/charybdis/charybdis.c
