# @author Sho Miyahara 2018

set(srcs
  dcm.cpp
  sysMom.cpp
  localCop.cpp
  netCop.cpp
  stabilityIndex.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" index_srcs)
set(index_srcs ${index_srcs} PARENT_SCOPE)
