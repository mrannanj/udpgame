#!/bin/bash

set -x

function linux_before_install() {
  sudo add-apt-repository ppa:sonkun/sfml-development -y
  sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
  sudo add-apt-repository ppa:h-rayflood/llvm -y
  sudo apt-get update -qq
  if [ "${CXX}" = "g++" ]; then
    sudo apt-get install -qq g++-4.8
    export CXX="g++-4.8"
  elif [ "${CXX}" = "clang++" ]; then
    sudo apt-get install -qq llvm-3.4 clang-3.4 libclang-3.4-dev \
      llvm-3.4-dev libc++-dev
    export CXX="clang++-3.4"
  fi
  sudo apt-get install -qq libglew-dev libsdl-image1.2-dev libglm-dev \
    libprotobuf-dev protobuf-compiler libsfml libsfml-dev
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
  brew install pkg-config protobuf glm sdl sdl_image glew sfml
}

UNAME=$(uname -s)
if [ ${UNAME} == "Linux" ]; then
  linux_before_install
elif [ ${UNAME} == "Darwin" ]; then
  osx_before_install
fi

set +x
