#========================================================================#
# Copyright (C) 2016 Evan Bowman                                         #
# Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            #
#========================================================================#


# arg2 is the app name, arg1 is the exe name
if [ $# == 2 ]; then
    rm -rf ../targets/macOS/$2.app

    mkdir -p ../targets/macOS/$2.app/Contents/MacOS
    printf "\nCreated parent package directory"
    
    mv -f $1 ../targets/macOS/$2.app/Contents/MacOS/$1
    printf "\nMoved executable to package"

    printf "\nCopying resources into package... "
    cp -rf ../Resources ../targets/macOS/$2.app/Contents/
    printf "Done!"

    printf "\nCopying frameworks into package... "
    cp -rf ../Frameworks ../targets/macOS/$2.app/Contents/
    printf "Done!"

    printf "\nCopying sources into package... "
    mkdir ../targets/macOS/$2.app/Contents/src
    cp -rf ./ ../targets/macOS/$2.app/Contents/src
    rm ../targets/macOS/$2.app/Contents/src/*.o
    printf "Done!"

    printf "\nCompressing sources... "
    tar -czf ../targets/macOS/$2.app/Contents/src.tar.gz ../targets/macOS/$2.app/Contents/src
    rm -rf ../targets/macOS/$2.app/Contents/src
    printf "Done!"
    
    printf "\nMoving plist file... "
    mv ../targets/macOS/$2.app/Contents/Resources/info.plist ../targets/macOS/$2.app/Contents/info.plist
    printf "Done!"
    
    if [ $? -eq 0 ]; then
	printf "\nBundling complete!"
    else
	printf "\nFailed to create app bundle"
	rm -rf ../targets/macOS/$2.app/Contents/MacOS
    fi
else
    printf "\nUsage: packageScriptMac <executable> <name>"
fi

