#include "vthai_engine.h"

// Classifies an incoming byte based on TIS-620/Kaset stacking rules
ThaiLayerType classify_byte(uint8_t byte_code) {
    // Standard ASCII and low control characters always advance the baseline
    if (byte_code < 0x80) {
        return LAYER_BASELINE;
    }
    
    // Stacking upper vowels (Level 1 Vertical Shift)
    if ((byte_code >= 0xD4 && byte_code <= 0xD7) || byte_code == 0xE5) {
        return LAYER_UPPER;
    }
    
    // Stacking tone markers (Level 2 Vertical Shift)
    if (byte_code >= 0xE8 && byte_code <= 0xEB) {
        return LAYER_TONE;
    }
    
    // Stacking lower vowels (Sub-Baseline Shift)
    if (byte_code >= 0xD8 && byte_code <= 0xDA) {
        return LAYER_LOWER;
    }
    
    // Default fallback for remaining standard Thai consonants/vowels
    return LAYER_BASELINE;
}

// Processes a single input byte and updates layout canvas coordinates
void process_vthai_step(uint8_t byte_code, VThaiCursorState* state) {
    ThaiLayerType type = classify_byte(byte_code);
    state->last_char_type = type;
    
    switch (type) {
        case LAYER_BASELINE:
            // Draw baseline character, then step one character cell right
            state->current_col += 1;
            break;
            
        case LAYER_UPPER:
        case LAYER_TONE:
        case LAYER_LOWER:
            // Stacking modifier: overlay character asset at active col position
            // Keep horizontal column frozen for the next incoming symbol
            break;
    }
}
