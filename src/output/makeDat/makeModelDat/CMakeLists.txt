# @author Sho Miyahara 2017

set(srcs
  baseTrans.cpp
  baseRot.cpp
  joint.cpp
  eeTrans.cpp
  eeRot.cpp
  eeWrench.cpp
  com.cpp
  mom.cpp
  makeTreeModelDat.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeModelDat_srcs)
set(makeModelDat_srcs ${makeModelDat_srcs} PARENT_SCOPE)
