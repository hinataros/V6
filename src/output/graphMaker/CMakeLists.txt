# @author Sho Miyahara 2018

add_subdirectory(datMaker)
add_subdirectory(gpMaker)
add_subdirectory(texMaker)

set(graphMaker_srcs ${graphMaker_srcs}
  ${datMaker_srcs}
  ${gpMaker_srcs}
  ${texMaker_srcs}
  PARENT_SCOPE
  )
