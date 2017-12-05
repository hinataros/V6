set(srcs
  baseTransDes.cpp
  baseRotDes.cpp
  eeTransDes.cpp
  eeRotDes.cpp
  baseTransErr.cpp
  baseRotErr.cpp
  comErr.cpp
  eeTransErr.cpp
  eeWrenchErr.cpp
  rcMomRef.cpp
  eeWrenchRef.cpp
  jointTorque.cpp
  formulatedMom.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeDatModule_srcs)
set(makeDatModule_srcs ${makeDatModule_srcs} PARENT_SCOPE)
