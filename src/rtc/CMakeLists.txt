# @author Sho Miyahara 2018

if(rls_rlsDynamicsRTC)
  add_subdirectory(rlsDynamics)
  set(rlsDynamicsRTCCore_srcs ${rlsDynamicsRTCCore_srcs} PARENT_SCOPE)
endif(rls_rlsDynamicsRTC)
