# @author Sho Miyahara 2018

set(srcs
  # makeGifDat.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" gifConfig_srcs)
set(gifConfig_srcs ${gifConfig_srcs} PARENT_SCOPE)
