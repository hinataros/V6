set(srcs
  ddthD.cpp
  cl_Bacc.cpp
  cl_Macc.cpp
  noname.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" accelerationController_srcs)
set(accelerationController_srcs ${accelerationController_srcs} PARENT_SCOPE)
