#!/bin/sh

# Build the lot (in ../dist)

sudo ./build_debian_package.sh i386 10
sudo ./build_debian_package.sh amd64 10
sudo ./build_debian_package.sh armhf 10