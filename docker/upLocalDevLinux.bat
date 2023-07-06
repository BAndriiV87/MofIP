@ECHO OFF

echo ------------- Build and Run docker DevLinux container -----------
docker compose -f docker-compose.yml up mofip-localdevlinux -d
echo ------------- docker DevLinux has been running -----------
