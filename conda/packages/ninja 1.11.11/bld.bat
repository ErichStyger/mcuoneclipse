xcopy /S "%SRC_DIR%\ninja*" "%LIBRARY_PREFIX%"
echo "bat done"
if errorlevel 1 exit 1