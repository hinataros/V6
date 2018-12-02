# @author Sho Miyahara 2018

add_subdirectory(checkUserSize)
add_subdirectory(checkValue)
add_subdirectory(checkUserValue)

set(srcs
  initialize.cpp
  reset.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" yamlInfo_srcs)
set(yamlInfo_srcs
  ${checkUserSize_srcs}
  ${checkValue_srcs}
  ${checkUserValue_srcs}
  ${yamlInfo_srcs}
  PARENT_SCOPE
  )
