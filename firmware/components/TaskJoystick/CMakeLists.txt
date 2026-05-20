idf_component_register(
    SRCS "TaskJoystick.c"
    INCLUDE_DIRS "."
    REQUIRES joystick adc config queues
)