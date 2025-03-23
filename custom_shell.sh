#!/bin/bash


# Run in a subshell to avoid modifying current shell env
(
    export PS1="USD Shell& "

    echo "We need to add a path to consume the USD library" 
    USDLIBRARY_PATH="$HOME/Documents/"
    PXR_PATH= ""

    if [ -f "$USDLIBRARY_PATH"]; then 
        echo "Welcome to the USD Bridge!!!"
        chmod +x "$USDLIBRARY_PATH" 
    else 
        echo "Could not find the path of a functional USD Library" 
    fi 

    echo "🛠️ Setting up USD Bridge tools..."
    # USD Bridge Paths
    USD_BRIDGE_DIR="$HOME/Desktop/USD_Bridge/bin"
    DOBLENDER_PATH="$USD_BRIDGE_DIR/doblender"
    DOUNREAL_PATH="$USD_BRIDGE_DIR/dounreal"

    # Setup doblender
    echo "⚙️ Setting up 'doblender'..."
    if [ ! -f "$DOBLENDER_PATH" ]; then
        echo "🚨 Error: doblender script not found at $DOBLENDER_PATH"
    else
        chmod +x "$DOBLENDER_PATH"
        echo "✅ Made doblender executable"

        if [ ! -L /usr/local/bin/doblender ]; then
            echo "🔗 Creating symlink to /usr/local/bin/doblender..."
            sudo ln -s "$DOBLENDER_PATH" /usr/local/bin/doblender
        else
            echo "ℹ️ 'doblender' symlink already exists"
        fi
    fi

    # Setup dounreal
    echo "⚙️ Setting up 'dounreal'..."
    if [ ! -f "$DOUNREAL_PATH" ]; then
        echo "🚨 Error: dounreal script not found at $DOUNREAL_PATH"
    else
        chmod +x "$DOUNREAL_PATH"
        echo "✅ Made dounreal executable"

        if [ ! -L /usr/local/bin/dounreal ]; then
            echo "🔗 Creating symlink to /usr/local/bin/dounreal..."
            sudo ln -s "$DOUNREAL_PATH" /usr/local/bin/dounreal
        else
            echo "ℹ️ 'dounreal' symlink already exists"
        fi
    fi

    my_leave(){
    echo "Good bye" 
    exit 
    }

    echo "🎉 Setup complete! You can now use 'doblender' and 'dounreal' from any terminal."
    exec bash --noprofile --norc -i

)
