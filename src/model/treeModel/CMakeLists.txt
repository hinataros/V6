# @author Sho Miyahara 2018

add_subdirectory(resize)
add_subdirectory(readYaml)
add_subdirectory(interface)

add_subdirectory(kinematics)
add_subdirectory(dynamics)

set(srcs
  initialize.cpp
  finalize.cpp
  outputConfig.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" treeModel_srcs)
set(treeModel_srcs
  ${resize_srcs}
  ${readYaml_srcs}
  ${interface_srcs}
  ${kinematics_srcs}
  ${dynamics_srcs}
  ${treeModel_srcs}
  PARENT_SCOPE
  )
