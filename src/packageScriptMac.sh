# arg2 is the app name, arg1 is the exe name
if [ $# == 2 ]; then
    rm -rf ../prod/$2.app/Contents/MacOS

    mkdir -p ../prod/$2.app/Contents/MacOS
    printf "\nCreated parent package directory"
    
    mv -f $1 ../prod/$2.app/Contents/MacOS/$1
    printf "\nMoved executable to package"

    printf "\nCopying resources into package..."
    cp -rf ../Resources ../prod/$2.app/Contents/

    printf "\nCopying frameworks into package..."
    cp -rf ../Frameworks ../prod/$2.app/Contents/

    printf "\nMoving plist file..."
    mv ../prod/$2.app/Contents/Resources/info.plist ../prod/$2.app/Contents/info.plist

    if [ $? -eq 0 ]; then
	printf "\nBundling complete!"
    else
	printf "\nFailed to create app bundle"
	rm -rf ../prod/$2.app/Contents/MacOS
    fi
else
    printf "\nUsage: packageScriptMac <executable> <name>"
fi

