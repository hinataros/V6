add_subdirectory(makeRlsDynamicsDat)

# set(srcs
#   makeRlsDynamicsDat.cpp
#   )

# MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeControllerDat_srcs)

set(makeControllerDat_srcs
  ${makeRlsDynamicsDat_srcs}
  PARENT_SCOPE
  )
