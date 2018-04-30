# @author Sho Miyahara 2018

add_subdirectory(graphMaker)
add_subdirectory(graphConfig)
add_subdirectory(makeMotionYaml)
# add_subdirectory(makeGif)

set(srcs
  pushBack.cpp
  finalize.cpp
  runGnuplot.cpp
  output.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" output_srcs)
set(output_srcs ${output_srcs}
  ${graphMaker_srcs}
  ${graphConfig_srcs}
  ${makeMotionYaml_srcs}
  # ${makeGif_srcs}
  PARENT_SCOPE
  )
