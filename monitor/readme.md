O Grafana e o InfluxDB estão hospedados em uma VM na Oracle Cloud, rodando via Docker.

### Links

- Grafana:  
  http://163.176.174.73:3000/

- InfluxDB:  
  http://163.176.174.73:8086/

---

### Grafana

- Usuário: `admin`
- Senha: `admin`

### InfluxDB

- Usuário: `admin`
- Senha: `labyrinth123`

ESP32 -> serial -> ponte.py (seu PC) -> InfluxDB (Oracle Cloud) -> Grafana (Oracle Cloud)

---

## Formato esperado do ESP32

O ESP32 deve enviar uma linha JSON a cada `100ms` pela UART no formato:

```json
{"pitch": 12.5, "roll": -7.3}
```

- `pitch` e `roll` em graus (`float`)
- Baud rate: `115200`
- Uma linha por envio, terminada com `\n`

---
É necessário ajustar a porta serial no arquivo `ponte.py`.
