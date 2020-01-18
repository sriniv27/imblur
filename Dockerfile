# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the Clang compiler
RUN apt-get -y install clang cmake libboost-all-dev libopencv-dev

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . /usr/src/screen-locker
COPY screenshot.png /usr/src/screen-locker
# Specify the working directory
WORKDIR /usr/src/screen-locker
RUN mkdir -p build
RUN cmake --build build 

# Use Clang to compile the Test.cpp source file


# Run the output program from the previous step


LABEL Name=screen-locker Version=0.0.1
