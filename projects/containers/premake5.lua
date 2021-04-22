-- Containers project level Premake Configuration
project "containers"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir (binaries)
    objdir (intermediate)

    -- Header only
    files {
        "include/**.hpp"
    }

    includedirs {
        "include/"
    }
