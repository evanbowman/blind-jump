#========================================================================#
# Copyright (C) 2016 Evan Bowman                                         #
# Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            #
#========================================================================#

if [ $# == 2 ]; then
    rm -rf ../targets/debian/$2.deb

    mkdir -p ../targets/debian/$2/DEBIAN
    mkdir -p ../targets/debian/$2/usr/bin
    cp ../Resources/control ../targets/debian/$2/DEBIAN/control
    cd ../targets/debian
    dpkg-deb -b $2
    rm -rf $2
    cd ../../src
else
    printf "\nUsage: packageScriptDebian <executable> <name>"
fi
