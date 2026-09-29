#include <iostream>
#include <vector>
#include "vthai_engine.h"
#include "vthai_font.h"

void run_phase1_test() {
    VThaiCursorState cursor = {0, 0, LAYER_BASELINE};
    // Mock input data stream containing both standard ASCII and Thai language ranges
    std::vector<uint8_t> stream = {0x41, 0xA1, 0xD4, 0xE8, 0xA2};
    
    std::cout << "\n--- Executing Phase 1: State Processing & Translation Telemetry ---" << std::endl;
    std::cout << "Initial Position: Col 0, Row 0\n" << std::endl;
    
    for (size_t i = 0; i < stream.size(); ++i) {
        uint8_t raw_byte = stream[i];
        uint8_t translated_byte = translate_char_code(raw_byte);
        uint16_t old_col = cursor.current_col;
        
        process_vthai_step(raw_byte, &cursor);
        
        std::cout << "Step [" << i << "] - Raw Input: 0x" << std::hex << (int)raw_byte 
                  << " -> Engine Mapping: 0x" << (int)translated_byte << std::dec
                  << " -> Position: Col " << cursor.current_col;
                  
        if (cursor.current_col == old_col) {
            std::cout << " (Cursor Frozen / Character Stacked)" << std::endl;
        } else {
            std::cout << " (Cursor Advanced)" << std::endl;
        }
    }
    std::cout << "\nPhase 1 Complete. Traveled " << cursor.current_col << " cells." << std::endl;
}

void run_phase2_test() {
    std::cout << "\n--- Executing Phase 2: Font Tile Reconstruction ---" << std::endl;
    uint8_t upper_mock_tile[] = { 0x3c, 0x42, 0x99, 0xa5, 0xa6, 0x98, 0x42, 0x3c };
    uint8_t lower_mock_tile[] = { 0x18, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42 };
    uint8_t output_16_byte_cell[16] = {0};
    
    assemble_8x16_cell(upper_mock_tile, lower_mock_tile, output_16_byte_cell);
    render_debug_cell(output_16_byte_cell);
    std::cout << "Phase 2 Font Matrix Assembly Complete." << std::endl;
}

int main() {
    int choice = 0;
    while (true) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  VTHAI MULTI-LINUX INTERACTIVE SUITE   " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Run Phase 1 (Translation & State Engine Test)" << std::endl;
        std::cout << "2. Run Phase 2 (8x16 Font Renderer Test)" << std::endl;
        std::cout << "3. Exit Testing Suite" << std::endl;
        std::cout << "Enter selection (1-3): ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }
        
        if (choice == 1) {
            run_phase1_test();
        } else if (choice == 2) {
            run_phase2_test();
        } else if (choice == 3) {
            std::cout << "Exiting testing suite. Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Unknown selection. Please choose 1, 2, or 3." << std::endl;
        }
    }
    return 0;
}
