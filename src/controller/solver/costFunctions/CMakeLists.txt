# @author Sho Miyahara 2017

add_subdirectory(pseudoQPpp)
#add_subdirectory(postureGenerator)
add_subdirectory(comWayOpt)

set(srcs

  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" costFunctions_srcs)
set(costFunctions_srcs
  ${costFunctions_srcs}
  ${pseudoQPpp_srcs}
  ${comWayOpt_srcs}
#  ${postureGenerator_srcs}
  PARENT_SCOPE
  )
