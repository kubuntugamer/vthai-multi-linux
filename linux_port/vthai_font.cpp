#include <iostream>
#include <fstream>
#include "vthai_font.h"

void assemble_8x16_cell(const uint8_t* upper_tile, const uint8_t* lower_tile, uint8_t* out_16_byte_cell) {
    for (int i = 0; i < 8; ++i) {
        out_16_byte_cell[i] = upper_tile[i];
    }
    for (int i = 0; i < 8; ++i) {
        out_16_byte_cell[i + 8] = lower_tile[i];
    }
}

void render_debug_cell(const uint8_t* cell_16_bytes) {
    std::cout << "\nReconstructed 8x16 Console Asset Matrix:\n+--------+" << std::endl;
    for (int row = 0; row < 16; ++row) {
        std::cout << "|";
        for (int bit = 7; bit >= 0; --bit) {
            if ((cell_16_bytes[row] >> bit) & 1) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+--------+" << std::endl;
}

bool load_raw_font_tile(const std::string& filepath, uint16_t tile_index, uint8_t* out_8_byte_tile) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    // Calculate byte address offset: font arrays start exactly at 0x0500 inside the binary
    std::streamoff target_offset = 0x0500 + (tile_index * 8);
    
    file.seekg(target_offset, std::ios::beg);
    if (!file.read(reinterpret_cast<char*>(out_8_byte_tile), 8)) {
        return false;
    }
    
    return true;
}
