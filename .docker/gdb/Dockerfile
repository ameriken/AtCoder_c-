FROM ubuntu:18.04

RUN apt update \
	&& apt upgrade -y \
	&& apt install -y \
	apt-utils build-essential clang gdb gdbserver openssh-server rsync vim wget libssl-dev software-properties-common software-properties-common

RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get install -y gcc-7 g++-7 gcc-8 g++-8 gcc-9 g++-9
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9 --slave /usr/bin/gcov gcov /usr/bin/gcov-9
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 80 --slave /usr/bin/g++ g++ /usr/bin/g++-8 --slave /usr/bin/gcov gcov /usr/bin/gcov-8
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 70 --slave /usr/bin/g++ g++ /usr/bin/g++-7 --slave /usr/bin/gcov gcov /usr/bin/gcov-7
RUN update-alternatives --config gcc


RUN mkdir -p /tmp/
COPY cmake-3.16.6.tar.gz  /tmp/

RUN cd /tmp     && \
    tar -zxvf cmake-3.16.6.tar.gz           && \
    cd /tmp/cmake-3.16.6                    && \
    ./bootstrap                             && \
    make install

RUN ln -snf /usr/local/bin/cmake /usr/bin/

# Taken from - https://docs.docker.com/engine/examples/running_ssh_service/#environment-variables
RUN mkdir /var/run/sshd
RUN echo 'root:root' | chpasswd
RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile

# 22 for ssh server. 7777 for gdb server.
EXPOSE 22 7777

# Create dev user with password 'dev'
RUN useradd -ms /bin/bash gdbdebug
RUN echo 'gdbdebug:gdbdebug' | chpasswd
WORKDIR  /home/gdbdebug

# Upon start, run ssh daemon
CMD ["/usr/sbin/sshd", "-D"]
