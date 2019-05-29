# @author Sho Miyahara 2018

set(srcs
  initialize.cpp
  setModel.cpp
  setYamlInfo.cpp
  resize.cpp
  # resizeState.cpp
  setMap.cpp
  setInitialBoundary.cpp
  initializeWalking.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" initialize_srcs)
set(initialize_srcs ${initialize_srcs} PARENT_SCOPE)
