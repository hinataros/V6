# @author Sho Miyahara 2017

add_subdirectory(makeDat)
add_subdirectory(makeGp)
add_subdirectory(makeTex)
add_subdirectory(makeMotionYaml)
# add_subdirectory(makeGif)

set(srcs
  pushBack.cpp
  finalize.cpp
  makeGraph.cpp
  # makeMotionYaml.cpp
  output.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" output_srcs)
set(output_srcs ${output_srcs}
  ${makeDat_srcs}
  ${makeGp_srcs}
  ${makeTex_srcs}
  ${makeMotionYaml_srcs}
  # ${makeGif_srcs}
  PARENT_SCOPE
  )
