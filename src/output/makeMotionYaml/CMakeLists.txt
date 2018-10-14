# @author Sho Miyahara 2018

set(srcs
  makeTreeModelMotionYaml.cpp
  makeMotionYaml.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeMotionYaml_srcs)
set(makeMotionYaml_srcs ${makeMotionYaml_srcs} PARENT_SCOPE)
