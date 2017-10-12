set(srcs
  makeRlsVelocityDat.cpp
  makeRlsAccelerationDat.cpp
  makeRlsDynamicsDat.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeControllerDat_srcs)
set(makeControllerDat_srcs ${makeControllerDat_srcs} PARENT_SCOPE)
