@ECHO OFF

echo ------------------------------
for /F %%i in ('docker ps -aq') do docker rm -f %%i
for /F %%i in ('docker images -q') do docker rmi %%i
for /F %%i in ('docker volume ls -q') do docker volume rm %%i
for /F %%i in ('docker network ls -q') do docker network rm %%i
docker system prune -a
echo ------------------------------
docker ps -a
docker images
docker volume ls
docker network ls
echo ------------------------------
