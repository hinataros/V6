# @author Sho Miyahara 2018

add_subdirectory(initialize)
add_subdirectory(graphMaker)
add_subdirectory(graphConfig)
add_subdirectory(makeMotionYaml)
add_subdirectory(makeEq)
# add_subdirectory(makeGif)

set(srcs
  pushBack.cpp
  finalize.cpp
  runGnuplot.cpp
  output.cpp
  dirCheck.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" output_srcs)
set(output_srcs ${output_srcs}
  ${initialize_srcs}
  ${graphMaker_srcs}
  ${graphConfig_srcs}
  ${makeMotionYaml_srcs}
  ${makeEq_srcs}
  # ${makeGif_srcs}
  PARENT_SCOPE
  )
