# @author Sho Miyahara 2018

set(srcs
  m_internalDistribution.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" internalForceController_srcs)
set(internalForceController_srcs ${internalForceController_srcs} PARENT_SCOPE )
