# @author Sho Miyahara 2017

add_subdirectory(makeModelDat)
add_subdirectory(makeControllerDat)

set(srcs
  makeModelDat.cpp
  makeControllerDat.cpp
  # makeGifDat.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeDat_srcs)
set(makeDat_srcs ${makeDat_srcs}
  ${makeModelDat_srcs}
  ${makeControllerDat_srcs}
  PARENT_SCOPE
  )
