-- Workspace level Premake Configuration
workspace "containers"
    configurations {
        "Debug",
        "Release"
    }

    architecture "x64"

    filter "configurations:Debug"
        runtime "Debug"
    
    filter "configurations:Release"
        runtime "Release"
    
    sln = solution()
    binaries = "%{sln.location}/bin/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"
    intermediate = "%{sln.location}/bin-int/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

    -- Dependencies
    include "dependencies/googletest"

    -- Projects
    include "projects/containers"
    include "projects/test"

    -- Include Directories
    IncludeDir = {}
    IncludeDir["containers"] = "%{sln.location}/projects/containers/include"
    IncludeDir["gtest"] = "%{sln.location}/dependencies/googletest/include"