-- Test project level Premake Configuration
project "test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir (binaries)
    objdir (intermediate)

    dependson {
        "containers",
        "googletest"
    }

    links {
        "googletest"
    }

    includedirs  {
        "%{IncludeDir.containers}",
        "%{IncludeDir.gtest}"
    }

    files {
        "src/**.cpp"
    }

    toolset "clang"
    filter "system:windows"
        systemversion "latest"
        staticruntime "Off"

        postbuildcommands {
            "\"" .. binaries .. "\\test.exe\""
        }

    filter "system:linux"
        staticruntime "Off"

        buildoptions {
            "-fms-extensions"
        }

        links {
            "pthread"
        }

        postbuildcommands {
            "\"" .. binaries .. "/test\""
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "Full"
        runtime "Release"
        symbols "Off"