set(srcs
  cl_Bvel.cpp
  cl_Mvel.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" velocityController_srcs)
set(velocityController_srcs ${velocityController_srcs} PARENT_SCOPE)
