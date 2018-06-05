# @author Sho Miyahara 2018

set(srcs
  baseTransDes.cpp
  baseRotDes.cpp
  comDes.cpp
  dcmDes.cpp
  eeTransDes.cpp
  eeRotDes.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" des_srcs)
set(des_srcs ${des_srcs} PARENT_SCOPE)
