# @author Sho Miyahara 2018

set(srcs
  initialize.cpp
  setLink.cpp
  setPath.cpp
  readArgument.cpp
  readInitYaml.cpp
  readConfig.cpp
  config.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" config_srcs)
set(config_srcs ${config_srcs} PARENT_SCOPE)
