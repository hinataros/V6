# @author Sho Miyahara 2018

# add_subdirectory(readYaml)
# add_subdirectory(updateYaml)

set(srcs
  setControllerMap.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" extWrapper_srcs)
set(extWrapper_srcs ${extWrapper_srcs} PARENT_SCOPE)
