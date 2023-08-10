@ECHO OFF

::SET /P COLOR="Choose a background color (type red, blue or black): " - interactive input

:: User variables:
set buildpath=%cd%\..\..\build

:: Project variables
set projectrootpath=%cd%\..\..\

:: ===========================================
IF NOT "%1"=="" (
    IF "%1"=="--config" (
        :: Create project build path
        IF EXIST %buildpath% (
            CALL :logStatus The build path "%buildpath%" has already exist
        ) ELSE (
            CALL :logStatus Create the build path "%buildpath%"
            mkdir %buildpath%
        )
        ::Configure cmake project
        CALL :logStatus Configure project
        :: For getting console debug information unlock line below
        ::set QT_DEBUG_PLUGINS=1
        cmake -G "Visual Studio 17 2022" -A "x64" -B %buildpath% -S %projectrootpath%
    )
    IF "%1"=="--build" (
        IF NOT EXIST %buildpath% (
            CALL :logWarning The build directory doesn't exist.
            CALL :logHint Configure cmake project using next command: build --config
        ) ELSE (
            cmake --build %buildpath%
        )
    )
    IF "%1"=="--clear" (
        IF EXIST %buildpath% (
            CALL :logStatus Remove directory: %buildpath%
            rmdir /s /q %buildpath%
        ) ELSE (
            CALL :logWarning The directory has already removed
        )
    )
    SHIFT
) ELSE (
    echo Usage: build.bat [option]
    echo Options:
    echo    --build     - build project
    echo    --config    - create build directory and configure project
    echo    --clear     - clear build directory
    echo usage buildwin.bat [command-parameter]
)

goto :EOF

:: Function block
:logHint
    echo [HINT]    : %*
EXIT /B 0
:logError
    echo [ERROR]   : %*
EXIT /B 0
:logWarning
    echo [WARNING] : %*
EXIT /B 0
:logStatus
    echo [STATUS]  : %*
EXIT /B 0

:: End of batch script
:EOF
