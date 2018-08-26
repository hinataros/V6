# @author Sho Miyahara 2017

set(srcs
  joints.cpp
  position.cpp
  velocity.cpp
  transformMatrix.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" kinematics_srcs)
set(kinematics_srcs ${kinematics_srcs} PARENT_SCOPE)
