project "googletest"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir (binaries)
    objdir (intermediate)

    files {
        "src/gmock-all.cc",
        "src/gtest-all.cc",
    }

    includedirs {
        ".",
        "include"
    }

    toolset "clang"

    filter "system:windows"
        systemversion "latest"
        staticruntime "Off"

    filter "system:linux"
        staticruntime "Off"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "Full"
        runtime "Release"
        symbols "Off"
