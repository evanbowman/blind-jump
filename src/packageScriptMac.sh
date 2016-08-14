#========================================================================#
# Copyright (C) 2016 Evan Bowman                                         #
#                                                                        #
# This program is free software: you can redistribute it and/or modify   #
# it under the terms of the GNU General Public License as published by   #
# the Free Software Foundation, either version 3 of the License, or      #
# (at your option) any later version.                                    #
#                                                                        #
# This program is distributed in the hope that it will be useful,        #
# but WITHOUT ANY WARRANTY; without even the implied warranty of         #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          #
# GNU General Public License for more details.                           #
#                                                                        #
# You should have received a copy of the GNU General Public License      #
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  #
#========================================================================#


# arg2 is the app name, arg1 is the exe name
if [ $# == 2 ]; then
    rm -rf ../prod/$2.app

    mkdir -p ../prod/$2.app/Contents/MacOS
    printf "\nCreated parent package directory"
    
    mv -f $1 ../prod/$2.app/Contents/MacOS/$1
    printf "\nMoved executable to package"

    printf "\nCopying resources into package... "
    cp -rf ../Resources ../prod/$2.app/Contents/
    printf "Done!"

    printf "\nCopying frameworks into package... "
    cp -rf ../Frameworks ../prod/$2.app/Contents/
    printf "Done!"

    printf "\nCopying sources into package... "
    mkdir ../prod/$2.app/Contents/src
    cp -rf ./ ../prod/$2.app/Contents/src
    rm ../prod/$2.app/Contents/src/*.o
    printf "Done!"

    printf "\nCompressing sources... "
    tar -czf ../prod/$2.app/Contents/src.tar.gz ../prod/$2.app/Contents/src
    rm -rf ../prod/$2.app/Contents/src
    printf "Done!"
    
    printf "\nMoving plist file... "
    mv ../prod/$2.app/Contents/Resources/info.plist ../prod/$2.app/Contents/info.plist
    printf "Done!"
    
    if [ $? -eq 0 ]; then
	printf "\nBundling complete!"
    else
	printf "\nFailed to create app bundle"
	rm -rf ../prod/$2.app/Contents/MacOS
    fi
else
    printf "\nUsage: packageScriptMac <executable> <name>"
fi

