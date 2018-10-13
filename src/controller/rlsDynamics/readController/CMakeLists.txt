# @author Sho Miyahara 2018

# add_subdirectory(readYaml)
# add_subdirectory(updateYaml)

set(srcs
  readController.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" readController_srcs)
set(readController_srcs ${readController_srcs} PARENT_SCOPE)
