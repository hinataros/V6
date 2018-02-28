# @author Sho Miyahara 2017

set(srcs
  baseTranslationSequence.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" baseTranslationReference_srcs)
set(baseTranslationReference_srcs ${baseTranslationReference_srcs} PARENT_SCOPE)
