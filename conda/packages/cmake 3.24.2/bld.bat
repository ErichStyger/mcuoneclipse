xcopy /S "%SRC_DIR%\*.*" "%LIBRARY_PREFIX%"
echo "bat done"
if errorlevel 1 exit 1