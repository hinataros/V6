# @author Sho Miyahara 2017

add_subdirectory(baseTranslationReference)
add_subdirectory(baseOrientationReference)
add_subdirectory(comReference)
add_subdirectory(dcmReference)
add_subdirectory(endEffectorReference)
add_subdirectory(externalWrenchReference)

set(srcs
  spatialReference.cpp
  reference.cpp
  )

MAP_ADD_STR(srcs "${CMAKE_CURRENT_SOURCE_DIR}/" reference_srcs)
set(reference_srcs
  ${baseTranslationReference_srcs}
  ${baseOrientationReference_srcs}
  ${comReference_srcs}
  ${dcmReference_srcs}
  ${endEffectorReference_srcs}
  ${externalWrenchReference_srcs}
  ${reference_srcs}
  PARENT_SCOPE
  )
