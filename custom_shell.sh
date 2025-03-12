#!/bin/zsh

# Full path to your bin directory
BRIDGE_PATH="$HOME/Desktop/USD_Bridge/bin"
DOBLENDER_SCRIPT="$BRIDGE_PATH/doBlender.py"
TARGET="$BRIDGE_PATH/doblender"

echo "🔧 Setting up your USD Bridge CLI..."

# Rename script if it's still doBlender.py
if [ -f "$DOBLENDER_SCRIPT" ]; then
    mv "$DOBLENDER_SCRIPT" "$TARGET"
    echo "✅ Renamed doBlender.py → doblender"
fi

# Make it executable
chmod +x "$TARGET"
echo "✅ Made doblender executable"

# Check if bin path is already in .zshrc
if ! grep -q "$BRIDGE_PATH" ~/.zshrc; then
    echo "🔗 Adding $BRIDGE_PATH to PATH in ~/.zshrc"
    echo "\n# USD Bridge custom CLI" >> ~/.zshrc
    echo "export PATH=\"\$PATH:$BRIDGE_PATH\"" >> ~/.zshrc
    echo "✅ PATH updated in ~/.zshrc"
else
    echo "📌 Path already exists in ~/.zshrc"
fi

# Source .zshrc to update current session
source ~/.zshrc
hash -r

echo "🎉 You're ready to use \`doblender\` from any directory!"
