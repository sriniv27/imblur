# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
# Update apps on the base imageRUN apt-get install software-properties-common -y

RUN apt-get -y update && apt-get install -y
RUN apt-get install software-properties-common -y
RUN apt-get update
RUN apt-get install -y apt-transport-https ca-certificates gnupg software-properties-common wget
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | apt-key add -
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
RUN apt-get update
# Install the Clang compiler
RUN apt-get install -f
RUN apt-get -y install clang cmake libboost-all-dev libopencv-dev graphviz doxygen git zip libspdlog-dev openssh-client

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . /usr/src/screen-locker/

LABEL Name=screen-locker Version=1.0
