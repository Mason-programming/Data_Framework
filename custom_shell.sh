#!/bin/bash

echo "🎛️ Welcome to the Custom USD Bridge Shell"
export USD_MODE=1
export DCC_CONTEXT="blender"

# Define custom aliases
#!/bin/bash

# Set up environment variables for your USD Bridge project
export USD_BRIDGE_DIR=~/Desktop/USD_Bridge
export PYTHONPATH="$USD_BRIDGE_DIR/modules:$PYTHONPATH"
export USD_PLUGIN_PATH="$USD_BRIDGE_DIR/plugins"

# Optional: Add the doBlender script to your PATH if not already
export PATH="$USD_BRIDGE_DIR/bin:$PATH"

# Create an alias for easy access
alias doBlender="python3 $USD_BRIDGE_DIR/bin/doBlender.py"

# (Optional) Make sure the script is executable
chmod +x "$USD_BRIDGE_DIR/bin/doBlender.py"

echo "✅ USD Bridge shell ready. Run: doBlender"


# Drop into subshell
bash --rcfile <(cat ~/.bashrc; declare -f; echo "PS1='[usd-bridge] \$PS1'")
