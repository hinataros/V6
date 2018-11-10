# @author Sho Miyahara 2018

set(srcs
  finalize.cpp
  readController.cpp
  update.cpp
  mapping.cpp
  desiredValueGenerator.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" desiredValueGenerator_srcs)

set(desiredValueGenerator_srcs ${desiredValueGenerator_srcs} PARENT_SCOPE)
