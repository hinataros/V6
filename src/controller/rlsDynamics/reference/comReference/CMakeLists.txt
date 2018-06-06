# @author Sho Miyahara 2017

set(srcs
  comSequence.cpp
  dcm2com.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" comReference_srcs)
set(comReference_srcs ${comReference_srcs} PARENT_SCOPE)
