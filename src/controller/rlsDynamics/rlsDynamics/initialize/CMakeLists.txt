# @author Sho Miyahara 2018

set(srcs
  initializeExt.cpp
  setDefaultConfig.cpp
  readControllerHeader.cpp
  setModelInfo.cpp
  setConstraintInfo.cpp
  resize.cpp
  setControllerMap.cpp
  stateTrigger.cpp
  localInitialize.cpp
  initialize.cpp
  extractorResize.cpp
  stateScanner.cpp
  controllerYamlModifier.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" initialize_srcs)
set(initialize_srcs ${initialize_srcs} PARENT_SCOPE)
