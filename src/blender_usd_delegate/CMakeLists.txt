
add_executable(blender_usd_node
        blender_usd_delegate.cpp
        blender_node_main.cpp
)

target_link_libraries(blender_usd_node PRIVATE
        usd
        usdGeom
        usdLux
        sdf
        tf
        gf
        ar
        usdUtils
)

target_link_libraries(blender_usd_node PRIVATE OpenSubdiv::osdCPU_static OpenSubdiv::osdGPU_static OpenSubdiv::OpenSubdiv_static)