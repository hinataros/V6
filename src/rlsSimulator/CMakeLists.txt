set(srcs
  initialize.cpp
  initialParameter.cpp
  runge4.cpp
  linkEqs.cpp
  diffEqs.cpp
  integrator.cpp
  se3exp.cpp
  update.cpp
  run.cpp
  finalize.cpp
  main.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" rlsSimulator_srcs)
set(rlsSimulator_srcs ${rlsSimulator_srcs} PARENT_SCOPE)
