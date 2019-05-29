# @author Sho Miyahara 2018

add_subdirectory(linear)
add_subdirectory(angular)

set(srcs
  baseMomentum.cpp
  baseVrpMomentum.cpp
  centroidalMomentum.cpp
  centroidalVrpMomentum.cpp
  centroidalVrpMomentumDamping.cpp
  centroidalVrpRNS.cpp
  centroidalCmpMomentum.cpp
  deltaMomentum.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" momentumController_srcs)
set(momentumController_srcs
  ${momentumController_srcs}
  ${linear_srcs}
  ${angular_srcs}
  PARENT_SCOPE
  )
