# @author Sho Miyahara 2017

set(srcs
  desiredDcmGeneratorCP.cpp
  # dcmAnkleHip.cpp
  # dcmSSWalking.cpp
  # dcmDSWalking.cpp
  # desiredDcmGeneratorHTWalking.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredDcmGenerator_srcs)
set(desiredDcmGenerator_srcs ${desiredDcmGenerator_srcs} PARENT_SCOPE)
