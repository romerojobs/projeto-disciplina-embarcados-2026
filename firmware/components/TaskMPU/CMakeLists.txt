idf_component_register(
    SRCS "TaskMPU.c"
    INCLUDE_DIRS "."
    REQUIRES global_data mpu mutexes config
)
