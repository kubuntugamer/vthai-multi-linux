#include <iostream>
#include <vector>
#include <stdint.h>

// Stitches two standalone 8x8 graphic tiles into a standard 8x16 font character cell
void assemble_8x16_cell(const uint8_t* upper_tile, const uint8_t* lower_tile, uint8_t* out_16_byte_cell) {
    // Top Half Assembly (Rows 0 to 7)
    for (int i = 0; i < 8; ++i) {
        out_16_byte_cell[i] = upper_tile[i];
    }
    // Bottom Half Assembly (Rows 8 to 15)
    for (int i = 0; i < 8; ++i) {
        out_16_byte_cell[i + 8] = lower_tile[i];
    }
}

// Verification function to print the reconstructed font cell cleanly into the shell
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
