# @author Sho Miyahara 2018

set(srcs
  setConfig.cpp
  analysisYaml.cpp
  readWorkHeader.cpp
  setModelInfo.cpp
  initializeConstraintInfo.cpp
  resize.cpp
  setControllerMap.cpp
  stateTrigger.cpp
  localInitialize.cpp
  initialize.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" initialize_srcs)
set(initialize_srcs ${initialize_srcs} PARENT_SCOPE)
