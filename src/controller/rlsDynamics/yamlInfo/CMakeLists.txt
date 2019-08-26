# @author Sho Miyahara 2018

add_subdirectory(checkSize)
add_subdirectory(checkValue)
add_subdirectory(checkUserValue)

set(srcs
  initialize.cpp
  reset.cpp
  docDist.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" yamlInfo_srcs)
set(yamlInfo_srcs
  ${checkSize_srcs}
  ${checkValue_srcs}
  ${checkUserValue_srcs}
  ${yamlInfo_srcs}
  PARENT_SCOPE
  )
