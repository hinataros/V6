# @author Sho Miyahara 2018

add_subdirectory(walking)

set(srcs
  desiredDcmGeneratorCP.cpp
  # dcmAnkleHip.cpp
  # dcmSSWalking.cpp
  # dcmDSWalking.cpp
  dcmHTWalking.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredDcmGenerator_srcs)
set(desiredDcmGenerator_srcs
  ${walking_srcs}
  ${desiredDcmGenerator_srcs}
  PARENT_SCOPE
  )
