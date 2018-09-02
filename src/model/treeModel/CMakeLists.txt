# @author Sho Miyahara 2017

add_subdirectory(initialize)
add_subdirectory(readYaml)
add_subdirectory(interface)

add_subdirectory(kinematics)
add_subdirectory(dynamics)

set(srcs
  outputConfig.cpp
  deleteModel.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" treeModel_srcs)
set(treeModel_srcs ${treeModel_srcs}
  ${initialize_srcs}
  ${readYaml_srcs}
  ${interface_srcs}
  ${kinematics_srcs}
  ${dynamics_srcs}
  PARENT_SCOPE
  )
