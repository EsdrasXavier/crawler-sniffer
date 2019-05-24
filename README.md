# Crawler-sniffer

## Hardware utilizado
- Arduino uno
- Ponte H VNH2SP30
- Módulo bluetooth HC-05

## Definição de pinos

| Pino | Função |
| :--: | :----: |
| 6 | PWM |
| 5 | INA |
| 2 | INB |
| 3 | GND do driver |
| 5 | 5 Volts do driver|
| 8 | TX |
| 9 | RX |
| 7 | Pino do servo |


## Funcionamento da ponte H
Os motores vão para frente e para trás, defina:

| INA | INB | Modo |
| :-: | :-: | :--: |
| LOW | HIGH | Frente |
| HIGH | LOW | Trás |
| LOW | LOW | Parado |
| HIGH | HIGH | Parado |