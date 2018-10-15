# @author Sho Miyahara 2018

set(srcs
  initialize.cpp
  resize.cpp
  readModel.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rigidBodyModel_srcs)
set(rigidBodyModel_srcs ${rigidBodyModel_srcs} PARENT_SCOPE)
