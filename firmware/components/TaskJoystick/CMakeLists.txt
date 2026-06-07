idf_component_register(
    SRCS "TaskJoystick.c"
    INCLUDE_DIRS "."
    REQUIRES global_data adc config queues mutexes
)
