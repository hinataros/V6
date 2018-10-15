# @author Sho Miyahara 2018

set(srcs
  mixedQuasiAccRef.cpp
  mixedQuasiAccOptRef.cpp
  rcMomRef.cpp
  eeWrenchRef.cpp
  extWrenchRef.cpp
  jointTorque.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" ref_srcs)
set(ref_srcs ${ref_srcs} PARENT_SCOPE)
