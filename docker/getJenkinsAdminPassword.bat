@ECHO OFF

echo ------------------ Jenkins credentials ------------------
set command=docker exec mofip-jenkins cat /var/jenkins_home/secrets/initialAdminPassword

for /F "tokens=* USEBACKQ" %%F in (`%command%`) do (SET var=%%F)

echo RUN Jenkins using next URL:    http://localhost:8080/
echo Jenkins Admin password:        %var%
echo ------------------ Jenkins credentials -------------------
