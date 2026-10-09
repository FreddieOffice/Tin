workspace "Tin"
    configurations {"Debug", "Release"}

    platforms {"x64"}
    architecture "x86_64"

    exceptionhandling "Off"
    rtti "Off"

    language "C++"
    cppdialect "C++17"
 
    location "build"
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    include "Tin"

    include "Editor"