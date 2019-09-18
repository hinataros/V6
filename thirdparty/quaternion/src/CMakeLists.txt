# @author Sho Miyahara 2018

set(srcs
  operator.cpp
  rotationMatrix.cpp
  zero.cpp
  identity.cpp
  xi2q.cpp
  R2q.cpp
  dq2w.cpp
  ddq2dw.cpp
  inverse.cpp
  sign.cpp
  )

macro(MAP_ADD_STR _list _str _output)
    set(${_output})
    foreach(_item ${${_list}})
        set(${_output} ${${_output}} ${_str}${_item})
    endforeach(_item)
endmacro(MAP_ADD_STR)

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" library_sources)
set(library_sources ${library_sources} PARENT_SCOPE)
