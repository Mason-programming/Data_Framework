import bpy
import sys
import os

# Safe path setup
current_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.abspath(os.path.join(current_dir, "..", ".."))
src_dir = os.path.join(project_root, "src")
plugins_dir = os.path.join(project_root, "plugins")

# Insert to sys.path
for path in [src_dir, project_root, plugins_dir]:
    if path not in sys.path:
        sys.path.insert(0, path)

# Pull in PYTHONPATH if provided
env_paths = os.environ.get("PYTHONPATH", "")
for path in env_paths.split(":"):
    if path and path not in sys.path:
        sys.path.insert(0, path)

# Debug sys.path
print("🔍 sys.path inside Blender:")
for p in sys.path:
    print(p)

# Register plugin
try:
    from plugins.custome_blender import register
    register()
except Exception as e:
    print(f"❌ Plugin registration failed: {e}")

# Import USD file if set
usd_file = os.environ.get("USD_FILE_PATH")
if usd_file and os.path.exists(usd_file):
    print(f"📥 Importing USD: {usd_file}")
    bpy.ops.wm.usd_import(filepath=usd_file)
