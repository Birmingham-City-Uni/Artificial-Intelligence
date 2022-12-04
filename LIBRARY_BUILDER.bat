set working_dir=%~dp0
set library_binaries=%working_dir%library_binaries

echo Creating Home for libs
cd %working_dir%
if not exist "library_binaries" mkdir library_binaries
pause 

echo Installing SDL
cd external\sdl-2.24.2
if not exist "build" mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release -S ./../ -B "x64"
cmake --build x64 --config Release --parallel
cmake --install x64 --prefix %library_binaries% --config Release 
cd ../../..
echo SDL Installed
pause

echo Installing SDL_Image
cd external\sdl-image-2.6.2
if not exist "build" mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release -S ./../ -B "x64" -DCMAKE_PREFIX_PATH=%library_binaries%
cmake --build x64 --config Release --parallel
cmake --install x64 --prefix %library_binaries% --config Release 
cd ../../..
echo SDL_Image Installed
pause

echo Installing SDL_Mixer
cd external\sdl-mixer-2.6.2
if not exist "build" mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release -S ./../ -B "x64" -DCMAKE_PREFIX_PATH=%library_binaries%
cmake --build x64 --config Release --parallel
cmake --install x64 --prefix %library_binaries% --config Release 
cd ../../..
echo SDL_Mixer Installed
pause

echo Installing SDL_TTF
cd external\sdl-ttf-2.20.1
if not exist "build" mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release -S ./../ -B "x64" -DCMAKE_PREFIX_PATH=%library_binaries%
cmake --build x64 --config Release --parallel
cmake --install x64 --prefix %library_binaries% --config Release 
cd ../../..
echo SDL_TTF Installed
echo Everything is installed
pause