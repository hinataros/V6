# @author Sho Miyahara 2018

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
  w2dR.cpp
  ddxi2dw.cpp
  round_cast.cpp
  dpInv.cpp
  dN.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" common_srcs)
set(common_srcs ${common_srcs} PARENT_SCOPE)
