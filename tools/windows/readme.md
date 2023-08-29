## Manual configurating environment
# Configure console environment  
    Set environment for find qt's dll for run qt gui part. Run <config.bat>.
# Config MS Visual Studio
    - go to GUI target option project: 
        Properties | Debugging | Environment
    - Fill the empty field to:
        PATH=%PATH%;c:/Qt/5.15.2/msvc2019_64/bin;c:\Qt\5.15.2\msvc2019_64\plugins;$(LocalDebuggerEnvironment)
