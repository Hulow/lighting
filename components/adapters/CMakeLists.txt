idf_component_register(
    SRCS "RMTMapper.cpp" "RMTEncoder.cpp" "RMTAdapter.cpp"
    INCLUDE_DIRS "."
    REQUIRES driver 
)