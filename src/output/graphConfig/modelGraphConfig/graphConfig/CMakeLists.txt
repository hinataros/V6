# @author Sho Miyahara 2018

set(srcs
  joint.cpp
  baseTrans.cpp
  baseRot.cpp
  eeTrans.cpp
  eeRot.cpp
  eeWrench.cpp
  com.cpp
  spatialMom.cpp
  mix.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" graphConfig_srcs)
set(graphConfig_srcs ${graphConfig_srcs} PARENT_SCOPE)
