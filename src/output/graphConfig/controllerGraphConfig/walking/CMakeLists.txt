# @author Sho Miyahara 2018

set(srcs
  # localCop4walking.cpp
  # netCop4walking.cpp
  # cmp4walking.cpp
  stabilityIndex4walking.cpp
  vrpDes4walking.cpp
  vrpBarDes4walking.cpp
  # footPrint.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" walking_srcs)
set(walking_srcs ${walking_srcs} PARENT_SCOPE)
