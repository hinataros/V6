set(srcs
  initialize.cpp
  finalize.cpp
  readInfo.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" info_srcs)
set(info_srcs ${info_srcs} PARENT_SCOPE)
