# @author Sho Miyahara 2018

add_subdirectory(checkValue)

set(srcs
  initialize.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" yamlInfo_srcs)
set(yamlInfo_srcs ${checkValue_srcs} ${yamlInfo_srcs} PARENT_SCOPE)
