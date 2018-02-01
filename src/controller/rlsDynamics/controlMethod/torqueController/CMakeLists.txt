# @author Sho Miyahara 2017

set(srcs
  jointSpace.cpp
  staticControl.cpp
  base.cpp
  mixed.cpp
  mixedmixed.cpp
  crb.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" torqueController_srcs)
set(torqueController_srcs ${torqueController_srcs} PARENT_SCOPE)
