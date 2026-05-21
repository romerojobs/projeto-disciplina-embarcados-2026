O Grafana e o InfluxDB estão hospedados em uma VM na Oracle Cloud, rodando via Docker

http://163.176.174.73:3000/ -> Grafana
http://163.176.174.73:8086 -> InfluxDB

Login Grafana:
Usuário: admin
Senha: 1507

Login InfluxDB:
Usuário: admin
Senha: labyrinth123

ESP32 -> serial -> ponte.py (seu PC) -> InfluxDB (Oracle Cloud) -> Grafana (Oracle Cloud)

O ESP32 deve enviar uma linha JSON a cada 100ms pela UART, no formato:
```{"pitch": 12.5, "roll": -7.3}```

- pitch e roll em graus (float)
- Baud rate: 115200
- Uma linha por envio, terminada com \n

necessário ajustar a porta serial no arquivo ponte.py