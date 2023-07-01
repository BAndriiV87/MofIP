@ECHO OFF

echo ------------- Build and Run docker DevLinux container -----------
docker compose -f docker-compose.yml -f docker-compose.docker-devLinux.yml up mofip-devlinux -d
echo ------------- docker DevLinux has been running -----------
