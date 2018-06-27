# @author Sho Miyahara 2017

set(srcs
  des.cpp
  err.cpp
  ref.cpp
  index.cpp
  indexPrint.cpp
  torqueOutputConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" torqueOutputConfig_srcs)
set(torqueOutputConfig_srcs ${torqueOutputConfig_srcs} PARENT_SCOPE)
