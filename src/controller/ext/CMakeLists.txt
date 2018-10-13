# @author Sho Miyahara 2018

add_subdirectory(initialize)

# set(srcs
#   )

# MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" ext_srcs)

set(ext_srcs
  ${initialize_srcs}
  ${ext_srcs}
  PARENT_SCOPE
  )
