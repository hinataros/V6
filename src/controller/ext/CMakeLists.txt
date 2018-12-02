# @author Sho Miyahara 2018

add_subdirectory(stateTrigger)
add_subdirectory(controlMethod)

set(srcs
  ext.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" ext_srcs)
set(ext_srcs
  ${stateTrigger_srcs}
  ${controlMethod_srcs}
  ${ext_srcs}
  PARENT_SCOPE
  )

add_subdirectory(datConfig)
set(extDat_srcs ${extDat_srcs} PARENT_SCOPE)
