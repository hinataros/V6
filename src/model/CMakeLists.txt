add_subdirectory(treeModel)

set(srcs
  readModel.cpp
  deleteModel.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" model_srcs)
set(model_srcs ${model_srcs}
  ${treeModel_srcs}
  PARENT_SCOPE
  )
