# @author Sho Miyahara 2018

set(srcs
  baseTrans.cpp
  baseRot.cpp
  joint.cpp
  com.cpp
  mix.cpp
  eeTrans.cpp
  eeRot.cpp
  eeWrench.cpp
  spatialMom.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" modelGraphConfig_srcs)
set(modelGraphConfig_srcs ${modelGraphConfig_srcs} PARENT_SCOPE)
