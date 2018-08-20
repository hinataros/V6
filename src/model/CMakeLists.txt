# @author Sho Miyahara 2017

add_subdirectory(treeModel)
# add_subdirectory(rigidBodyModel)

set(srcs
  readModel.cpp
  # deleteModel.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" model_srcs)
set(model_srcs ${model_srcs}
  ${treeModel_srcs}
  ${rigidBodyModel_srcs}
  PARENT_SCOPE
  )
