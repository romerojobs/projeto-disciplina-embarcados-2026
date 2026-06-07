idf_component_register(
    SRCS "serial.c"
    INCLUDE_DIRS "."
    REQUIRES driver global_data config
    PRIV_REQUIRES esp_driver_uart
)
