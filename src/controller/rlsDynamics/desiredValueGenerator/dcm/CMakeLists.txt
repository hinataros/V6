# @author Sho Miyahara 2018

set(srcs
  dcmCP.cpp
  dcmCPabs.cpp
  # dcmAnkleHip.cpp
  # dcmSSWalking.cpp
  # dcmDSWalking.cpp
  dcmHTWalking.cpp
  dcmvrpHTWalking.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" dcm_srcs)
set(dcm_srcs
  ${dcm_srcs}
  PARENT_SCOPE
  )
