# Screen-locker
**Pipeline status -- master**![.github/workflows/ci-script.yml](https://github.com/sriniv27/imblur/workflows/.github/workflows/ci-script.yml/badge.svg?branch=master)

**pipeline status -- development**![.github/workflows/ci-script.yml](https://github.com/sriniv27/imblur/workflows/.github/workflows/ci-script.yml/badge.svg?branch=development)

An incredibly heavy implementation of a program to take a screencap, blur it, and lock the session using said image as the lockscreen background. 

The core program is outlined in main.cpp and provides the imblur executable. 
## Installation

```
$ git clone https://gitlab.com/sugas182/screen-locker.git screen-locker
$ cd screen-locker/ 
$ cmake -B build 
$ cmake --build build --target all -- -j4 
$ cmake --install build
```

## Dependencies
1) `imlib2` to use the `imlib2_grab` function. Any drop-in replacement should be fine. We just need the image. 
2) `i3lock` or similar screen-locker that can accept an image to be used as background. See [`screen-lock`](./screen-lock) and replace `i3lock` with its associated syntax with your screen locker of choice.
3) See [Dockerfile](./Dockerfile) for a minimal ubuntu installation example.
    - This project requires the following packages:
        - boost : `apt install libboost-all-dev`
        - OpenCV: `apt install libopencv-dev` 

![build dependency graph](xml/deps.png)


# This Project Uses: 

[spdlog](https://github.com/gabime/spdlog): A **fast**  c++ logging library. Install using your [package manager](https://github.com/gabime/spdlog#package-managers).

