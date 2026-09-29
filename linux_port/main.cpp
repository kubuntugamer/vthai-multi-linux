#include <iostream>
#include <vector>
#include "vthai_engine.h"

int main() {
    VThaiCursorState cursor = {0, 0, LAYER_BASELINE};
    
    // Mock data stream containing a mix of standard baseline letters and stacking codes
    std::vector<uint8_t> stream = {
        0x41,  // 'A' (Standard Baseline)
        0xA1,  // Thai baseline character (Advances cursor)
        0xD4,  // Thai upper vowel (Stacks - Freezes cursor)
        0xE8,  // Thai tone marker  (Stacks - Freezes cursor)
        0xA2   // Thai baseline character (Advances cursor)
    };
    
    std::cout << "Starting VTHAI State Processing Telemetry Loop..." << std::endl;
    std::cout << "Initial Position: Col " << cursor.current_col << ", Row " << cursor.current_row << "\n" << std::endl;
    
    for (size_t i = 0; i < stream.size(); ++i) {
        uint8_t byte = stream[i];
        uint16_t old_col = cursor.current_col;
        
        process_vthai_step(byte, &cursor);
        
        std::cout << "Step [" << i << "] - Processing Byte: 0x" << std::hex << (int)byte << std::dec;
        std::cout << " -> Active Canvas Position: Col " << cursor.current_col;
        
        if (cursor.current_col == old_col) {
            std::cout << " (Cursor Frozen / Character Stacked)" << std::endl;
        } else {
            std::cout << " (Cursor Advanced)" << std::endl;
        }
    }
    
    std::cout << "\nFinal Layout Metrics: Traveled " << cursor.current_col << " character cells widthwise." << std::endl;
    return 0;
}
