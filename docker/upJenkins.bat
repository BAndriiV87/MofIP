@ECHO OFF

echo ------------- Build and Run docker Jenkins container -----------
docker compose -f docker-compose.yml -f ./jenkins/docker-compose.docker-jenkins.yml up mofip-docker-dind mofip-jenkins -d
echo RUN Jenkins using next URL: http://localhost:8080/
echo ------------- docker Jenkins has been running -----------
