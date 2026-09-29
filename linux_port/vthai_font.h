#ifndef VTHAI_FONT_H
#define VTHAI_FONT_H

#include <stdint.h>
#include <string>

void assemble_8x16_cell(const uint8_t* upper_tile, const uint8_t* lower_tile, uint8_t* out_16_byte_cell);
void render_debug_cell(const uint8_t* cell_16_bytes);
bool load_raw_font_tile(const std::string& filepath, uint16_t tile_index, uint8_t* out_8_byte_tile);

// Phase 2 Bulk Extraction: Exports all 256 vertical character matrix sets to a target text layout file
bool export_full_font_set(const std::string& bin_path, const std::string& out_text_path);

#endif // VTHAI_FONT_H
