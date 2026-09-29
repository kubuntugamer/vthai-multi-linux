#ifndef VTHAI_ENGINE_H
#define VTHAI_ENGINE_H

#include <stdint.h>
#include <string>
#include <vector>

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

// Represents a single 8x16 text block cell that handles layered accents
struct VThaiScreenCell {
    uint8_t baseline_code;
    uint8_t upper_vowel_code;
    uint8_t tone_mark_code;
    uint8_t lower_vowel_code;
    bool has_content;
};

// Core processing functions
uint8_t translate_char_code(uint8_t input_byte);
ThaiLayerType classify_byte(uint8_t byte_code);
void process_vthai_step(uint8_t byte_code, VThaiCursorState* state);
void render_string_to_grid(const std::vector<uint8_t>& input_stream, std::vector<VThaiScreenCell>& line_cells);

// Reads a file from storage and returns a byte stream payload vector
bool load_input_file_stream(const std::string& filepath, std::vector<uint8_t>& out_stream);

#endif // VTHAI_ENGINE_H
