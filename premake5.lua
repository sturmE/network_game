workspace "dirty"
    startproject "dirtyjam"
    location "build"
    configurations { "debug", "release" }
    platforms { "x32", "x64" }

    vectorextensions "SSE2"

    filter "platforms:x32"
        architecture "x86"
    filter "platforms:x64"
        architecture "x86_64"

    filter "configurations:debug"
        runtime "Debug"
        optimize "Debug"
        symbols "On"
        targetsuffix "d"
        defines { 
            "_DEBUG"
        }
    filter "configurations:release"
        runtime "Release"
        optimize "On"
        symbols "On"
        defines { "NDEBUG" }

    filter "system:windows"
        defines { "_WINDOWS", "WIN32" }
    -- optimization levels in debug running debug stepping
    filter { "configurations:debug", "system:macosx" }
        xcodebuildsettings {['GCC_OPTIMIZATION_LEVEL'] = 0}
    filter {}

    cppdialect "C++17"
    xcodebuildsettings {['CLANG_CXX_LANGUAGE_STANDARD'] = 'c++17'}

    group "external"
        include "external/enet.lua"
        include "external/sdl2.lua"
        include "external/gfx.lua"
    group ""

project "dirtycommon"
    kind "SharedLib"
    language "C++"
    targetdir "bin"


    filter "system:macosx"
       links {
            "dirtycommon",
            "enet",
        }

    sysincludedirs {
        "external/enet/include",
    }
    
    includedirs {
        "src/common/**"
    }

    files {
        "src/common/**.cpp",
        "src/common/**.h",
        "src/common/**.hpp",
    }


project "dirtyclient"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin"

    filter "system:macosx"
       links {
            "dirtycommon",
            "enet",
            "SDL2",
            "RenderBackend",
        }

    sysincludedirs {
        "external/enet/include",
        "external/SDL-mirror/include",
        "external/gfx/src/**"

    }

    includedirs {
        "src/common",
        "src/client/**"
    }

    buildoptions { "-x objective-c++"}
        links { 
            "Metal.framework",
            "QuartzCore.framework",
            "Cocoa.framework",
        }

    files {
        "src/client/**.cpp",
        "src/client/**.h",
        "src/client/**.hpp",
    }

project "dirtyserver"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin"

    filter "system:macosx"
       links {
            "dirtycommon",
            "enet",
            "sqlite3",
        }

    sysincludedirs {
        "external/enet/include",
        "external/rapidjson/include",
        "external/sqlite3pp/headeronly_src/"
    }

    includedirs {
        "src/common",
        "src/server/**"
    }

    files {
        "src/server/**.cpp",
        "src/server/**.h",
        "src/server/**.hpp",
    }
