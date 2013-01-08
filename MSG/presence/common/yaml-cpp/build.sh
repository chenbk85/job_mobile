#!/bin/bash -v

#Building yaml-cpp

g++ -g -shared -fPIC -c -I./include -I/home/sk68/local/include -L/home/sk68/local/lib src/aliasmanager.cpp src/directives.cpp src/emitterstate.cpp src/iterator.cpp src/nodeownership.cpp src/parser.cpp src/scanscalar.cpp src/simplekey.cpp src/tag.cpp src/binary.cpp src/emitfromevents.cpp src/emitterutils.cpp src/nodebuilder.cpp src/null.cpp src/regex.cpp src/scantag.cpp src/singledocparser.cpp src/conversion.cpp src/emitter.cpp src/exp.cpp src/node.cpp src/ostream.cpp src/scanner.cpp src/scantoken.cpp src/stream.cpp

#ld -G *.o -o libyaml-cpp.so
g++ -shared -o libyaml-cpp.so *.o

rm *.o

