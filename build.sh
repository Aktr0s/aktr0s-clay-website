#!/bin/bash

# Get LLVM path from Homebrew
LLVM_BIN="$(brew --prefix llvm)/bin/clang"

# Ensure build directory exists
mkdir -p build

# Compile to WebAssembly
"$LLVM_BIN" \
    -Wall \
    -Werror \
    -Os \
    -DCLAY_WASM \
    -mbulk-memory \
    --target=wasm32 \
    -nostdlib \
    -Wl,--strip-all \
    -Wl,--export-dynamic \
    -Wl,--no-entry \
    -Wl,--export=__heap_base \
    -Wl,--export=ACTIVE_RENDERER_INDEX \
    -Wl,--initial-memory=6553600 \
    -o build/index.wasm \
    main.c && \
cp index.html build/index.html && \
cp -r fonts/ build/fonts && \
cp -r images/ build/images
