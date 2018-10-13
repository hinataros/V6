# @author Sho Miyahara 2018

add_subdirectory(controllerTreeModel)

set(srcs
  initialize.cpp
  finalize.cpp
  setModel.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" model_srcs)
set(model_srcs
  ${controllerTreeModel_srcs}
  ${model_srcs}
  PARENT_SCOPE
  )
