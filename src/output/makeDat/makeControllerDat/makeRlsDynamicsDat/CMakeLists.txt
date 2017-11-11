add_subdirectory(makeDynamicsDat)

set(srcs
  makeVelocityDat.cpp
  makeAccelerationDat.cpp
  makeRlsDynamicsDat.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeRlsDynamicsDat_srcs)
set(makeRlsDynamicsDat_srcs
  ${makeRlsDynamicsDat_srcs}
  ${makeDynamicsDat_srcs}
  PARENT_SCOPE
  )
