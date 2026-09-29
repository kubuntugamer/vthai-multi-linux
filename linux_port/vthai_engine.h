#ifndef VTHAI_ENGINE_H
#define VTHAI_ENGINE_H

#include <stdint.h>
#include <string>
#include <vector>

enum ThaiLayerType {
    LAYER_BASELINE,
    LAYER_UPPER,
    LAYER_TONE,
    LAYER_LOWER
};

struct VThaiCursorState {
    uint16_t current_col;
    uint16_t current_row;
    uint8_t  last_char_type;
};

struct VThaiScreenCell {
    uint8_t baseline_code;
    uint8_t upper_vowel_code;
    uint8_t tone_mark_code;
    uint8_t lower_vowel_code;
    bool has_content;
};

struct VThaiScreenBuffer {
    uint16_t max_cols;
    uint16_t max_rows;
    std::vector<std::vector<VThaiScreenCell>> grid;
};

// Global translation settings modifier flag
void set_engine_version_mode(const std::string& path);

uint8_t translate_char_code(uint8_t input_byte);
ThaiLayerType classify_byte(uint8_t byte_code);
void process_vthai_step(uint8_t byte_code, VThaiCursorState* state);
void render_string_to_grid(const std::vector<uint8_t>& input_stream, std::vector<VThaiScreenCell>& line_cells);
bool load_input_file_stream(const std::string& filepath, std::vector<uint8_t>& out_stream);
void process_stream_to_buffer(const std::vector<uint8_t>& stream, VThaiScreenBuffer& buffer);

#endif // VTHAI_ENGINE_H
