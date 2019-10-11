# @author Sho Miyahara 2018

set(srcs
  externalWrenchCP.cpp
  externalWrenchStep.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" externalWrench_srcs)
set(externalWrench_srcs ${externalWrench_srcs} PARENT_SCOPE)
