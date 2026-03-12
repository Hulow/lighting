idf_component_register(
    SRCS "RMTAdapter.cpp"
    INCLUDE_DIRS "."  # "." means look in this folder for .hpp files
    REQUIRES driver  # ESP-IDF driver component (for RMT)
)