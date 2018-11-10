# @author Sho Miyahara 2018

add_subdirectory(walking)

set(srcs
  dcmCP.cpp
  # dcmAnkleHip.cpp
  # dcmSSWalking.cpp
  # dcmDSWalking.cpp
  dcmHTWalking.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" dcm_srcs)
set(dcm_srcs
  ${walking_srcs}
  ${dcm_srcs}
  PARENT_SCOPE
  )
