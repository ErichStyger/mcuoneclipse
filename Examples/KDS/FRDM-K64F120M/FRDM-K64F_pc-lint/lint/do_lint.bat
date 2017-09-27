@rem call this batch file from the Eclipse project settings
@rem The arguments for this batch file: 
@rem %1: The path to the project root folder
@rem ------------------------------------------------------
@rem Path to the project folder
SET PROJ_PATH=%1

@rem Path to lint-nt.exe (NO SPACES!!!)
SET LINT_EXE=C:\nxp\lint\lint-nt.exe

@rem Path to my lint configuration files
SET LOCAL_LNT_FILES=C:\nxp\lint\lnt

@rem Path to my local lint folder inside the project with the lint files
SET PROJ_LINT_PATH=%PROJ_PATH%\lint

@rem Lint configuration files and includes
SET LNT_INCLUDES=-i"%PROJ_LINT_PATH%" -i%LOCAL_LNT_FILES%

@rem --------------- Run PC-lint ---------------------------
%LINT_EXE% %LNT_INCLUDES% %PROJ_LINT_PATH%\eclipse_msg.lnt %PROJ_LINT_PATH%\proj_options.lnt %PROJ_LINT_PATH%\proj_files.lnt -vf