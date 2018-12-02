# @author Sho Miyahara 2018

add_subdirectory(initialize)
add_subdirectory(update)

set(srcs
  finalize.cpp
  reconfigure.cpp
  getControlNode.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" constraintModel_srcs)
set(constraintModel_srcs
  ${initialize_srcs}
  ${update_srcs}
  ${constraintModel_srcs}
  PARENT_SCOPE
  )
