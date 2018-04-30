# @author Sho Miyahara 2018

set(srcs
  baseTrans.cpp
  baseRot.cpp
  joint.cpp
  eeTrans.cpp
  eeRot.cpp
  eeWrench.cpp
  com.cpp
  spatialMom.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" graphConfig_srcs)
set(graphConfig_srcs ${graphConfig_srcs} PARENT_SCOPE)
