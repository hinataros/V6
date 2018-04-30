# @author Sho Miyahara 2017

set(srcs
  dcmSequence.cpp
  dcmAnkleHip.cpp
  dcmSSWalking.cpp
  dcmDSWalking.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" dcmReference_srcs)
set(dcmReference_srcs ${dcmReference_srcs} PARENT_SCOPE)
