# VTHAI Multi-Linux Core Translation Framework

Modern Linux port of the 1990 real-mode DOS visual rendering engine, handling text parsing and bitmap fonts.

## Code Build Automation Instructions

Use the standardized Makefile rules:

```bash
make run    # Launch interactive app
make clean  # Clean compiled object maps
```

## Automated Quality Assurance Validation Tests

Run pre-baked cross-generation layout matrices:

```bash
make test_v300  # Test modern v3.00 sequential single-plane TIS-620 layout stacking
```
