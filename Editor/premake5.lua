project "Editor"
    location "%{wks.location}/%{prj.name}"
    objdir ("%{wks.location}/obj/%{prj.name}/"..outputdir)
    targetdir ("%{wks.location}/bin/%{prj.name}/"..outputdir)

    kind "ConsoleApp"

    includedirs {
        "include/",
        "include/Editor/",
        "include/Vendor/",
        "include/Vendor/imgui",
        "../Tin/include",
        "../Tin/include/vendor"
    }

    links {
        "opengl32",
        "Tin"
    }

    files {
        "include/**.h",
        "include/**.hpp",
        "src/**.cpp",
        "assets/**.*"
    }

    -- Global Defines
    defines {"GLM_ENABLE_EXPERIMENTAL"}

    -- Configurations
    filter {"configurations:Debug"}
        symbols "On"
        staticruntime "Off"

    filter {"configurations:Release"}
        optimize "Speed"
        staticruntime "On"

    filter {}
    
    -- Platforms
    filter {"platforms:x64"}
        architecture "x86_64"

    filter {}