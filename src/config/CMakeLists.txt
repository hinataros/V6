set(srcs
  readConfig.cpp
  setDir.cpp
  readArgument.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" config_srcs)
set(config_srcs ${config_srcs} PARENT_SCOPE)
