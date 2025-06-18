💧 Medidor de Nível de Água com Arduino

Projeto de medidor de nível de água com Arduino Uno, sensor ultrassônico, display LCD I2C, RTC DS3231, EEPROM, LEDs e buzzer. O sistema monitora o nível da água e alerta visual e sonoramente quando o nível atinge faixas pré-definidas, além de salvar eventos críticos na EEPROM.

---

## 🚀 Componentes utilizados
- Arduino Uno (ou Nano/Mega)
- Sensor Ultrassônico HC-SR04
- Display LCD 16x2 com módulo I2C
- Módulo RTC DS3231
- EEPROM interna do Arduino
- 1 Buzzer
- LEDs: 1 verde, 1 amarelo, 1 vermelho
- 3 resistores 220Ω
- Jumpers e protoboard

---

## ⚡ Esquema de ligação

| Componente | Pino Arduino |
|------------|--------------|
| HC-SR04 Trig | D9 |
| HC-SR04 Echo | D10 |
| LED Verde | D4 |
| LED Amarelo | D2 |
| LED Vermelho | D7 |
| Buzzer | D3 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| RTC SDA | A4 |
| RTC SCL | A5 |
| RTC VCC | 5V |
| RTC GND | GND |
| LCD VCC | 5V |
| LCD GND | GND |
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |

📌 *RTC e LCD compartilham SDA (A4) e SCL (A5).*

---

## 💡 Funcionamento
- **0 a 5 cm** → LED verde aceso, mensagem `Baixo`, buzzer desligado.
- **6 a 10 cm** → LED amarelo aceso, mensagem `Atencao`, buzzer ligado.
- **11 cm ou mais** → LED vermelho aceso, mensagem `Perigo`, buzzer ligado, evento salvo na EEPROM.
- O RTC fornece horário no display e para os registros.
- O LCD exibe nível e hora.

---

## 📝 Código
Código principal no arquivo `nivel_agua.ino`.  
Inclui:
- Medição do nível
- Exibição no LCD
- Controle dos LEDs e buzzer
- Registro na EEPROM

---

## 🛠 Como usar
1️⃣ Monte o circuito conforme o esquema.  
2️⃣ Faça o upload do código no Arduino via Arduino IDE.  
3️⃣ Abra o Serial Monitor (9600 baud) para logs e leituras.  
4️⃣ Teste variando o nível de água simulado.

---

## 📈 Possíveis expansões
- Botão para ler eventos salvos no LCD
- Wi-Fi (ESP8266/ESP32) para envio dos dados
- Dashboard web com gráficos
- Salvamento em cartão SD

---