idf_component_register(
    SRCS "Transceiver.cpp" "Encoder.cpp" "MemoryMonitor.cpp"
    INCLUDE_DIRS "."
    REQUIRES driver 
)