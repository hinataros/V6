set(srcs
  makeGp.cpp
  makeGpLibrary.cpp
  makeGpTimeLimb.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeGp_srcs)
set(makeGp_srcs ${makeGp_srcs} PARENT_SCOPE)
