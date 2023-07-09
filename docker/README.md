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

## Setting environment for build and run application

# Manual run all containers:
- upJenkins.bat
- upDevLinux.bat
- upLocalDevlinux.bat
- upServerLinux.bat
# Autorun all containers:
- upAllContainers.bat

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
   - GitHub Integration

# Configure Publish over SSH
1. Install and copy ssh keys
   - Copy from mofip-jenkins </var/jenkins_home/.ssh/ssh_host_rsa_key> to jenkins-web key or set path to key
   - Copy from mofip-jenkins contant of file </var/jenkins_home/.ssh/ssh_host_rsa_key.pub> to mofip-devlinux
      </home/devlinux/.ssh/authorized_keys>. Create </home/devlinux/.ssh/authorized_keys> befor copy
2. Open <Manage/Jenkins/System> and go to <Publish over SSH>
   - add Key:
      - Key: copy private key from console if you run <upAllContainers.bat> or run <jenkinsKeys.bat>
         for obtain those keys. 
      - Passphrase: set passphrase if you need.
   - add SSH Server:
      - Name: devlinux
      - Hostname: mofip-devlinux
      - Username: devlinux
      - Remote Directory: </home/devlinux/jenkins>

# Add node for compile project in mofip-devlinux container
1. Go to <Nodes/buildlinux/Configure>
2. Name: buildlinux
3. Number of executors: 2
4. Remote root directory: </home/devlinux/jenkins>
5. Labels: ubuntu ubuntu20
6. Launch method: Launch agents via SSH
   - Host: mofip-devlinux
   - Credentials: choos from <Publish over SSH> <devlinux>
   - Host Key Verification Strategy: Manually trusted key Verification Strategy

