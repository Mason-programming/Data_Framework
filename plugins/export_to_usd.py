import os
import bpy
import sys
from pxr import Usd, UsdGeom, Sdf

# Absolute path to the src directory
repo_root = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))


from src.bridge_scripts.sessionManager import sessionManager

class ExportToUsd:
    def __init__(self):
        self.session = sessionManager()
        self.stage = self.session.get_current_stage()
        self.root_path = f"/Users/masonkirby/Desktop/Assets"  # Change as needed

    def _get_asset_paths(self, asset_name, purpose, fragment):
        base = os.path.join(self.root_path, asset_name)
        purpose_dir = os.path.join(base, purpose)
        fragment_dir = os.path.join(purpose_dir, fragment)
        data_dir = os.path.join(fragment_dir, "data")
        os.makedirs(data_dir, exist_ok=True)
        return {
            "asset_root": base,
            "purpose_dir": purpose_dir,
            "fragment_dir": fragment_dir,
            "data_dir": data_dir,
            "payload": os.path.join(fragment_dir, "payload.usda"),
            "fragment_index": os.path.join(fragment_dir, "index.usda"),
            "purpose_index": os.path.join(purpose_dir, "index.usda"),
            "asset_index": os.path.join(base, "index.usda"),
        }
    def export_model_fragment(self, asset_name="tree", purpose="render"):
        paths = self._get_asset_paths(asset_name, purpose, "model")

        # Export the geometry
        stage = self.stage
        UsdGeom.Xform.Define(stage, "/root")
        # NOTE: Ideally, you’d export selected objects from Blender here
        stage.Save()

        # Fragment index references the payload
        frag_stage = Usd.Stage.CreateNew(paths["fragment_index"])
        frag_stage.GetRootLayer().subLayerPaths.append("payload.usda")
        frag_stage.Save()

        # Purpose index composes fragments
        if not os.path.exists(paths["purpose_index"]):
            purpose_stage = Usd.Stage.CreateNew(paths["purpose_index"])
            purpose_stage.GetRootLayer().subLayerPaths.append("model/index.usda")
            purpose_stage.Save()

        # Asset index references render/proxy
        if not os.path.exists(paths["asset_index"]):
            asset_stage = Usd.Stage.CreateNew(paths["asset_index"])
            for p in ["render", "proxy"]:
                asset_stage.DefinePrim(f"/{p}", "Xform")
                asset_stage.GetRootLayer().subLayerPaths.append(f"{p}/index.usda")
            asset_stage.Save()
