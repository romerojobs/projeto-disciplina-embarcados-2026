idf_component_register(
    SRCS "setup.c"
    INCLUDE_DIRS "."
    REQUIRES TaskPWM TaskSerial TaskJoystick serial queues pwm mutexes joystick adc
)