# @author Sho Miyahara 2018

add_subdirectory(initialize)
add_subdirectory(rename)
add_subdirectory(index)

set(srcs
  finalize.cpp
  contactCoordinate.cpp
  transform.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controllerTreeModel_srcs)
set(controllerTreeModel_srcs
  ${initialize_srcs}
  ${rename_srcs}
  ${index_srcs}
  ${controllerTreeModel_srcs}
  PARENT_SCOPE
  )
