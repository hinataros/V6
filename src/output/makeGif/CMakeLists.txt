set(srcs
  setPlane.cpp
  makeGif2D.cpp
  makeGif3D.cpp
  makeGif.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeGif_srcs)
set(makeGif_srcs ${makeGif_srcs} PARENT_SCOPE)
