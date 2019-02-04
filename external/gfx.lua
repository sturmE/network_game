project "RenderBackend"
    kind "StaticLib"
    language "C++"
    targetdir "lib"

    files {
        "gfx/src/**.cpp",
        "gfx/src/**.h",
    }

    filter "configurations:release"
        flags { "LinkTimeOptimization" }

    filter "system:windows"
        characterset "MBCS" -- oops

        libdirs { "external/winlibs/%{cfg.platform}" }
        links { 
            "d3d11",
            "d3dcompiler",
            "DXGI",
            "dxguid",
        }

    filter "system:macosx"
        buildoptions { "-x objective-c++"}
        links { 
            "Metal.framework",
            "QuartzCore.framework",
            "Cocoa.framework",
        }
        files { "gfx/src/**.mm" }
        removefiles { "gfx/src/**/dx11/**"}