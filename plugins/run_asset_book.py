import subprocess
import sys
import os
import bpy

# Get repo root → one level above /src and /plugins
current_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.abspath(os.path.join(current_dir, "..", ".."))

# Point directly to the folder that contains the "plugins" package
if project_root not in sys.path:
    sys.path.insert(0, project_root)

class AssetBookPlugin(bpy.types.Operator):
    bl_idname = "object.asset_book"
    bl_label = "Asset Book"

    def execute(self, context):
        try:
            script_path = "/Users/masonkirby/Desktop/Data_Framework/plugins/asset_book.py"
            subprocess.Popen([sys.executable, script_path])
            self.report({'INFO'}, "✅ Launched external Asset Book UI.")
            return {'FINISHED'}
        except Exception as e:
            self.report({'ERROR'}, str(e))
            return {'CANCELLED'}