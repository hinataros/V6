# @author Sho Miyahara 2017

set(srcs
  desiredBaseTranslationGeneratorCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredBaseTranslationGenerator_srcs)
set(desiredBaseTranslationGenerator_srcs ${desiredBaseTranslationGenerator_srcs} PARENT_SCOPE)
