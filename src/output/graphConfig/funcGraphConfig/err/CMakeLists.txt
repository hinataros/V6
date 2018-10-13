# @author Sho Miyahara 2018

set(srcs
  baseTransErr.cpp
  baseRotErr.cpp
  comErr.cpp
  dcmErr.cpp
  eeTransErr.cpp
  eeRotErr.cpp
  eeWrenchErr.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" err_srcs)
set(err_srcs ${err_srcs} PARENT_SCOPE)
