# @author Sho Miyahara 2017

add_subdirectory(identityVectorMethod)
add_subdirectory(analyticalDynamics)

set(dynamics_srcs ${dynamics_srcs}
  ${analyticalDynamics_srcs}
  ${identityVectorMethod_srcs}
  PARENT_SCOPE
  )
