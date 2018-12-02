# @author Sho Miyahara 2018

set(srcs setDat.cpp)

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" extDat_srcs)
set(extDat_srcs ${extDat_srcs} PARENT_SCOPE)
