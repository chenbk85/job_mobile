ln -s ../MOB_lib ./MOB_lib

find . -name CMakeCache.txt -exec rm -rf {} \;

cmake . -G Xcode
xcodebuild
