#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <EEPROM.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

// Pinos do Ultrassônico
const int trigPin = 9;
const int echoPin = 10;

// Pinos dos LEDs e buzzer
const int ledVerde = 4;
const int ledAmarelo = 2;
const int ledVermelho = 7;  // atualizado para pino D7
const int buzzer = 3;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  if (!rtc.begin()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro no RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  lcd.setCursor(0, 0);
  lcd.print("  SafePlace");
  lcd.setCursor(0, 1);
  lcd.print(" Monitorando...");
  delay(2000);
}

void salvarEvento(float distancia) {
  DateTime agora = rtc.now();
  int addr = EEPROM.read(0);
  if (addr > 100) addr = 1;

  EEPROM.write(addr++, (byte)distancia);
  EEPROM.write(addr++, agora.hour());
  EEPROM.write(addr++, agora.minute());
  EEPROM.write(addr++, agora.second());
  EEPROM.write(0, addr);

  Serial.print("Evento salvo: ");
  Serial.print(distancia);
  Serial.print(" cm em ");
  Serial.print(agora.hour());
  Serial.print(":");
  Serial.print(agora.minute());
  Serial.print(":");
  Serial.println(agora.second());
}

void loop() {
  long duracao;
  float distancia;

  // Medição do ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  DateTime agora = rtc.now();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nivel:");

  if (distancia <= 5) {
    lcd.print(" Baixo");
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);
  }
  else if (distancia > 5 && distancia <= 10) {
    lcd.print(" Atencao");
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, HIGH);
  }
  else {
    lcd.print(" Perigo");
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
    salvarEvento(distancia);
  }

  lcd.setCursor(0, 1);
  if (agora.hour() < 10) lcd.print("0");
  lcd.print(agora.hour());
  lcd.print(":");
  if (agora.minute() < 10) lcd.print("0");
  lcd.print(agora.minute());
  lcd.print(":");
  if (agora.second() < 10) lcd.print("0");
  lcd.print(agora.second());

  delay(1000);
}
