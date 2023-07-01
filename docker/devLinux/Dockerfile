FROM --platform=amd64 ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install \
    git \
    build-essential \
    iputils-ping \
    net-tools \
    cmake -y

RUN useradd -ms /bin/bash dev && mkdir /home/dev/jenkins
USER dev
WORKDIR /home/dev

CMD [ "/bin/bash" ]
