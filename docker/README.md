## FOR WINDOWS HOST MACHINE
===========================

# Berfor execute instractions below you need setup next tools:
1. Docker engine on local machine
2. Java 8 or higher

# What each container must do
1. mofip-jenkins. Folder jenkins. It's local jenkins server.
   Build image and run container. Execute <upJenkins.bat>
2. mofip-devlinux. Folder devLinux. This container needs to compile application and 
   obtain server application executer. Build server and deploy to test environment. 
   Build image and run container. Execute <upDevLinux.bat>
3. mofip-localdevlinux. It's duplicat of <mofip-devlinux> for local build without Jenkins.
   Share local <app> directory to </app> in docker for build application

# Run docker Jenkins:
1. Run <upDockerJenkins.bat>
2. Use URL and run Jenkins server from browser
3. Get admin password running <getJenkinsAdminPassword.bat>
4. Insert password to browser that opened in stage (2) for activated Jenkins server
5. Install suggested plugins
6. Start using Jenkins
7. Plugins need install:
   - in begining of use Jenkins install offers plugins
   - Publish Over SSH
   - SSH Agent

# How connect ssh Jenkins to devlinux container
1. Copy from mofip-jenkins </var/jenkins_home/.ssh/ssh_host_rsa_key> to jenkins-web key or set path to key
2. Set hostname <mofip-jenkins>. It's docker network for jenkins and devlinux containers
3. Copy from mofip-jenkins contant of file </var/jenkins_home/.ssh/ssh_host_rsa_key.pub> to mofip-devlinux
   </home/devlinux/.ssh/authorized_keys>. Create </home/devlinux/.ssh/authorized_keys> befor copy
4. Set "Remote Directory" in Jenkins </home/devlinux/jenkins>
4. Set user <devlinux> and network <mofip-devlinux>
