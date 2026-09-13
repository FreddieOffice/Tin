@echo off

:: Copy assets into the sandbox build directory so it can build in visual studio
if not exist "build\Sandbox\assets" (
    mkdir build\Sandbox\assets
    xcopy /Q /E /Y /I Sandbox\assets build\Sandbox\assets
)

:: Build
premake5 vs2022