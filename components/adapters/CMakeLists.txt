idf_component_register(
    SRCS "RMTMapper.cpp" "WS2815Encoder.cpp" "RMTAdapter.cpp"
    INCLUDE_DIRS "."
    REQUIRES driver 
)