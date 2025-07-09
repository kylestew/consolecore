#!/bin/bash

echo "Obra Music Tracker - Build Test"
echo "================================"

# Check if make is available
if ! command -v make &> /dev/null; then
    echo "❌ Error: 'make' is not installed"
    echo "Please install build tools first"
    exit 1
fi

# Check if gcc is available
if ! command -v gcc &> /dev/null; then
    echo "❌ Error: 'gcc' is not installed"
    echo "Please install a C compiler first"
    exit 1
fi

echo "✅ Build tools found"

# Try to build the project
echo "Building Obra..."
if make clean && make; then
    echo "✅ Build successful!"
    echo ""
    echo "To run Obra, you'll need some WAV sample files."
    echo "Example usage:"
    echo "  ./obra samples/kick.wav samples/snare.wav samples/hihat.wav"
    echo ""
    echo "You can create a samples directory with:"
    echo "  make samples"
    echo ""
    echo "For help with dependencies, run:"
    echo "  make help"
else
    echo "❌ Build failed!"
    echo ""
    echo "This usually means missing dependencies."
    echo "Try installing them first:"
    echo ""
    echo "macOS:"
    echo "  make install-deps"
    echo ""
    echo "Ubuntu/Debian:"
    echo "  make install-deps-ubuntu"
    echo ""
    echo "For more help, run:"
    echo "  make help"
    exit 1
fi 