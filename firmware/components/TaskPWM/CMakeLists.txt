idf_component_register(
    SRCS "TaskPWM.c"
    INCLUDE_DIRS "."
    REQUIRES global_data config queues pwm
)
