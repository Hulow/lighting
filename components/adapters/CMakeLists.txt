idf_component_register(
    SRCS "BitToRMTMapper.cpp" "WS2815Encoder.cpp" "RMTAdapter.cpp"
    INCLUDE_DIRS "."
    REQUIRES driver 
)