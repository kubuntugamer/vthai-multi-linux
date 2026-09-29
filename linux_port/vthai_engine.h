#ifndef VTHAI_ENGINE_H
#define VTHAI_ENGINE_H

#include <stdint.h>

// Phase 1 Layout Rule Classifications
enum ThaiLayerType {
    LAYER_BASELINE,   // Consonants, numbers, symbols (Advances Cursor)
    LAYER_UPPER,      // Floating vowels (Freezes Cursor, Level 1 Stack)
    LAYER_TONE,       // Tone markers (Freezes Cursor, Level 2 Stack)
    LAYER_LOWER       // Under-letters (Freezes Cursor, Sub-Baseline)
};

// State structure tracking the active line canvas coordinates
struct VThaiCursorState {
    uint16_t current_col;
    uint16_t current_row;
    uint8_t  last_char_type;
};

// Function prototypes to expose them to main.cpp
ThaiLayerType classify_byte(uint8_t byte_code);
void process_vthai_step(uint8_t byte_code, VThaiCursorState* state);

#endif // VTHAI_ENGINE_H
