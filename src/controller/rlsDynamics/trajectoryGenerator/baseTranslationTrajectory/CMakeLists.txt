# @author Sho Miyahara 2017

set(srcs
  baseTranslationTrajectoryCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" baseTranslationTrajectory_srcs)
set(baseTranslationTrajectory_srcs ${baseTranslationTrajectory_srcs} PARENT_SCOPE)
