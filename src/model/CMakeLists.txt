# @author Sho Miyahara 2018

add_subdirectory(worldModel)
add_subdirectory(treeModel)
add_subdirectory(rigidBodyModel)
add_subdirectory(model)

# set(srcs
#   )

# MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" model_srcs)

set(model_srcs
  ${worldModel_srcs}
  ${treeModel_srcs}
  ${rigidBodyModel_srcs}
  ${model_srcs}
  PARENT_SCOPE
  )
