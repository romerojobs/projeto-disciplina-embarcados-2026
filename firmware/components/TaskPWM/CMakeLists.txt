idf_component_register(
    SRCS "TaskPWM.c"
    INCLUDE_DIRS "."
    REQUIRES joystick config queues pwm
)