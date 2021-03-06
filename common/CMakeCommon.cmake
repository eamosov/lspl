SET(Boost_USE_STATIC_LIBS TRUE)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb")

SET(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_library(PCRE NAMES libpcre.a HINTS /usr/local/lib )
find_library(PCRECPP NAMES libpcrecpp.a HINTS /usr/local/lib )

link_directories(
    ${CMAKE_SOURCE_DIR}/../deps/aot/Source/AgramtabLib/
    ${CMAKE_SOURCE_DIR}/../deps/aot/Source/GraphanLib/
    ${CMAKE_SOURCE_DIR}/../deps/aot/Source/LemmatizerLib/
    ${CMAKE_SOURCE_DIR}/../deps/aot/Source/MorphWizardLib/
    ${CMAKE_SOURCE_DIR}/../deps/aot/Source/StructDictLib/
)

if(WIN32)
    include_directories( ../core/src/main/ ../deps/ ../deps-win32/include/ ${Boost_INCLUDE_DIR} )

    link_directories(
        ${CMAKE_SOURCE_DIR}/../deps-win32/lib/
        ${CMAKE_SOURCE_DIR}/../core/build-win32/
    )

    SET(MY_TARGETLIB_PREFIX "")
    SET(MY_TARGETLIB_SUFFIX ".dll")
elseif(APPLE)
    include_directories( ../core/src/main/ ../deps/ ${Boost_INCLUDE_DIRS} )

    link_directories(
        ${CMAKE_SOURCE_DIR}/../core/build-mac/
        ${Boost_LIBRARY_DIRS}
    )

    SET(MY_TARGETLIB_PREFIX "lib")
    SET(MY_TARGETLIB_SUFFIX ".so")
else(WIN32)
    include_directories( ../core/src/main/ ../deps/ ${Boost_INCLUDE_DIR} )

    link_directories(
        ${CMAKE_SOURCE_DIR}/../core/build-linux64/
    )

    SET(MY_TARGETLIB_PREFIX "lib")
    SET(MY_TARGETLIB_SUFFIX ".so")
endif(WIN32)
