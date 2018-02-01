# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

# @rewrite Sho Miyahara 2017

file(GLOB sources *.cpp)
file(GLOB headers *.hpp)
set(library_sources ${sources})
list(REMOVE_ITEM library_sources ${CMAKE_CURRENT_SOURCE_DIR}/qptest.cpp)

add_definitions(-fPIC)

add_library(quadprog STATIC ${library_sources} ${headers})

if(rls_thirdparty_QuadProgpp_sample)
  set_property(TARGET quadprog PROPERTY POSITION_INDEPENDENT_CODE 1)
  set_property(TARGET quadprog PROPERTY PUBLIC_HEADER ${headers})

  add_executable(qpsample main.cpp ${headers})
  target_link_libraries(qpsample quadprog)
endif()

# install(TARGETS quadprog
#   EXPORT quadprog-targets
#   RUNTIME DESTINATION bin
#   PUBLIC_HEADER DESTINATION include/QuadProg++
#   LIBRARY DESTINATION lib
#   ARCHIVE DESTINATION lib)

# install(EXPORT quadprog-targets DESTINATION cmake)
