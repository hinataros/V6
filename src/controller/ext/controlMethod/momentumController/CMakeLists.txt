# @author Sho Miyahara 2018

set(srcs
  linear_CRB.cpp
  linear_Damper.cpp
  linear_RNS.cpp
  linear_MobilityCompensation.cpp
  linear_FrictionDistribution.cpp
  vrp_CRB.cpp
  vrp_Damper.cpp
  vrp_RNS.cpp
  vrp_MobilityCompensation.cpp
  vrp_FrictionDistribution.cpp
  vrp_FrictionDistribution_zDamper.cpp
  CRB_AM.cpp
  SAM_Damper.cpp
  SAM_RNS.cpp
  SAM_MobilityCompensation.cpp
  SAM_FrictionDistribution.cpp
  SAM_FrictionDistribution_zDamper.cpp
  testMomentumController.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" momentumController_srcs)
set(momentumController_srcs ${momentumController_srcs} PARENT_SCOPE)


