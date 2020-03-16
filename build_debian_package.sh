#!/bin/sh

#   arg1 - platform
#   i386    ununtu/debian    ./build_debian_package.sh i386 10
#   amd64,  ununtu/debian    ./build_debian_package.sh amd64 10
#   armhf   raspbian         ./build_debian_package.sh armhf 10
#
#   arg2 - COMPAT
#   
# Package version
MAJOR_VERSION=`head -n4  VERSION.m4 |  grep major_version | cut -c30- | tr -d "[]()"`
MINOR_VERSION=`head -n4  VERSION.m4 |  grep minor_version | cut -c30- | tr -d "[]()"`
RELEASE_VERSION=`head -n4  VERSION.m4 |  grep release_version | cut -c30- | tr -d "[]()"`
BUILD_VERSION=`head -n4  VERSION.m4 |  grep build_version | cut -c30- | tr -d "[]()"`
RELEASE_DEBIAN=`head -n4  VERSION.m4 |  grep release_debian | tr -d "m4_define[release_debian], ()"`

NAME_PLUS_VER=libvscphelper$MAJOR_VERSION-$MAJOR_VERSION.$MINOR_VERSION.$RELEASE_VERSION
BUILD_FOLDER="../dist"
DATENOW="`date -R`"

# Create the build folder
echo "***   ---Creating build folder: ["$BUILD_FOLDER"]"
mkdir -p $BUILD_FOLDER

# Debian compability 10 on Raspberry
# relevant for 'control' and 'compat'
COMPAT="12"

# makes correct /usr/lib subfolder (/usr/lib/x86_64-linux-gnu/), none on Raspberry
# relevant for 'install' and 'links'
#SUBFOLDER='$(DEB_BUILD_GNU_CPU)-$(DEB_BUILD_GNU_SYSTEM)'
SUBFOLDER="x86_64-linux-gnu"

# dependencies for control
DEPENDENCY="libc6-dev (>= 2.14), libstdc++6 (>= 5.2), libgcc1 (>= 1:3.0), libssl-dev (>=1.0) libexpat1 (>= 2.0)"

# Get OS and version
if [ -f /etc/os-release ]; then
    # freedesktop.org and systemd
    . /etc/os-release
    OS=$NAME
    VER=$VERSION_ID
elif type lsb_release >/dev/null 2>&1; then
    # linuxbase.org
    OS=$(lsb_release -si)
    VER=$(lsb_release -sr)
elif [ -f /etc/lsb-release ]; then
    # For some versions of Debian/Ubuntu without lsb_release command
    . /etc/lsb-release
    OS=$DISTRIB_ID
    VER=$DISTRIB_RELEASE
elif [ -f /etc/debian_version ]; then
    # Older Debian/Ubuntu/etc.
    OS=Debian
    VER=$(cat /etc/debian_version)
elif [ -f /etc/SuSe-release ]; then
    # Older SuSE/etc.
    ...
elif [ -f /etc/redhat-release ]; then
    # Older Red Hat, CentOS, etc.
    ...
else
    # Fall back to uname, e.g. "Linux <version>", also works for BSD, etc.
    OS=$(uname -s)
    VER=$(uname -r)
fi

echo "OS=${OS} VER=${VER}"

# Get acitecture
case $(uname -m) in
x86_64)
    BITS=64
    SUBFOLDER="x86_64-linux-gnu"
    ;;
i*86)
    BITS=32
    SUBFOLDER="i386-linux-gnu"
    ;;
armv6l)
    BITS=32
    SUBFOLDER="arm-linux-gnueabihf"
    ;; 
armv7l)
    BITS=64
    SUBFOLDER="arm-linux-gnueabihf"
    ;;       
*)
    BITS=?
    ;;
esac

# Get word width
echo "BITS=${BITS}"

case $(uname -m) in
x86_64)
    ARCH=x64  # or AMD64 or Intel64 or whatever
    ;;
i*86)
    ARCH=x86  # or IA32 or Intel32 or whatever
    ;;
*)
    # leave   armv6l/armv7l
    ARCH=`uname -m`
    ;;
esac

echo "ARCH=${ARCH}"

case $OS in
Debian)
    COMPAT="11"
    ;;
Ubuntu)
    COMPAT="10"
    ;;
Raspian)
    COMPAT="9"
    ;;
esac

# ---------------------------------------------------------------------
case "$1" in
amd64)
    echo "Building for amd64"	
    BITS=64
    SUBFOLDER="x86_64-linux-gnu"
    ARCH=x64
    ;;
i386)
    echo "Building for i386"	
    BITS=32
    SUBFOLDER="i386-linux-gnu"
    ARCH=x86
    ;;
armhf)
    echo "Building for armhf"	
    BITS=32
    SUBFOLDER="arm-linux-gnueabihf"
    ARCH=armhf
    ;;
*)
    echo "Building with discovery for installed system"
    ;;
esac
# ---------------------------------------------------------------------

echo "*** name+ver  --- "$NAME_PLUS_VER

# Clean project
make clean
vscp/clean_for_dist
./clean_for_dist

echo "---Copying Debian_orig to destination folder "$BUILD_FOLDER
cp -r debian_orig/ $BUILD_FOLDER

echo "***   ---making tar"
tar -zcf $BUILD_FOLDER/$NAME_PLUS_VER.tar.gz *

echo "***   $NAME_PLUS_VER.tgz created."
cd $BUILD_FOLDER
mkdir $NAME_PLUS_VER/
cd $NAME_PLUS_VER/

#tar -zxvf ../$NAME_PLUS_VER.tar.gz
tar -zxf ../$NAME_PLUS_VER.tar.gz

echo "***   Making 'debian' folder"
mkdir debian
cp -r debian_orig/* debian

echo "***   Rename files to match MAJOR_VERSION"
mv debian/libvscphelper-dev.dirs "debian/libvscphelper${MAJOR_VERSION}-dev.dirs"
mv debian/libvscphelper-dev.install "debian/libvscphelper${MAJOR_VERSION}-dev.install"
mv debian/libvscphelper-dev.manpages "debian/libvscphelper${MAJOR_VERSION}-dev.manpages"
mv debian/libvscphelper-dev.substvars "debian/libvscphelper${MAJOR_VERSION}-dev.substvars"

mv debian/libvscphelper.dirs "debian/libvscphelper${MAJOR_VERSION}.dirs"
mv debian/libvscphelper.install "debian/libvscphelper${MAJOR_VERSION}.install"
mv debian/libvscphelper.links "debian/libvscphelper${MAJOR_VERSION}.links"
mv debian/libvscphelper.manpages "debian/libvscphelper${MAJOR_VERSION}.manpages"
mv debian/libvscphelper.substvars "debian/libvscphelper${MAJOR_VERSION}.substvars"

echo "***   Running dh_make" ../$NAME_PLUS_VER.tar.gz
dh_make --single --defaultless -f ../$NAME_PLUS_VER.tar.gz -a -s -c mit -y

echo "***   Do variable substitution"
sed -i "s/%MAJOR-VERSION/${MAJOR_VERSION}/g" debian/*
sed -i "s/%MINOR-VERSION/${MINOR_VERSION}/g" debian/*
sed -i "s/%RELEASE-VERSION/${RELEASE_VERSION}/g" debian/*
sed -i "s/%BUILD-VERSION/${BUILD_VERSION}/g" debian/*
sed -i "s/%RELEASE-DEBIAN/${RELEASE_DEBIAN}/g" debian/*
sed -i "s/%COMPAT/${COMPAT}/g" debian/*
sed -i "s/%SUBFOLDER/${SUBFOLDER}/g" debian/*
sed -i "s/%DATENOW/${DATENOW}/g" debian/*

echo "***   ---Now do 'dpkg-buildpackage -us -uc' or 'dpkg-buildpackage -b'"

#cd $NAME_PLUS_VER
#debuild clean
debuild -us -uc

echo "***   If all is alright check dist folder for Debian package "

# ---------------------------------------------------------------------

pwd
cd ..

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

    sudo rm -f /var/cache/pbuilder/debian-stretch-amd64/result/*
    sudo OS=debian DIST=stretch ARCH=amd64 pbuilder build *.dsc
    mkdir debian_stretch_amd64
    cp -r /var/cache/pbuilder/debian-stretch-amd64/result/* debian_stretch_amd64

    if [ ! -d "/var/cache/pbuilder/debian-buster-amd64/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/debian-buster-amd64/aptcache/
        sudo OS=debian DIST=buster ARCH=amd64 pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/debian-buster-amd64/result/*
    sudo OS=debian DIST=buster ARCH=amd64 pbuilder build *.dsc
    mkdir debian_buster_amd64
    cp -r /var/cache/pbuilder/debian-buster-amd64/result/* debian_buster_amd64

    if [ ! -d "/var/cache/pbuilder/ubuntu-bionic-amd64/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-bionic-amd64/aptcache/
        sudo OS=ubuntu DIST=bionic ARCH=amd64 pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/ubuntu-bionic-amd64/result/*
    sudo OS=ubuntu DIST=bionic ARCH=amd64 pbuilder build *.dsc
    mkdir ubuntu_bionic_amd64
    cp -r /var/cache/pbuilder/ubuntu-bionic-amd64/result/* ubuntu_bionic_amd64
    
    if [ ! -d "/var/cache/pbuilder/ubuntu-disco-amd64/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-disco-amd64/aptcache/
        sudo OS=ubuntu DIST=disco ARCH=amd64 pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/ubuntu-disco-amd64/result/*
    sudo OS=ubuntu DIST=disco ARCH=amd64 pbuilder build *.dsc
    mkdir ubuntu_disco_amd64
    cp -r /var/cache/pbuilder/ubuntu-disco-amd64/result/* ubuntu_disco_amd64

    if [ ! -d "/var/cache/pbuilder/ubuntu-disco-amd64/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-eoan-amd64/aptcache/
        sudo OS=ubuntu DIST=eoan ARCH=amd64 pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/ubuntu-eoan-amd64/result/*
    sudo OS=ubuntu DIST=eoan ARCH=amd64 pbuilder build *.dsc
    mkdir ubuntu_eoan_amd64
    cp -r /var/cache/pbuilder/ubuntu-eoan-amd64/result/* ubuntu_eoan_amd64

fi

if [ "i386" = "$1" ]; then

    echo "build i386 things"
    
    if [ ! -d "/var/cache/pbuilder/debian-stretch-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/debian-stretch-i386/aptcache/
        sudo OS=debian DIST=stretch ARCH=i386 pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/debian-stretch-i386/result/*
    sudo OS=debian DIST=stretch ARCH=i386 pbuilder build *.dsc
    mkdir debian_stretch_i386
    cp -r /var/cache/pbuilder/debian-stretch-i386/result/* debian_stretch_i386

    if [ ! -d "/var/cache/pbuilder/debian-buster-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/debian-buster-i386/aptcache/
        sudo OS=debian DIST=buster ARCH=i386 pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/debian-buster-i386/result/*
    sudo OS=debian DIST=buster ARCH=i386 pbuilder build *.dsc
    mkdir debian_buster_i386
    cp -r /var/cache/pbuilder/debian-buster-i386/result/* debian_buster_i386
    
    if [ ! -d "/var/cache/pbuilder/ubuntu-bionic-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-bionic-i386/aptcache/
        sudo OS=ubuntu DIST=bionic ARCH=i386 pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/ubuntu-bionic-i386/result/*
    sudo OS=ubuntu DIST=bionic ARCH=i386 pbuilder build *.dsc
    mkdir ubuntu_bionic_i386
    cp -r /var/cache/pbuilder/ubuntu-bionic-i386/result/* ubuntu_bionic_i386
    
    if [ ! -d "/var/cache/pbuilder/ubuntu-disco-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-disco-i386/aptcache/
        sudo OS=ubuntu DIST=disco ARCH=i386 pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/ubuntu-disco-i386/result/*
    sudo OS=ubuntu DIST=disco ARCH=i386 pbuilder build *.dsc
    mkdir ubuntu_disco_i386
    cp -r /var/cache/pbuilder/ubuntu-disco-i386/result/* ubuntu_disco_i386
    
    if [ ! -d "/var/cache/pbuilder/ubuntu-eoan-i386/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/ubuntu-eoan-i386/aptcache/
        sudo OS=ubuntu DIST=eoan ARCH=i386 pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/ubuntu-eoan-i386/result/*
    sudo OS=ubuntu DIST=eoan ARCH=i386 pbuilder build *.dsc
    mkdir ubuntu_eoan_i386
    cp -r /var/cache/pbuilder/ubuntu-eoan-i386/result/* ubuntu_eoan_i386

fi

if [ "armhf" = "$1" ]; then
    
    echo "build armhf things"
    
    if [ ! -d "/var/cache/pbuilder/raspbian-stretch-armhf/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/raspbian-stretch-armhf/aptcache/
        sudo OS=raspbian DIST=stretch ARCH=armhf pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/raspbian-stretch-armhf/result/*
    sudo OS=raspbian DIST=stretch ARCH=armhf pbuilder build *.dsc
    mkdir raspian_stretch_armhf
    cp -r /var/cache/pbuilder/raspbian-stretch-armhf/result/* raspian_stretch_armhf 
    
    if [ ! -d "/var/cache/pbuilder/raspbian-buster-armhf/aptcache" ] 
    then
        sudo mkdir -p /var/cache/pbuilder/raspbian-buster-armhf/aptcache/
        sudo OS=raspbian DIST=buster ARCH=armhf pbuilder --create
    fi

    sudo rm -f /var/cache/pbuilder/raspbian-buster-armhf/result/*
    sudo OS=raspbian DIST=buster ARCH=armhf pbuilder build *.dsc
    mkdir raspian_buster_armhf
    cp -r /var/cache/pbuilder/raspbian-buster-armhf/result/* raspian_buster_armhf 
    
fi

# ---------------------------------------------------------------------

