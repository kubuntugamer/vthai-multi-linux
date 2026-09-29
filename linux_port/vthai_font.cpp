#include "vthai_font.h"
#include <iostream>
#include <fstream>

void assemble_8x16_cell(const uint8_t* upper_tile, const uint8_t* lower_tile, uint8_t* out_16_byte_cell) {
    for (int i = 0; i < 8; ++i) out_16_byte_cell[i] = upper_tile[i];
    for (int i = 0; i < 8; ++i) out_16_byte_cell[i + 8] = lower_tile[i];
}

void render_debug_cell(const uint8_t* cell_16_bytes) {
    std::cout << "\n+--------+" << std::endl;
    for (int row = 0; row < 16; ++row) {
        std::cout << "|";
        for (int bit = 7; bit >= 0; --bit) {
            std::cout << (((cell_16_bytes[row] >> bit) & 1) ? '#' : ' ');
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+--------+" << std::endl;
}

bool load_raw_font_tile(const std::string& filepath, uint16_t tile_index, uint8_t* out_8_byte_tile) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) return false;
    std::streamoff target_offset = 0x0500 + (tile_index * 8);
    file.seekg(target_offset, std::ios::beg);
    return (bool)file.read(reinterpret_cast<char*>(out_8_byte_tile), 8);
}

bool export_full_font_set(const std::string& bin_path, const std::string& out_text_path) {
    std::ofstream out(out_text_path);
    if (!out.is_open()) return false;
    out << "VTHAI COMPREHENSIVE 8x16 CHARACTER FONT DIRECTORY\n\n";
    for (int i = 0; i < 256; i += 2) {
        uint8_t upper[8] = {0}, lower[8] = {0}, cell[16] = {0};
        load_raw_font_tile(bin_path, i, upper);
        load_raw_font_tile(bin_path, i + 1, lower);
        assemble_8x16_cell(upper, lower, cell);
        out << "Character Slot Index: " << (i / 2) << "\n+--------+\n";
        for (int row = 0; row < 16; ++row) {
            out << "|";
            for (int bit = 7; bit >= 0; --bit) out << (((cell[row] >> bit) & 1) ? '#' : ' ');
            out << "|\n";
        }
        out << "+--------+\n\n";
    }
    return true;
}

void render_horizontal_line(const std::string& bin_path, const std::vector<VThaiScreenCell>& line_buffer) {
    std::vector<std::vector<uint8_t>> constructed_cells(line_buffer.size(), std::vector<uint8_t>(16, 0));
    
    // Pre-assemble all 16-byte character matrix blocks for the current string
    for (size_t col = 0; col < line_buffer.size(); ++col) {
        const auto& cell = line_buffer[col];
        uint8_t upper[8] = {0}, lower[8] = {0}, combined[16] = {0};
        
        load_raw_font_tile(bin_path, cell.baseline_code, upper);
        load_raw_font_tile(bin_path, cell.baseline_code + 1, lower);
        
        if (cell.upper_vowel_code != 0) {
            uint8_t vowel[8] = {0};
            load_raw_font_tile(bin_path, cell.upper_vowel_code, vowel);
            for(int r=0; r<8; ++r) upper[r] |= vowel[r];
        }
        if (cell.tone_mark_code != 0) {
            uint8_t tone[8] = {0};
            load_raw_font_tile(bin_path, cell.tone_mark_code, tone);
            for(int r=0; r<8; ++r) upper[r] |= tone[r];
        }
        if (cell.lower_vowel_code != 0) {
            uint8_t sub[8] = {0};
            load_raw_font_tile(bin_path, cell.lower_vowel_code, sub);
            for(int r=0; r<8; ++r) lower[r] |= sub[r];
        }
        
        assemble_8x16_cell(upper, lower, combined);
        for(int r=0; r<16; ++r) constructed_cells[col][r] = combined[r];
    }
    
    // Print row-by-row across all horizontal cell blocks simultaneously
    std::cout << "\nHorizontal Line String Visualization Layout:" << std::endl;
    for (int row = 0; row < 16; ++row) {
        for (size_t col = 0; col < constructed_cells.size(); ++col) {
            for (int bit = 7; bit >= 0; --bit) {
                std::cout << (((constructed_cells[col][row] >> bit) & 1) ? '#' : ' ');
            }
        }
        std::cout << std::endl;
    }
}
