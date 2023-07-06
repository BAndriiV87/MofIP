FROM  --platform=linux/amd64 jenkins/jenkins:2.401.1

ENV DEBIAN_FRONTEND noninteractive

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

USER root

# Setup the default user.
RUN echo 'root:root' | chpasswd \
    && echo 'jenkins:jenkins' | chpasswd

RUN apt-get update && apt-get install -y lsb-release

RUN curl -fsSLo /usr/share/keyrings/docker-archive-keyring.asc \
  https://download.docker.com/linux/debian/gpg

RUN echo "deb [arch=$(dpkg --print-architecture) \
  signed-by=/usr/share/keyrings/docker-archive-keyring.asc] \
  https://download.docker.com/linux/debian \
  $(lsb_release -cs) stable" > /etc/apt/sources.list.d/docker.list

RUN apt-get update && apt-get install -y docker-ce-cli

USER jenkins

ARG work_data_path
ENV DATA_PATH=$work_data_path

RUN ssh-keygen -q -N "" -t dsa -f $DATA_PATH/.ssh/ssh_host_dsa_key \
    && ssh-keygen -q -N "" -t rsa -b 4096 -f $DATA_PATH/.ssh/ssh_host_rsa_key \
    && ssh-keygen -q -N "" -t ecdsa -f $DATA_PATH/.ssh/ssh_host_ecdsa_key \
    && ssh-keygen -q -N "" -t ed25519 -f $DATA_PATH/.ssh/ssh_host_ed25519_key

RUN jenkins-plugin-cli --plugins "blueocean docker-workflow"

WORKDIR $DATA_PATH
