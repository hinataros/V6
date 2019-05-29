# @author Sho Miyahara 2018

set(srcs
  baseTranslationDefault.cpp
  baseRotationDefault.cpp
  controlNodeTranslationDefault.cpp
  controlNodeRotationDefault.cpp
  controlNodeForceDefault.cpp
  controlNodeMomentDefault.cpp
  comDefault.cpp
  dcmDefault.cpp
  externalWrenchDefault.cpp
  zeroToOneSpline.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" default_srcs)
set(default_srcs ${default_srcs} PARENT_SCOPE)
