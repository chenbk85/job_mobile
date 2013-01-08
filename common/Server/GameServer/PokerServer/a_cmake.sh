ln -s ../MOB_lib ./MOB_lib

find . -name CMakeCache.txt -exec rm -rf {} \;
find . -name CMakeFiles -exec rm -rf {} \;
find . -name *.a -exec rm -rf {} \;

cmake .
make


#rm ./MOB_lib
