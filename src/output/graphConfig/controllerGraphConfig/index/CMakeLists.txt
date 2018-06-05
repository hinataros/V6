# @author Sho Miyahara 2018

set(srcs
  # formulatedMom.cpp
  localCop.cpp
  netCop.cpp
  stabilityIndex.cpp
  footPrint.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" index_srcs)
set(index_srcs ${index_srcs} PARENT_SCOPE)
