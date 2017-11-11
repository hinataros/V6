set(srcs
  baseTransDes.cpp
  baseRotDes.cpp
  eeTransDes.cpp
  eeRotDes.cpp
  baseTransErr.cpp
  baseRotErr.cpp
  comErr.cpp
  rcMomRef.cpp
  eeWrenchRef.cpp
  formulatedMom.cpp
  makeDynamicsDat.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeDynamicsDat_srcs)
set(makeDynamicsDat_srcs ${makeDynamicsDat_srcs} PARENT_SCOPE)
