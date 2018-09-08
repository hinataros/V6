# @author Sho Miyahara 2017

set(srcs
  intIntString.cpp
  intIntStringInt.cpp
  intIntStringIntInt.cpp
  intIntStringIntString.cpp
  intIntStringString.cpp
  intIntStringStringInt.cpp
  intIntStringStringString.cpp
  intString.cpp
  intStringInt.cpp
  intStringIntInt.cpp
  intStringIntString.cpp
  intStringString.cpp
  intStringStringInt.cpp
  intStringStringString.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" readValue_srcs)
set(readValue_srcs ${readValue_srcs} PARENT_SCOPE)
