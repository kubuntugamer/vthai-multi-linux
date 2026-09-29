#ifndef VTHAI_FONT_H
#define VTHAI_FONT_H

#include <stdint.h>
#include <string>
#include <vector>
#include "vthai_engine.h"

void assemble_8x16_cell(const uint8_t* upper_tile, const uint8_t* lower_tile, uint8_t* out_16_byte_cell);
void render_debug_cell(const uint8_t* cell_16_bytes);
bool load_raw_font_tile(const std::string& filepath, uint16_t tile_index, uint8_t* out_8_byte_tile);
bool export_full_font_set(const std::string& bin_path, const std::string& out_text_path);

// Renders an entire line of composite cells horizontally side-by-side
void render_horizontal_line(const std::string& bin_path, const std::vector<VThaiScreenCell>& line_buffer);

#endif // VTHAI_FONT_H
