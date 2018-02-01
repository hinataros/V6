# @author Sho Miyahara 2017

set(srcs
  math.cpp
  diag.cpp
  antiDiag.cpp
  R.cpp
  cross.cpp
  bb_R.cpp
  bb_T.cpp
  B.cpp
  pInv.cpp
  N.cpp
  Nast.cpp
  R2xi.cpp
  xi2R.cpp
  dxi2w.cpp
  w2dxi.cpp
  ddxi2dw.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" common_srcs)
set(common_srcs ${common_srcs} PARENT_SCOPE)
