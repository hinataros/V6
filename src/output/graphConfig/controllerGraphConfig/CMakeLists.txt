# @author Sho Miyahara 2018

add_subdirectory(des)
add_subdirectory(err)
add_subdirectory(ref)
# add_subdirectory(index)
add_subdirectory(master)
add_subdirectory(walking)

# add_subdirectory(gif)

set(srcs
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controllerGraphConfig_srcs)
set(controllerGraphConfig_srcs
  ${des_srcs}
  ${err_srcs}
  ${ref_srcs}
  ${index_srcs}
  ${walking_srcs}
  ${gif_srcs}
  ${controllerGraphConfig_srcs}
  PARENT_SCOPE
  )
