if(rls_thirdparty_yaml-cpp_compile)
  add_subdirectory(yaml-cpp)
endif()

if(rls_thirdparty_quaternion_compile)
  add_subdirectory(quaternion)
endif()

if(rls_thirdparty_QuadProgpp_compile)
  add_subdirectory(QuadProgpp)
endif()
