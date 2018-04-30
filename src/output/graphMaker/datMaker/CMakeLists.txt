# @author Sho Miyahara 2018

set(srcs
  setDat.cpp
  datMaker.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" datMaker_srcs)
set(datMaker_srcs ${datMaker_srcs} PARENT_SCOPE)
