#include <iostream>
#include <vector>
#include "vthai_engine.h"
#include "vthai_font.h"

void run_phase1_test() {
    VThaiCursorState cursor = {0, 0, LAYER_BASELINE};
    std::vector<uint8_t> stream = {0x41, 0xA1, 0xD4, 0xE8, 0xA2};
    std::cout << "\n--- Executing Phase 1: State Processing & Translation Telemetry ---\n" << std::endl;
    for (size_t i = 0; i < stream.size(); ++i) {
        uint8_t raw_byte = stream[i];
        uint8_t translated_byte = translate_char_code(raw_byte);
        uint16_t old_col = cursor.current_col;
        process_vthai_step(raw_byte, &cursor);
        std::cout << "Step [" << i << "] - Raw Input: 0x" << std::hex << (int)raw_byte 
                  << " -> Engine Mapping: 0x" << (int)translated_byte << std::dec
                  << " -> Position: Col " << cursor.current_col;
        if (cursor.current_col == old_col) std::cout << " (Cursor Frozen / Character Stacked)" << std::endl;
        else std::cout << " (Cursor Advanced)" << std::endl;
    }
}

void run_phase2_test() {
    std::cout << "\n--- Executing Phase 2: Live Font Tile Extraction ---" << std::endl;
    std::string bin_path = "2.00/THAI.COM";
    uint8_t upper[8], lower[8], cell[16];
    if (!load_raw_font_tile(bin_path, 95, upper) || !load_raw_font_tile(bin_path, 97, lower)) return;
    assemble_8x16_cell(upper, lower, cell);
    render_debug_cell(cell);
}

void run_bulk_export() {
    std::cout << "\n--- Executing Bulk Font Map Asset Generation ---" << std::endl;
    std::string bin_path = "2.00/THAI.COM";
    std::string out_path = "linux_port/full_font_set.txt";
    if (export_full_font_set(bin_path, out_path)) {
        std::cout << "Success! Entire 256-character font directory dumped to: " << out_path << std::endl;
    } else {
        std::cout << "Error: Failed to export font directory files." << std::endl;
    }
}

int main() {
    int choice = 0;
    while (true) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  VTHAI MULTI-LINUX INTERACTIVE SUITE   " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Run Phase 1 (Translation & State Engine Test)" << std::endl;
        std::cout << "2. Run Phase 2 (Live 8x16 Font Renderer Test)" << std::endl;
        std::cout << "3. Execute Bulk Character Font Map Export (Path A)" << std::endl;
        std::cout << "4. Exit Testing Suite" << std::endl;
        std::cout << "Enter selection (1-4): ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 1) run_phase1_test();
        else if (choice == 2) run_phase2_test();
        else if (choice == 3) run_bulk_export();
        else if (choice == 4) break;
    }
    return 0;
}
