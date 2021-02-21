#!/bin/bash

set -x

sudo apt-get update -qq
sudo apt-get install -qq libglew-dev libsdl-image1.2-dev libglm-dev \
  libprotobuf-dev protobuf-compiler libfreetype-dev
