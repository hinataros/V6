# @author Sho Miyahara 2018

set(srcs
  baseTranslationCP.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" baseTranslation_srcs)
set(baseTranslation_srcs ${baseTranslation_srcs} PARENT_SCOPE)
