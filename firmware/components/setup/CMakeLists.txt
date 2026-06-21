idf_component_register(
    SRCS "setup.c"
    INCLUDE_DIRS "."
    REQUIRES TaskPWM TaskSerial TaskJoystick TaskMPU TaskVitoria gpio serial queues pwm mutexes global_data adc mpu
)
