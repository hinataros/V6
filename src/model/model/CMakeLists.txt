# @author Sho Miyahara 2018

set(srcs
  initialize.cpp
  finalize.cpp
  initializeInfo.cpp
  makeModel.cpp
  setID.cpp
  initialUpdate.cpp
  update.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" model_srcs)
set(model_srcs ${model_srcs} PARENT_SCOPE)
