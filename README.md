# VTHAI Multi-Linux Core Translation Framework

This directory houses the modern Linux port of the 1990 real-mode DOS visual rendering engine. It handles text parsing, vertical keyboard tracking matrices, and multi-layer 8x16 bitmap font generation.

## Code Build Automation Instructions

To wipe previous compilation binaries, build optimized object layers, and run the main interactive suite, use the standardized Makefile rules:

```bash
# Clean out target directory and immediately launch the interactive app
make run

# Clean up all compiled intermediate object maps and test suites
make clean
```

## Runtime Component Infrastructure Overview

The test application includes five isolated routines to test the driver components:

1. **Phase 1 (State Engine Loop):** Tracks cursor coordinate matrices, automatically checking if an incoming byte advances column positioning widthwise or freezes it for stacking.
2. **Phase 2 (Font Tile Extraction):** Dynamically parses individual 8x8 bitmap fragments out of the `2.00/THAI.COM` asset library and stitches them into full 16-row layout cells.
3. **Bulk Map Export (Path A):** Sweeps the entire uncompressed graphics sector from the binary and outputs all character indices to `full_font_set.txt`.
4. **Multi-Line Screen Buffer (Path B):** Intercepts control delimiters like newlines to wrap layout arrays downward across clean horizontal text grid rows.

## Advanced Terminal Command-Line Modifiers

You can bypass the menu panels entirely to parse custom tokens directly from your command-line terminal line:

```bash
# Direct Hex Streaming Mode
./vthai_suite 0xA1 0xD4

# File Ingestion Parsing Mode
./vthai_suite -f filename.txt
```
