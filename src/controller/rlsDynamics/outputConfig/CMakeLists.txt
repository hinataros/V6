# @author Sho Miyahara 2018

set(srcs
  des.cpp
  err.cpp
  ref.cpp
  index.cpp
  # indexPrint.cpp
  ext.cpp
  outputConfig.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" outputConfig_srcs)
set(outputConfig_srcs ${outputConfig_srcs} PARENT_SCOPE)
