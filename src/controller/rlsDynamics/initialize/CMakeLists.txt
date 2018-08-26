# @author Sho Miyahara 2017

set(srcs
  sequence.cpp
  referenceMap.cpp
  trajectoryGeneratorMap.cpp
  controllerMap.cpp
  walking.cpp
  initialize.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" initialize_srcs)
set(initialize_srcs ${initialize_srcs} PARENT_SCOPE)
