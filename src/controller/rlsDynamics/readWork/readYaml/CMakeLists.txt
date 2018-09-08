# @author Sho Miyahara 2017

add_subdirectory(readValue)

# set(srcs
  # )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" readYaml_srcs)
set(readYaml_srcs
  ${readValue_srcs}
  ${readYaml_srcs}
  PARENT_SCOPE
  )
