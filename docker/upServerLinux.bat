@ECHO OFF

echo ------------- Build and Run docker DevLinux container -----------
docker compose -f docker-compose.yml -f ./serverLinux/docker-compose.serverLinux.yml up mofip-serverlinux -d
echo ------------- docker DevLinux has been running -----------
