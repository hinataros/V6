# @author Sho Miyahara 2018

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
  eeRotErr.cpp
  eeWrenchErr.cpp
  rcMomRef.cpp
  eeWrenchRef.cpp
  extWrenchRef.cpp
  jointTorque.cpp
  # formulatedMom.cpp
  localCop.cpp
  netCop.cpp
  stabilityIndex.cpp
  # footPrint.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" graphConfig_srcs)
set(graphConfig_srcs ${graphConfig_srcs} PARENT_SCOPE)
