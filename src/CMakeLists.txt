if(DEFINED OPENRTM_INCLUDE_DIRS)
  string(REGEX REPLACE "-I" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
endif(DEFINED OPENRTM_INCLUDE_DIRS)

if (DEFINED OPENRTM_LIBRARY_DIRS)
  string(REGEX REPLACE "-L" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
endif (DEFINED OPENRTM_LIBRARY_DIRS)

if (DEFINED OPENRTM_LIBRARIES)
  string(REGEX REPLACE "-l" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
endif (DEFINED OPENRTM_LIBRARIES)

include_directories(${PROJECT_SOURCE_DIR}/include)
# include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
# include_directories(${PROJECT_BINARY_DIR})
# include_directories(${PROJECT_BINARY_DIR}/idl)
# include_directories(${OPENRTM_INCLUDE_DIRS})
# include_directories(${OMNIORB_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include/model)
include_directories(${PROJECT_SOURCE_DIR}/include/model/treeModel)
include_directories(${PROJECT_SOURCE_DIR}/include/interpolation)

include_directories(${PROJECT_SOURCE_DIR}/include/controller)
include_directories(${PROJECT_SOURCE_DIR}/include/controller/rlsVelocity)
include_directories(${PROJECT_SOURCE_DIR}/include/controller/rlsAcceleration)
include_directories(${PROJECT_SOURCE_DIR}/include/controller/rlsDynamics)

include_directories(${OPENRTM_INCLUDE_DIRS})

add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})
add_definitions("-O2 -MMD -MP -Wall -Wextra -std=c++11")

# MAP_ADD_STR(comp_hdrs "../" comp_headers)

# link_directories(${OPENRTM_LIBRARY_DIRS})
# link_directories(${OMNIORB_LIBRARY_DIRS})
# link_directories(/usr/local/lib)

link_directories(${CMAKE_BINARY_DIR}/thirdparty/yaml-cpp)

set(LDFLAGS yaml-cpp)

add_subdirectory(config)
add_subdirectory(info)
add_subdirectory(common)
add_subdirectory(model)
add_subdirectory(output)
set(sources
  ${config_srcs}
  ${info_srcs}
  ${common_srcs}
  ${model_srcs}
  ${output_srcs}
  )

add_subdirectory(controller)

if(rls_rlsDynamicsRTC)
  set(RTC_NAME "rlsDynamicsRTC")
  add_definitions(-DCHOREONOID)

  set(comp_srcs ${comp_srcs} ${sources})

  add_library(${RTC_NAME} ${LIB_TYPE} ${comp_srcs})
  target_link_libraries(${RTC_NAME} ${LDFLAGS})
  set_target_properties(${RTC_NAME} PROPERTIES PREFIX "")
endif(rls_rlsDynamicsRTC)

if(rls_rlsSimulator)
  add_subdirectory(rlsSimulator)

  set(comp_srcs
    ${sources}
    ${controllerComp_srcs}
    ${rlsSimulator_srcs}
    )

  add_executable(main ${comp_srcs})
  target_link_libraries(main ${LDFLAGS})
endif(rls_rlsSimulator)

# add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
#   ${comp_headers} ${ALL_IDL_SRCS})
# set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
# set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
# if(NOT TARGET ALL_IDL_TGT)
#   add_custom_target(ALL_IDL_TGT)
# endif(NOT TARGET ALL_IDL_TGT)
# add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
# target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES} ${LDFLAGS})

# set(standalone_srcs rlsComp.cpp)

# add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
#   ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS})
# target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES} ${LDFLAGS})

# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
#     EXPORT ${PROJECT_NAME}
#     RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT component
#     LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT component
#     ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT component)
# install(EXPORT ${PROJECT_NAME}
#     DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
#     FILE ${PROJECT_NAME}Depends.cmake)
