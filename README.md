lightberry
==========

Playing around with a Raspberry Pi and some Philips Hue Lights

# Go

[Install go from source](http://golang.org/doc/install/source) and then run:

    go run src/hue.go

# JavaScript

First, install nodejs and npm:

    sudo apt-get install nodejs npm

Then install the dependencies for the project:

    npm install

Finally, to run the lsupnp tool:

    nodejs src/lsupnp.js

# C++

To install the dependencies in raspbian, start with these apt packages:

    sudo apt-get install libgflags-dev libgflags2
    sudo apt-get install libasound2-dev libasound2
    sudo apt-get install libcurl4-openssl-dev
    sudo apt-get install libboost-dev

Install google-glog from https://code.google.com/p/google-glog/. You can use
any version probably. Best not to unzip this inside this project's directory.
You can do it anywhere.

    wget https://google-glog.googlecode.com/files/glog-0.3.3.tar.gz
    tar -xzvf glog-0.3.3.tar.gz
    cd glog-0.3.3
    ./configure --prefix=/usr
    make
    sudo make install

And finally, get the gtest source from apt, and then build it.

    sudo apt-get install libgtest-dev
    sudo apt-get install cmake
    cd /usr/src/gtest
    sudo cmake CMakeLists.txt
    sudo make
    sudo cp *.a /usr/lib

Now, to build all of the lightberry binaries, just do:

    make

