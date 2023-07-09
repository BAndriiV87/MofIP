START /B /WAIT cmd /c "upJenkins.bat"
start http://localhost:8080
START /B /WAIT cmd /c "upDevLinux.bat"
START /B /WAIT cmd /c "upLocalDevLinux.bat"
START /B /WAIT cmd /c "upServerLinux.bat"
START /B /WAIT cmd /c "jenkinsKeys.bat"
