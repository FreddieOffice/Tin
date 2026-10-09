project "Tin"
    location "%{wks.location}/%{prj.name}"
    objdir ("%{wks.location}/obj/%{prj.name}/"..outputdir)
    targetdir ("%{wks.location}/bin/%{prj.name}/"..outputdir)

    kind "StaticLib"

    includedirs {
        "include",
        "include/Vendor",
    }

    libdirs {
        "lib"
    }

    links {
        "opengl32",
        "glfw3_mt"
    }

    files {
        "include/**.h",
        "include/**.hpp",
        "include/**.inl",
        "src/**.c",
        "src/**.cpp"
    }

    -- Precompiled headers
    pchheader "Tin/TinPCH.hpp"
    pchsource "src/Tin/TinPCH.cpp"

    filter "files:src/vendor/**.cpp"
        flags {"NoPCH"}

    filter "files:src/vendor/**.c"
        flags {"NoPCH"}

    filter {}

    -- Global Defines
    defines {"GLFW_INCLUDE_NONE", "GLM_ENABLE_EXPERIMENTAL"}

    -- Windows defines
    filter "system:Windows"
        defines {"NOMINMAX", "WIN32_LEAN_AND_MEAN"}

    filter {}

    -- Configurations
    filter {"configurations:Debug"}
        symbols "On"
        staticruntime "Off"

    filter {"configurations:Release"}
        optimize "Speed"
        staticruntime "On"

    filter {}