# @author Sho Miyahara 2018

add_subdirectory(controllerTreeModel)

set(srcs
  initialize.cpp
  finalize.cpp
  setModel.cpp
  update.cpp
  originReset.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controllerModel_srcs)
set(controllerModel_srcs
  ${controllerTreeModel_srcs}
  ${controllerModel_srcs}
  PARENT_SCOPE
  )
