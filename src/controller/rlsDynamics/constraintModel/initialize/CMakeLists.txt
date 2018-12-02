# @author Sho Miyahara 2018

set(srcs
  setModel.cpp
  constraintInfo.cpp
  resize.cpp
  initialize.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" initialize_srcs)
set(initialize_srcs ${initialize_srcs} PARENT_SCOPE)
