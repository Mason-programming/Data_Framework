#!/bin/bash

echo "🎛️ Welcome to the Custom USD Bridge Shell"
export USD_MODE=1
export DCC_CONTEXT="blender"

# Define custom aliases
alias launchdcc="echo Launching DCC: \$DCC_CONTEXT"
alias usdupdate="echo Watching for USD changes..."
alias="~/Destop/USD_Bridge"

# Drop into subshell
bash --rcfile <(cat ~/.bashrc; declare -f; echo "PS1='[usd-bridge] \$PS1'")
