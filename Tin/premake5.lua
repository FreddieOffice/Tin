project "Tin"
    location "%{wks.location}/%{prj.name}"
    objdir ("%{wks.location}/obj/%{prj.name}/"..outputdir)
    targetdir ("%{wks.location}/bin/%{prj.name}/"..outputdir)

    kind "StaticLib"

    defines {"GLM_ENABLE_EXPERIMENTAL", "GLFW_INCLUDE_NONE", "NOMINMAX"}

    includedirs {
        "include",
        "include/Vendor",
        "include/Vendor/SOIL2"
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

    -- Configurations
    filter {"configurations:Debug"}
        symbols "On"
        staticruntime "Off"

    filter {"configurations:Release"}
        optimize "On"
        staticruntime "On"

    filter {}