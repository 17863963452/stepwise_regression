aux_source_directory(. DIR_LIB_SRCS)
link_libraries(m)
add_library(mean_module ${DIR_LIB_SRCS})
