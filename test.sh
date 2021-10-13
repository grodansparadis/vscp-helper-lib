#!/bin/sh

case "$1" in
amd64)
    echo "Building for amd64"	
    BITS=64
    SUBFOLDER="x86_64-linux-gnu"
    ;;
i386)
    echo "Building for i386"	
    BITS=32
    SUBFOLDER="i386-linux-gnu"
    ;;
armhf)
    echo "Building for armhf"	
    BITS=32
    SUBFOLDER="arm-linux-gnueabihf"
    ;;
*
    echo "Building with discovery for installed system"
    ;;
esac

case "$2" in
"")
    echo "Using discovered COMPAT"	
    ;;  
*)
    echo "Setting COMPAT = $2"
    COMPAT="$2"
    ;;
esac


if [ "amd64" = "$1" ]; then
    echo "build amd64 things"

    if [ ! -d "/var/cache/pbuilder/debian-stretch-amd64/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/debian-stretch-amd64/aptcache/
        sudo OS=debian DIST=stretch ARCH=amd64 pbuilder --create
    fi
    sudo OS=debian DIST=stretch ARCH=amd64 pbuilder build *.dsc

    if [ ! -d "/var/cache/pbuilder/debian-buster-amd64/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/debian-buster-amd64/aptcache/
        sudo OS=debian DIST=buster ARCH=amd64 pbuilder --create
    fi
    sudo OS=debian DIST=buster ARCH=amd64 pbuilder build *.dsc

    if [ ! -d "/var/cache/pbuilder/ubuntu-bionic-amd64/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-bionic-amd64/aptcache/
        sudo OS=ubuntu DIST=bionic ARCH=amd64 pbuilder --create
    fi
    sudo OS=ubuntu DIST=bionic ARCH=amd64 pbuilder build *.dsc
    
    if [ ! -d "/var/cache/pbuilder/ubuntu-disco-amd64/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-disco-amd64/aptcache/
        sudo OS=ubuntu DIST=disco ARCH=amd64 pbuilder --create
    fi
    sudo OS=ubuntu DIST=disco ARCH=amd64 pbuilder build *.dsc

    if [ ! -d "/var/cache/pbuilder/ubuntu-disco-amd64/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-eoan-amd64/aptcache/
        sudo OS=ubuntu DIST=eoan ARCH=amd64 pbuilder --create
    fi
    sudo OS=ubuntu DIST=eoan ARCH=amd64 pbuilder build *.dsc
fi

if [ "i386" = "$1" ]; then
    echo "build i386 things"
    
    if [ ! -d "/var/cache/pbuilder/debian-stretch-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/debian-stretch-i386/aptcache/
        sudo OS=debian DIST=stretch ARCH=i386 pbuilder --create
    fi
    sudo OS=debian DIST=stretch ARCH=i386 pbuilder --create

    if [ ! -d "/var/cache/pbuilder/debian-buster-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/debian-buster-i386/aptcache/
        sudo OS=debian DIST=buster ARCH=i386 pbuilder --create
    fi
    sudo OS=debian DIST=buster ARCH=i386 pbuilder build *.dsc
    
    if [ ! -d "/var/cache/pbuilder/ubuntu-bionic-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-bionic-i386/aptcache/
        sudo OS=ubuntu DIST=bionic ARCH=i386 pbuilder --create
    fi
    sudo OS=ubuntu DIST=bionic ARCH=i386 pbuilder build *.dsc
    
    if [ ! -d "/var/cache/pbuilder/ubuntu-disco-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-disco-i386/aptcache/
        sudo OS=ubuntu DIST=disco ARCH=i386 pbuilder --create
    fi
    sudo OS=ubuntu DIST=disco ARCH=i386 pbuilder build *.dsc
    
    if [ ! -d "/var/cache/pbuilder/ubuntu-eoan-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-eoan-i386/aptcache/
        sudo OS=ubuntu DIST=eoan ARCH=i386 pbuilder --create
    fi
    sudo OS=ubuntu DIST=eoan ARCH=i386 pbuilder build *.dsc
fi

if [ "armhf" = "$1" ]; then
    
    echo "build amd64 things"
    
    if [ ! -d "/var/cache/pbuilder/raspbian-stretch-armhf/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/raspbian-stretch-armhf/aptcache/
        sudo OS=raspbian DIST=stretch ARCH=armhf pbuilder --create
    fi
    sudo OS=raspbian DIST=stretch ARCH=armhf pbuilder build *.dsc
    
    if [ ! -d "/var/cache/pbuilder/raspbian-buster-armhf/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/raspbian-buster-armhf/aptcache/
        sudo OS=raspbian DIST=buster ARCH=armhf pbuilder --create
    fi
    sudo OS=raspbian DIST=buster ARCH=armhf pbuilder build *.dsc
fi