INCLUDE(FindSubversion)
Subversion_WC_INFO(${SOURCE_DIR} MY)
FILE(WRITE svn_version.hpp "#define SVNVERSION ${MY_WC_REVISION}\n")
