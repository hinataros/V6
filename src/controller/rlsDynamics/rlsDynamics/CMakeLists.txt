# @author Sho Miyahara 2018

add_subdirectory(initialize)

set(srcs
  finalize.cpp
  rlsDynamics.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsDynamics_srcs)

set(rlsDynamics_srcs
  ${initialize_srcs}
  ${rlsDynamics_srcs}
  PARENT_SCOPE
  )
