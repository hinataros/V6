# @author Sho Miyahara 2018

# add_subdirectory(velocityGraphConfig)
# add_subdirectory(accelerationGraphConfig)
# add_subdirectory(torqueGraphConfig)

set(srcs
  use_func.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" activate_srcs)
set(activate_srcs ${activate_srcs} PARENT_SCOPE)
