#include "vthai_font.h"
#include <iostream>
#include <fstream>

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
    std::streamoff target_offset = 0x0500 + (tile_index * 8);
    file.seekg(target_offset, std::ios::beg);
    return (bool)file.read(reinterpret_cast<char*>(out_8_byte_tile), 8);
}

bool export_full_font_set(const std::string& bin_path, const std::string& out_text_path) {
    std::ofstream out(out_text_path);
    if (!out.is_open()) return false;

    out << "VTHAI COMPREHENSIVE 8x16 CHARACTER FONT DIRECTORY\n";
    out << "=================================================\n\n";

    // Loop through all 256 characters, pairing adjacent 8x8 memory slots
    for (int i = 0; i < 256; i += 2) {
        uint8_t upper[8] = {0};
        uint8_t lower[8] = {0};
        uint8_t cell[16] = {0};

        load_raw_font_tile(bin_path, i, upper);
        load_raw_font_tile(bin_path, i + 1, lower);
        assemble_8x16_cell(upper, lower, cell);

        out << "Character Slot Index: " << (i / 2) << " (Upper Tile: " << i << ", Lower Tile: " << (i + 1) << ")\n";
        out << "+--------+\n";
        for (int row = 0; row < 16; ++row) {
            out << "|";
            for (int bit = 7; bit >= 0; --bit) {
                out << (((cell[row] >> bit) & 1) ? '#' : ' ');
            }
            out << "|\n";
        }
        out << "+--------+\n\n";
    }
    return true;
}
