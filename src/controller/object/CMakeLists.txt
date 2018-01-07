# @author Sho Miyahara 2017


set(srcs
  )

if(rls_objectRTC)
  add_subdirectory(RTC)
  set(objectRTCCore_srcs ${objectRTCCore_srcs} PARENT_SCOPE)
endif(rls_objectRTC)

# MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsDynamics_srcs)
# set(rlsDynamics_srcs
#   ${rlsDynamics_srcs}
#   ${reference_srcs}
#   ${control_srcs}
#   ${index_srcs}
#   ${outputConfig_srcs}
#   PARENT_SCOPE
#   )
