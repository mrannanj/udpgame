# udpgame

![Screenshot](https://raw.github.com/mrannanj/udpgame/master/doc/udpgame.png
"Screenshot")

### Ubuntu deps

```
sudo apt-get install libglew-dev libsdl-image1.2-dev libglm-dev libprotobuf-dev protobuf-compiler
```

### Ubuntu PPA

```
sudo add-apt-repository ppa:mrannanj/udpgame
sudo apt-get update
sudo apt-get install udpgame
```

### Compile on OS X

First, [install Homebrew](http://brew.sh).

```
brew install gcc48
sudo rm -f /usr/bin/c++ /usr/bin/g++ /usr/bin/clang++
sudo ln -s /usr/local/bin/g++-4.8 /usr/local/bin/c++
sudo ln -s /usr/local/bin/g++-4.8 /usr/local/bin/g++
sudo ln -s /usr/local/bin/g++-4.8 /usr/local/bin/clang++
brew install pkg-config protobuf glm sdl sdl_image glew
make
```
