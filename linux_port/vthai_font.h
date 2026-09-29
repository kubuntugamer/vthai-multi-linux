#ifndef VTHAI_FONT_H
#define VTHAI_FONT_H

#include <stdint.h>

void assemble_8x16_cell(const uint8_t* upper_tile, const uint8_t* lower_tile, uint8_t* out_16_byte_cell);
void render_debug_cell(const uint8_t* cell_16_bytes);

#endif // VTHAI_FONT_H
