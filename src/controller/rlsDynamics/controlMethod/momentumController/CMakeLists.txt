# @author Sho Miyahara 2017

set(srcs
  baseMomentum.cpp
  centroidalMomentum.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" momentumController_srcs)
set(momentumController_srcs ${momentumController_srcs} PARENT_SCOPE)
