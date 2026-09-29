#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "vthai_engine.h"
#include "vthai_font.h"

// Track the globally active driver binary location
std::string global_bin_path = "2.00/THAI.COM";

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
    std::cout << "Target Binary: " << global_bin_path << std::endl;
    uint8_t upper[8] = {0}, lower[8] = {0}, cell[16] = {0};
    if (!load_raw_font_tile(global_bin_path, 95, upper) || !load_raw_font_tile(global_bin_path, 97, lower)) return;
    assemble_8x16_cell(upper, lower, cell);
    render_debug_cell(cell);
}

void run_bulk_export() {
    std::cout << "\n--- Executing Bulk Font Map Asset Generation ---" << std::endl;
    std::string out_path = "linux_port/full_font_set.txt";
    if (export_full_font_set(global_bin_path, out_path)) {
        std::cout << "Success! Entire character directory dumped to: " << out_path << std::endl;
    } else {
        std::cout << "Error: Failed to export font directory files from " << global_bin_path << std::endl;
    }
}

void process_and_render_stream(const std::vector<uint8_t>& stream) {
    VThaiScreenBuffer buffer;
    buffer.max_cols = 40;
    buffer.max_rows = 4;
    buffer.grid.resize(buffer.max_rows);

    process_stream_to_buffer(stream, buffer);

    std::cout << "\n--- Generating Multi-Line Display Grid Canvas Preview (Source: " << global_bin_path << ") ---" << std::endl;
    for (uint16_t r = 0; r < buffer.max_rows; ++r) {
        if (buffer.grid[r].empty()) continue;
        std::cout << "\n--- Display Canvas Layout Row [" << r << "] ---" << std::endl;
        render_horizontal_line(global_bin_path, buffer.grid[r]);
    }
}

int main(int argc, char* argv[]) {
    std::vector<uint8_t> target_stream;
    
    // Parse runtime command-line configurations
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        
        // Handle Dynamic Version Flag: -v [path]
        if (arg == "-v" && i + 1 < argc) {
            global_bin_path = argv[++i];
            continue;
        }
        
        // Handle File Ingestion Flag: -f [filename]
        if (arg == "-f" && i + 1 < argc) {
            std::string file_target = argv[++i];
            std::cout << "Streaming File Data Input Target: " << file_target << std::endl;
            if (load_input_file_stream(file_target, target_stream)) {
                process_and_render_stream(target_stream);
                return 0;
            } else {
                std::cout << "Error: Could not process text document source file." << std::endl;
                return 1;
            }
        }
        
        // Fallback: Treat loose arguments as hex data tokens
        unsigned int byte_val;
        std::stringstream ss;
        if (arg.substr(0, 2) == "0x" || arg.substr(0, 2) == "0X") ss << std::hex << arg.substr(2);
        else ss << std::hex << arg;
        if (ss >> byte_val) target_stream.push_back(static_cast<uint8_t>(byte_val));
    }

    if (!target_stream.empty()) {
        process_and_render_stream(target_stream);
        return 0;
    }

    int choice = 0;
    while (true) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "  VTHAI MULTI-LINUX INTERACTIVE SUITE   " << std::endl;
        std::cout << "  Active Version: " << global_bin_path << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Run Phase 1 (Translation & State Engine Test)" << std::endl;
        std::cout << "2. Run Phase 2 (Live 8x16 Font Renderer Test)" << std::endl;
        std::cout << "3. Execute Bulk Character Font Map Export" << std::endl;
        std::cout << "4. Run Multi-Line Screen Buffer Test" << std::endl;
        std::cout << "5. Exit Testing Suite" << std::endl;
        std::cout << "Enter selection (1-5): ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 1) run_phase1_test();
        else if (choice == 2) run_phase2_test();
        else if (choice == 3) run_bulk_export();
        else if (choice == 4) {
            std::vector<uint8_t> mock = {0xA1, 0xD4, 0xE8, 0xA2, 0xD9, 0x42};
            process_and_render_stream(mock);
        }
        else if (choice == 5) break;
    }
    return 0;
}
