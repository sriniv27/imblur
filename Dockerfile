# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
# Update apps on the base image
RUN apt-get -y update && apt-get install -y

RUN apt-get install -y apt-transport-https ca-certificates gnupg software-properties-common wget
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | apt-key add -
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
RUN apt-get update
# Install the Clang compiler
RUN apt-get install -f
RUN apt-get -y install clang cmake libboost-all-dev libopencv-dev

# Copy the current folder which contains C++ source code to the Docker image under /usr/src

COPY screenshot.png screenshot.png
# Specify the working directory



# Use Clang to compile the Test.cpp source file


# Run the output program from the previous step


LABEL Name=screen-locker Version=0.0.1
