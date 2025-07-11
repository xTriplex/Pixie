workspace "PixieEngine"
    architecture "x64"
    startproject "Sandbox"

    configurations { "Debug", "Release", "Dist" }

-- Output directories
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root
IncludeDir = {}
IncludeDir["GLFW"]    = "PixieEngine/Vendor/GLFW/include"
IncludeDir["GLAD"]    = "PixieEngine/Vendor/GLAD/include"
IncludeDir["IMGUI"]   = "PixieEngine/Vendor/ImGui"
IncludeDir["GLM"]     = "PixieEngine/Vendor/GLM"
IncludeDir["spdlog"]  = "PixieEngine/Vendor/SPDLOG/include"
IncludeDir["STB"]     = "PixieEngine/Vendor/STB"
IncludeDir["YamlCPP"] = "PixieEngine/Vendor/YamlCPP/include"
IncludeDir["OPENAL"]  = "PixieEngine/Vendor/OpenAL/include"
IncludeDir["BOX2D"]   = "PixieEngine/Vendor/BOX2D"
IncludeDir["TRACY"]   = "PixieEngine/Vendor/TRACY/public"

-- Group external dependencies
group "Dependencies"
    include "PixieEngine/Vendor/GLFW"
    include "PixieEngine/Vendor/GLAD"
    include "PixieEngine/Vendor/ImGui"
    include "PixieEngine/Vendor/YamlCPP"
    include "PixieEngine/Vendor/BOX2D"
    include "PixieEngine/Vendor/TRACY"
group ""

--
-- PixieEngine Library
--
project "PixieEngine"
    location "PixieEngine"
    kind     "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    dependson { "BOX2D" }

    targetdir ("bin/"     .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ppch.h"
    pchsource "PixieEngine/Source/ppch.cpp"

    files {
        "PixieEngine/Source/**.h",
        "PixieEngine/Source/**.cpp",
       
        "PixieEngine/Shaders/**.vert",
        "PixieEngine/Shaders/**.frag",
        "PixieEngine/Shaders/**.glsl"
    }

    -- disable PCH for stb_image
    filter "files:PixieEngine/Vendor/STB/stb_image.cpp"
        flags { "NoPCH" }
    filter {}

    -- exclude shader files from build
    filter "files:PixieEngine/Shaders/**"
        flags { "ExcludeFromBuild" }
    filter {}

    includedirs {
        "PixieEngine/Source",
        "PixieEngine/Source/Public",
        "PixieEngine/Source/Private",
        IncludeDir.GLFW,
        IncludeDir.GLAD,
        IncludeDir.IMGUI,
        IncludeDir.GLM,
        IncludeDir.spdlog,
        IncludeDir.STB,
        IncludeDir.YamlCPP,
        IncludeDir.OPENAL,
        IncludeDir.BOX2D,
        IncludeDir.TRACY
    }

    links {
        "GLFW",
        "GLAD",
        "ImGui",
        "YamlCPP",
        "BOX2D",
        "TRACY",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        defines {
            "PX_PLATFORM_WINDOWS",
            "PX_BUILD_STATIC",
            "GLFW_INCLUDE_NONE"
        }
        buildoptions "/utf-8"
    filter {}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        optimize "Off"
    filter {}

    filter "configurations:Release"
    runtime "Release"
    symbols "On"
    optimize "Speed"
    inlining "Auto"
    linktimeoptimization "On"
    buildoptions { "/arch:AVX2", "/fp:fast" }
    removebuildoptions { "/fp:precise" }
filter {}

filter "configurations:Dist"
    runtime "Release"
    symbols "Off"
    optimize "Speed"
    inlining "Auto"
    linktimeoptimization "On"
    buildoptions { "/arch:AVX2", "/fp:fast" }
    removebuildoptions { "/fp:precise" }
filter {}

--
-- Sandbox Application
--
project "Sandbox"
    location "Sandbox"
    kind     "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/"     .. outputdir .. "/%{prj.name}")
    objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "Sandbox/Source/**.h",
        "Sandbox/Source/**.cpp"
    }

    includedirs {
        "PixieEngine/Source/Public",
        "Sandbox/Source/Public",
        IncludeDir.GLFW,
        IncludeDir.GLAD,
        IncludeDir.IMGUI,
        IncludeDir.GLM,
        IncludeDir.spdlog,
        IncludeDir.STB
    }

    links {
        "PixieEngine",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "PX_PLATFORM_WINDOWS" }
        buildoptions "/utf-8"
        postbuildcommands {
            '{COPY} "%{wks.location}/Sandbox/Content" "%{cfg.targetdir}/Content"',
            '{COPYDIR} "%{wks.location}/PixieEngine/Shaders" "%{cfg.targetdir}/Shaders"'
        }
    filter {}

    filter "configurations:Debug"
        runtime   "Debug"
        symbols   "On"
        optimize "Off"
    filter {}

    filter "configurations:Release"
        runtime   "Release"
        symbols   "On"
        optimize "Speed"
        inlining "Auto"
        linktimeoptimization "On"
        buildoptions { "/arch:AVX2", "/fp:fast" }
    filter {}

    filter "configurations:Dist"
        runtime   "Release"
        symbols "Off"
        optimize "Speed"
        inlining "Auto"
        linktimeoptimization "On"
        buildoptions { "/arch:AVX2", "/fp:fast" }
    filter {}
