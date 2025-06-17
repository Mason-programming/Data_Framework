#!/usr/bin/env python3
import sys
from pxr import Usd, UsdGeom

def create_usd_scene(output_path, assets):
    stage = Usd.Stage.CreateNew(output_path)
    UsdGeom.SetStageUpAxis(stage, UsdGeom.Tokens.y)

    root = UsdGeom.Xform.Define(stage, "/World")

    for idx, name in enumerate(assets):
        asset_path = f"assets/{name}/index.usda"
        prim_path = f"/World/{name}"
        xform = UsdGeom.Xform.Define(stage, prim_path)
        xform.AddTranslateOp().Set((idx * 2.0, 0, 0))
        xform.GetPrim().GetReferences().AddReference(asset_path)

    stage.GetRootLayer().Save()
    print(f"Created USD scene: {output_path}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: create_shot asset1 [asset2 ...]")
        sys.exit(1)

    asset_names = sys.argv[1:]
    create_usd_scene("shot.usda", asset_names)