# @author Sho Miyahara 2017

set(srcs
  baseTransDes.cpp
  baseRotDes.cpp
  eeTransDes.cpp
  eeRotDes.cpp
  dcmDes.cpp
  baseTransErr.cpp
  baseRotErr.cpp
  comErr.cpp
  dcmErr.cpp
  eeTransErr.cpp
  eeWrenchErr.cpp
  rcMomRef.cpp
  eeWrenchRef.cpp
  extWrenchRef.cpp
  jointTorque.cpp
  formulatedMom.cpp
  localCop.cpp
  cop.cpp
  stabilityIndex.cpp
  footPrint.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" makeDatModule_srcs)
set(makeDatModule_srcs ${makeDatModule_srcs} PARENT_SCOPE)
