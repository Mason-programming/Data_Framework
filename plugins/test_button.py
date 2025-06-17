
import bpy
class MyOperator(bpy.types.Operator):
    bl_idname = "object.my_operator"
    bl_label = "My Operator"
    def execute(self, context):
        print("Executing MyOperator")
        return {'FINISHED'}

def menu_func(self, context):
    self.layout.operator(MyOperator.bl_idname)