# Labirinto — Mesa 3D 

Visualização 3D em tempo real da orientação de uma mesa controlada por ESP32, usando InfluxDB e Grafana.

```
ESP32 → serial → ponte.py (seu PC) → InfluxDB → Grafana
```

- necessário Docker e Docker Compose instalados 

---

## Subindo os serviços

```bash
docker compose up -d
```

Isso sobe o **InfluxDB** (porta `8086`) e o **Grafana** (porta `3000`) localmente.

| Serviço  | URL                        | Usuário | Senha          |
|----------|----------------------------|---------|----------------|
| Grafana  | http://localhost:3000      | admin   | admin          |
| InfluxDB | http://localhost:8086      | admin   | labyrinth123   |

> O arquivo STL da mesa precisa estar em `./assets/mesa.stl` para ser servido pelo Grafana.

---

### Formato esperado do ESP32

O ESP32 deve enviar uma linha JSON a cada `100ms` via UART:

```json
{"pitch": 12.5, "roll": -7.3}
```

- Valores em graus (`float`)
- Baud rate: `115200`
- Uma linha por envio, terminada com `\n`

