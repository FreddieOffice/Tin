@echo off

:: Copy assets into the editor build directory so it can build in visual studio
mkdir build\Editor\assets
xcopy /Q /E /Y /I Editor\assets build\Editor\assets

:: Build
premake5 vs2022