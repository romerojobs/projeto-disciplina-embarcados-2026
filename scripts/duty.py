PWM_FREQ = 50
PWM_RESOLUTION = 4096

SERVO_MAX_ANGLE = 180.0

PWM_PERIOD_MS = 1000.0 / PWM_FREQ


def angle_to_duty(angle, pulse_min, pulse_max):
    """
    Converte ângulo -> duty PWM
    """

    # Limita o ângulo
    angle = max(0.0, min(angle, SERVO_MAX_ANGLE))

    # Range do pulso
    pulse_range = pulse_max - pulse_min

    # Ângulo -> tempo HIGH
    pulse_ms = (
        pulse_min +
        (angle / SERVO_MAX_ANGLE) * pulse_range
    )

    # tempo HIGH -> duty
    duty = int(
        (pulse_ms / PWM_PERIOD_MS)
        * PWM_RESOLUTION
    )

    return duty, pulse_ms


def calcular_servo(
    nome_servo,
    pulse_min,
    pulse_max,
    angulo_min,
    angulo_max
):
    """
    Calcula:
        - duty mínimo
        - duty máximo
        - duty central
    """

    angulo_meio = (
        angulo_min + angulo_max
    ) / 2.0

    # Mínimo
    duty_min, pulse_min_calc = angle_to_duty(
        angulo_min,
        pulse_min,
        pulse_max
    )

    # Meio
    duty_mid, pulse_mid = angle_to_duty(
        angulo_meio,
        pulse_min,
        pulse_max
    )

    # Máximo
    duty_max, pulse_max_calc = angle_to_duty(
        angulo_max,
        pulse_min,
        pulse_max
    )

    # Prints
    print("\n==============================")
    print(nome_servo)
    print("==============================")

    print(f"\nÂngulo mínimo : {angulo_min:.1f}°")
    print(f"Pulso mínimo  : {pulse_min_calc:.3f} ms")
    print(f"Duty mínimo   : {duty_min}")

    print(f"\nÂngulo central: {angulo_meio:.1f}°")
    print(f"Pulso central : {pulse_mid:.3f} ms")
    print(f"Duty central  : {duty_mid}")

    print(f"\nÂngulo máximo : {angulo_max:.1f}°")
    print(f"Pulso máximo  : {pulse_max_calc:.3f} ms")
    print(f"Duty máximo   : {duty_max}")


# ================= ENTRADA =================

while True:
  angulo_min = float(
      input("Digite o ângulo mínimo: ")
  )

  angulo_max = float(
      input("Digite o ângulo máximo: ")
  )

  # ================= SERVO 1 =================
  # Servo padrão: 1ms -> 2ms

  calcular_servo(
      nome_servo="SERVO 1 (1ms até 2ms)",
      pulse_min=1.0,
      pulse_max=2.0,
      angulo_min=angulo_min,
      angulo_max=angulo_max
  )

  # ================= SERVO 2 =================
  # Servo ampliado: 0.5ms -> 2.4ms

  calcular_servo(
      nome_servo="SERVO 2 (0.5ms até 2.4ms)",
      pulse_min=0.5,
      pulse_max=2.4,
      angulo_min=angulo_min,
      angulo_max=angulo_max
  )
