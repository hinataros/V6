# @author Sho Miyahara 2018

# add_subdirectory(gif)

set(srcs
  baseTrans.cpp
  baseRot.cpp
  joint.cpp
  joint_wTorso.cpp
  joint_wTorso1.cpp
  joint_wTorso3.cpp
  com.cpp
  mix.cpp
  eeTrans.cpp
  eeRot.cpp
  eeWrench.cpp
  mom.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" modelGraphConfig_srcs)
set(modelGraphConfig_srcs ${modelGraphConfig_srcs} ${gif_srcs} PARENT_SCOPE)
