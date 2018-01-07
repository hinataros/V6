# @author Sho Miyahara 2017

add_subdirectory(makeDatModule)

set(srcs
  makeVelocityDat.cpp
  makeAccelerationDat.cpp
  makeDynamicsDat.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeRlsDynamicsDat_srcs)
set(makeRlsDynamicsDat_srcs
  ${makeRlsDynamicsDat_srcs}
  ${makeDatModule_srcs}
  PARENT_SCOPE
  )
