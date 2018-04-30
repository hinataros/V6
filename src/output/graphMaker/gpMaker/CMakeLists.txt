# @author Sho Miyahara 2018

set(srcs
  libraryMaker.cpp
  gpMaker.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" gpMaker_srcs)
set(gpMaker_srcs ${gpMaker_srcs} PARENT_SCOPE)
