import bpy
import json
import importlib

import os

def get_json():
    current_dir = os.path.dirname(os.path.abspath(__file__))
    json_path = os.path.join(current_dir, "what_to_run.json")

    with open(json_path, "r") as json_file:
        return json.load(json_file)

# Register classes dynamically
def launch_commands(command_list):
    for item in command_list:
        module_path = item["module"]
        class_name = item["class"]
        try:
            module = importlib.import_module(module_path)
            clazz = getattr(module, class_name)
            bpy.utils.register_class(clazz)
            LOADED_CLASSES.append(clazz)
            print(f"✅ Registered: {module_path}.{class_name}")
        except Exception as e:
            print(f"❌ Failed to register {module_path}.{class_name}:\n{e}")

# Custom panel that adds buttons for dynamically loaded operators
class DynamicPanel(bpy.types.Panel):
    bl_idname = "VIEW3D_PT_dynamic_panel"
    bl_label = "Custom Tools"
    bl_space_type = "VIEW_3D"
    bl_region_type = "UI"
    bl_category = "My Tools"

    def draw(self, context):
        layout = self.layout
        for cls in LOADED_CLASSES:
            if hasattr(cls, "bl_idname"):
                layout.operator(cls.bl_idname)

# Globals to track dynamically registered classes
LOADED_CLASSES = []

# Register everything
def register():
    command_list = get_json()
    launch_commands(command_list)
    bpy.utils.register_class(DynamicPanel)

# Unregister everything cleanly
def unregister():
    for cls in reversed(LOADED_CLASSES):
        try:
            bpy.utils.unregister_class(cls)
        except Exception as e:
            print(f"Error unregistering {cls}: {e}")
    LOADED_CLASSES.clear()
    bpy.utils.unregister_class(DynamicPanel)

