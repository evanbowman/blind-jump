#========================================================================#
# Copyright (C) 2016 Evan Bowman                                         #
# Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            #
#========================================================================#


# arg2 is the app name, arg1 is the exe name
if [ $# == 2 ]; then
    rm -rf ../target/$2.app

    mkdir -p ../target/$2.app/Contents/MacOS
    printf "\nCreated parent package directory"
    
    mv -f $1 ../target/$2.app/Contents/MacOS/$1
    printf "\nMoved executable to package"

    printf "\nCopying resources into package... "
    cp -rf ../Resources ../target/$2.app/Contents/
    printf "Done!"

    printf "\nCopying frameworks into package... "
    cp -rf ../Frameworks ../target/$2.app/Contents/
    printf "Done!"

    printf "\nCopying sources into package... "
    mkdir ../target/$2.app/Contents/src
    cp -rf ./ ../target/$2.app/Contents/src
    rm ../target/$2.app/Contents/src/*.o
    printf "Done!"

    printf "\nCompressing sources... "
    tar -czf ../target/$2.app/Contents/src.tar.gz ../target/$2.app/Contents/src
    rm -rf ../target/$2.app/Contents/src
    printf "Done!"
    
    printf "\nMoving plist file... "
    mv ../target/$2.app/Contents/Resources/info.plist ../target/$2.app/Contents/info.plist
    printf "Done!"
    
    if [ $? -eq 0 ]; then
	printf "\nBundling complete!"
    else
	printf "\nFailed to create app bundle"
	rm -rf ../target/$2.app/Contents/MacOS
    fi
else
    printf "\nUsage: packageScriptMac <executable> <name>"
fi

