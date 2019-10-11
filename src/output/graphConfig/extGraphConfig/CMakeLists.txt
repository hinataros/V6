# @author Ryotaro Hinata 2019

set(srcs
  jointLimitGradient.cpp
  jointLimitGradient_wTorso.cpp
  jointLimitGradient_wTorso3.cpp
  jointLimitGradient_wTorso1.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" extGraphConfig_srcs)
set(extGraphConfig_srcs
  ${extGraphConfig_srcs}
  PARENT_SCOPE
  )
