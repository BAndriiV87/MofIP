@ECHO OFF

:: Print public key mofip-jenkins
echo ==========
echo PUBLIC KEY
echo ==========
set command=docker exec mofip-jenkins cat /var/jenkins_home/.ssh/ssh_host_rsa_key.pub
for /F "tokens=* USEBACKQ" %%F in (`%command%`) do (
    echo %%F
)

:: Print private key mofip-jenkins
echo ===========
echo PRIVATE KEY
echo ===========
set command=docker exec mofip-jenkins cat /var/jenkins_home/.ssh/ssh_host_rsa_key
for /F "tokens=* USEBACKQ" %%F in (`%command%`) do (
    echo %%F
)

:: Print Jenkin's Admin password
echo ==============
echo ADMIN PASSWORD 
echo ==============
set command=docker exec mofip-jenkins cat /var/jenkins_home/secrets/initialAdminPassword
for /F "tokens=* USEBACKQ" %%F in (`%command%`) do (SET var=%%F)
echo RUN Jenkins using next URL:    http://localhost:8080/
echo Jenkins Admin password:        %var%
