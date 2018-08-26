# @author Sho Miyahara 2017

set(srcs
  baseOrientationReferencePI.cpp
  # baseOrientationAnkleHip.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" baseOrientationReference_srcs)
set(baseOrientationReference_srcs ${baseOrientationReference_srcs} PARENT_SCOPE)
