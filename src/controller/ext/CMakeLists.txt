# @author Sho Miyahara 2018

add_subdirectory(controlMethod)

set(srcs
  ext.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" ext_srcs)
set(ext_srcs
  ${controlMethod_srcs}
  ${ext_srcs}
  PARENT_SCOPE
  )

set(srcs setDat.cpp)
MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" extDat_srcs)
set(extDat_srcs ${extDat_srcs} PARENT_SCOPE)
