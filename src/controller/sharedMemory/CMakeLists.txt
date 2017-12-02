set(srcs
  initialize.cpp
  finalize.cpp
  putData.cpp
  getData.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" sharedMemory_srcs)
set(sharedMemory_srcs ${sharedMemory_srcs} PARENT_SCOPE)
