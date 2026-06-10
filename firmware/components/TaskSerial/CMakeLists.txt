idf_component_register(
    SRCS "TaskSerial.c"
    INCLUDE_DIRS "."
    REQUIRES global_data config mutexes serial
)
