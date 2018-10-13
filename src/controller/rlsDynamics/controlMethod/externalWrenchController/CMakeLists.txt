#@author Sho Miyahara 2018

set(srcs
  transformExternalWrench.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" externalWrenchController_srcs)
set(externalWrenchController_srcs ${externalWrenchController_srcs} PARENT_SCOPE)
