# @author Sho Miyahara 2017

set(srcs
  readModel.cpp
  initialize.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rigidBodyModel_srcs)
set(rigidBodyModel_srcs ${rigidBodyModel_srcs}
  PARENT_SCOPE
  )
