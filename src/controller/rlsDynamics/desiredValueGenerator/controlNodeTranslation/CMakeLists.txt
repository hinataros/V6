# @author Sho Miyahara 2018

set(srcs
  controlNodeTranslationCP.cpp
  controlNodeTranslationCPabs.cpp
  controlNodeTranslationSwing.cpp
  # controlNodeTranslationWalkingToeoff.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" controlNodeTranslation_srcs)
set(controlNodeTranslation_srcs ${controlNodeTranslation_srcs} PARENT_SCOPE)
