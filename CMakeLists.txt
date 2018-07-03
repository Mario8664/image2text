cmake_minimum_required (VERSION 2.8)
project (image2text)

find_package( OpenCV REQUIRED )

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_compile_options(-std=gnu++11)


INCLUDE_DIRECTORIES(  ${PROJECT_SOURCE_DIR}/include )
LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/lib )

aux_source_directory (./src DIR_SRCS)
add_subdirectory(CharGrayRatioCalculator)
add_executable (image2text ${DIR_SRCS})

target_link_libraries(image2text CalcGray ${OpenCV_LIBS} )