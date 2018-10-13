# @author Sho Miyahara 2018

set(srcs
  initialize.cpp
  setPath.cpp
  readCnoid.cpp
  readModel.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" worldModel_srcs)
set(worldModel_srcs ${worldModel_srcs} PARENT_SCOPE)
