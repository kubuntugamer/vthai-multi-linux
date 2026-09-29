#include <iostream>
#include "vthai_font.h"

int main() {
    std::cout << "Starting VTHAI Phase 2 Font Reconstruction Test..." << std::endl;
    
    // Sample mock 8x8 cell byte data arrays extracted from the binary maps
    uint8_t upper_mock_tile[8] = { 0x3c, 0x42, 0x99, 0xa5, 0xa6, 0x98, 0x42, 0x3c }; // Index 127
    uint8_t lower_mock_tile[8] = { 0x18, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42 }; // Index 90
    
    uint8_t output_16_byte_cell[16] = {0};
    
    // Assemble the two discrete halves into a cohesive 16-row layout block
    assemble_8x16_cell(upper_mock_tile, lower_mock_tile, output_16_byte_cell);
    
    // Render the final stitched graphic visualization matrix
    render_debug_cell(output_16_byte_cell);
    
    return 0;
}
