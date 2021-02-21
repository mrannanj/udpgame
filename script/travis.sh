#!/bin/bash

set -x

function linux_before_install() {
  sudo apt-get update -qq
  sudo apt-get install -qq libglew-dev libsdl-image1.2-dev libglm-dev \
    libprotobuf-dev protobuf-compiler
}

function osx_before_install() {
  GCC_ML_BOTTLE="gcc48-4.8.2.mountain_lion.bottle.tar.gz"
  brew tap homebrew/versions
  brew update
  wget "http://www.cs.helsinki.fi/u/mrannanj/${GCC_ML_BOTTLE}" \
    -O "$(brew --cache)/${GCC_ML_BOTTLE}"
  brew install "$(brew --cache)/${GCC_ML_BOTTLE}"
  sudo rm -f /usr/bin/g++ /usr/bin/clang++ /usr/bin/c++
  sudo ln -s /usr/local/bin/g++-4.8 /usr/bin/c++
  sudo ln -s /usr/local/bin/g++-4.8 /usr/bin/g++
  sudo ln -s /usr/local/bin/g++-4.8 /usr/bin/clang++
  brew install pkg-config protobuf glm sdl sdl_image glew
}

UNAME=$(uname -s)
if [ ${UNAME} == "Linux" ]; then
  linux_before_install
elif [ ${UNAME} == "Darwin" ]; then
  osx_before_install
fi

set +x
