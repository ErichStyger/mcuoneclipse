del build.ninja .ninja_deps .ninja_log >nul 2>nul
del CMakeCache.txt cmake_install.cmake >nul 2>nul
del compile_commands.json >nul 2>nul
rmdir /S /Q build 
