# Build Ubuntu image with base functionality.
FROM --platform=linux/amd64 ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# Setup the default user.
RUN echo 'root:root' | chpasswd \
    && adduser devlinux \
    && usermod -aG sudo devlinux \
    && echo 'devlinux:devlinux' | chpasswd

# Install required tools.
RUN apt-get -qq update \
    && apt-get -qq --no-install-recommends install -y git \
    && apt-get -qq --no-install-recommends install vim \
    && apt-get -qq --no-install-recommends install build-essential \
    && apt-get -qq --no-install-recommends install cmake \
    && apt-get -qq --no-install-recommends install openssh-server \
    && apt-get -qq --no-install-recommends install iputils-ping \
    && apt-get -qq --no-install-recommends install net-tools \
    && apt-get -qq --no-install-recommends install sudo \
    && apt-get -qq clean \
    && rm -rf /var/lib/apt/lists/*

USER root
RUN sed -i "s@.*PermitRootLogin.*prohibit.*@PermitRootLogin = without-password@g" /etc/ssh/sshd_config \
    && sed -i "s@.*PasswordAuthentication yes@PasswordAuthentication no@g" /etc/ssh/sshd_config \
    && sed -i "s@.*UsePAM yes@UsePAM no@g" /etc/ssh/sshd_config

EXPOSE 22

USER devlinux

RUN mkdir /home/devlinux/jenkins
WORKDIR /home/devlinux/jenkins

ENTRYPOINT echo 'devlinux' | sudo -S service ssh start && bash
