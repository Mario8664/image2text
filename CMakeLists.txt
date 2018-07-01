cmake_minimum_required (VERSION 2.8)
project (image2text)
aux_source_directory (./src DIR_SRCS)
add_subdirectory(CharGrayRatioCalculator)
add_executable (image2text ${DIR_SRCS})
target_link_libraries(image2text CalcGray)

