# @author Sho Miyahara 2018

set(srcs
  operator.cpp
  rotationMatrix.cpp
  zero.cpp
  identity.cpp
  xi2q.cpp
  R2q.cpp
  dq2w.cpp
  ddq2dw.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" quaternion_srcs)
set(quaternion_srcs ${quaternion_srcs} PARENT_SCOPE)
