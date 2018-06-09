# @author Sho Miyahara 2017

set(srcs
  cop.cpp
  cmp.cpp
  dcm.cpp
  index.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" index_srcs)
set(index_srcs ${index_srcs} PARENT_SCOPE)
