# @author Sho Miyahara 2018

set(srcs
  baseRotationPI.cpp
  # baseRotationAnkleHip.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" baseRotation_srcs)
set(baseRotation_srcs ${baseRotation_srcs} PARENT_SCOPE)
