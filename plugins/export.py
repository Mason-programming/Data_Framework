import bpy
from plugins.export_to_usd import ExportToUsd
class ExportAssetOperator(bpy.types.Operator):
    bl_idname = "export.asset_usd"
    bl_label = "Export Asset as USD Structure"

    def execute(self, context):
        exporter = ExportToUsd()
        exporter.export_model_fragment(asset_name="tree", purpose="render")
        return {'FINISHED'}

