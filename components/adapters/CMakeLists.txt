idf_component_register(
    SRCS "RMTMapper.cpp" "RMTEncoder.cpp" "RMTAdapter.cpp" "Transceiver.cpp" "Encoder.cpp"
    INCLUDE_DIRS "."
    REQUIRES driver 
)