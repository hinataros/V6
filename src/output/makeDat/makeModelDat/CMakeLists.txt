set(srcs
  makeTreeModelDat.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeModelDat_srcs)
set(makeModelDat_srcs ${makeModelDat_srcs} PARENT_SCOPE)
