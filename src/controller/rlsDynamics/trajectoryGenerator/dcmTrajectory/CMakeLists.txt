# @author Sho Miyahara 2017

set(srcs
  dcmTrajectoryCP.cpp
  # dcmAnkleHip.cpp
  # dcmSSWalking.cpp
  # dcmDSWalking.cpp
  # dcmHTWalking.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" dcmTrajectory_srcs)
set(dcmTrajectory_srcs ${dcmTrajectory_srcs} PARENT_SCOPE)
