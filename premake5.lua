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
    group ""

project "dirtycommon"
    kind "SharedLib"
    language "C++"
    targetdir "bin"

    sysincludedirs {
    }

    includedirs {
        "src/common/**"
    }

    files {
        "src/common/**.cpp",
        "src/common/**.h",
    }

project "dirtyclient"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin"

    filter "system:macosx"
       buildoptions {"-F ../external/SFML-2.5.1-macos-clang/Frameworks"}
       linkoptions  {"-F ../external/SFML-2.5.1-macos-clang/Frameworks"}
       buildoptions {"-F ../external/SFML-2.5.1-macos-clang/extlibs"}
       linkoptions  {"-F ../external/SFML-2.5.1-macos-clang/extlibs"}
       links {
            "dirtycommon",
            "enet",
            "SFML.framework",
            "sfml-graphics.framework",
            "sfml-window.framework",
            "sfml-system.framework",
            "FLAC.framework",
            "freetype.framework",
            "ogg.framework",
            "OpenAL.framework",
            "vorbis.framework",
            "vorbisenc.framework",
            "vorbisfile.framework",
        }

    sysincludedirs {
        "external/SFML-2.5.1-macos-clang/include",
        "external/enet/include",
        "external/json/single_include/nlohmann",
    }

    includedirs {
        "src/common",
        "src/client/**"
    }

    files {
        "src/client/**.cpp",
        "src/client/**.h",
    }

project "dirtyserver"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin"

    filter "system:macosx"
       links {
            "dirtycommon",
            "enet",
        }

    sysincludedirs {
        "external/enet/include",
        "external/json/single_include/nlohmann",        
    }

    includedirs {
        "src/common",
        "src/server/**"
    }

    files {
        "src/server/**.cpp",
        "src/server/**.h",
    }