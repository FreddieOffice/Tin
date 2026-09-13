project "Sandbox"
    location "%{wks.location}/%{prj.name}"
    objdir ("%{wks.location}/obj/%{prj.name}/"..outputdir)
    targetdir ("%{wks.location}/bin/%{prj.name}/"..outputdir)

    kind "ConsoleApp"

    includedirs {
        "include/",
        "include/imgui",
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
        "src/**.cpp"
    }

    -- Configurations
    filter {"configurations:Debug"}
        symbols "On"
        staticruntime "Off"

    filter {"configurations:Release"}
        optimize "On"
        staticruntime "On"

    filter {}
    
    -- Platforms
    filter {"platforms:x64"}
        system "Windows"
        architecture "x86_64"

    filter {}