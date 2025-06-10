// Done by Zofia Sewerynska
// 2023, Poland

#include "Wire.h"  // Biblioteka Wire używana do komunikacji szeregowej (I2C)
#include "Adafruit_PWMServoDriver.h"  // Biblioteka do obsługi modułu sterownika serwomechanizmów PCA9685
#include <SoftwareSerial.h>  // Biblioteka do obsługi komunikacji szeregowej za pomocą oprogramowania

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // Inicjalizacja obiektu do sterowania modułem PCA9685
SoftwareSerial Serial_Bluetooth(3, 2);  // Inicjalizacja obiektu dla komunikacji Bluetooth (Tx - wyjście cyfrowe 3, Rx - wyjście cyfrowe 2)

// Deklaracja stałych
#define FREQUENCY 50  // Częstotliwość PWM (Pulse Width Modulation)
#define NUM_SERVOS 16  // Liczba serwomechanizmów
#define SERVOMIN  95  // Minimalna wartość sygnału PWM dla serwomechanizmu
#define SERVOMAX  520  // Maksymalna wartość sygnału PWM dla serwomechanizmu
String stan;  // Zmienna przechowująca stan komunikacji Bluetooth

// Deklaracje wyjść Arduino dla różnych wariantów serwomechanizmów
uint8_t servoPins_1[] = {14, 12, 11, 9, 6, 4, 3, 1};
uint8_t servoPins_2[] = {15, 13, 10, 8, 7, 5, 2, 0};
uint8_t servoPins_3[] = {15, 14, 13, 12, 7, 6, 5, 4};
uint8_t servoPins_4[] = {11, 10, 9, 8, 3, 2, 1, 0};
uint8_t servoPins_5[] = {5};
uint8_t servoPins_6[] = {6};
uint8_t servoPins_7[] = {9};
uint8_t servoPins_8[] = {10};

// Inicjalizacja - ustawienia początkowe
void setup() {
  pwm.setOscillatorFrequency(27000000);  // Ustawienie częstotliwości
  pwm.begin();  // Inicjalizacja modułu PCA9685
  pwm.setPWMFreq(FREQUENCY);  // Ustawienie częstotliwości sygnału PWM
  Serial_Bluetooth.begin(9600);  // Inicjalizacja komunikacji Bluetooth
  delay(10);  // Opóźnienie dla stabilizacji  
}

// Funkcja do poruszania serwomechanizmami
void moveServos(int servoNumber, int targetAngle) {
  int currentAngle = 0;  // Aktualny kąt serwomechanizmu
  int step = 1;  // Krok zmiany kąta

  // Pętla zmieniająca kąt serwomechanizmu stopniowo
  while (currentAngle != targetAngle) {
    pwm.setPWM(servoNumber, 0, map(currentAngle, 0, 180, SERVOMIN, SERVOMAX));  // Ustawienie kąta serwomechanizmu
    delay(100);  // Opóźnienie
    if (currentAngle < targetAngle) {
      currentAngle += step;  // Zwiększenie kąta
    } else {
      currentAngle -= step;  // Zmniejszenie kąta
    }

    // Wysyłanie stanu pozycji serwomechanizmu po zmianie kąta
    String positionData = "Serwomechanizm nr." + String(servoNumber) + ", " + "pozycja: " + String(currentAngle) + " °"; //Zmienna do wysyłania danych
    Serial_Bluetooth.println(positionData); // Przesyłanie danych poprzez Bluetooth
    delay(100); // Opóźnienie
  }
}


// Główna pętla programu
void loop() {
  if (Serial_Bluetooth.available()) {  // Sprawdzenie dostępności danych z Bluetooth
    stan = Serial_Bluetooth.read();  // Odczyt danych z Bluetooth
    Serial.println(stan);  // Wyświetlenie odczytanych danych w monitorze szeregowym

    // Kod obsługujący różne warianty sterowania serwomechanizmami

    // Warunek dla wariantu numer 0
    if (stan == "0") {
      int targetAngle_1 = 90;  // Docelowy kąt serwomechanizmów dla wariantu 0

      // Poruszanie serwomechanizmami dla wariantu 0
      for (uint8_t i = 0; i < sizeof(servoPins_1) / sizeof(servoPins_1[0]); i++) {
          uint8_t currentPin_1 = servoPins_1[i];
          moveServos(currentPin_1, targetAngle_1);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów 
      for (uint8_t j = 0; j < sizeof(servoPins_1) / sizeof(servoPins_1[0]); j++) {
          pwm.setPWM(servoPins_1[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }

    // Warunek dla wariantu numer 1
    if (stan == "1") {
      int targetAngle_2 = 90;  // Docelowy kąt dla wariantu 1

      // Poruszanie serwomechanizmami dla wariantu 1
      for (uint8_t i = 0; i < sizeof(servoPins_2) / sizeof(servoPins_2[0]); i++) {
          uint8_t currentPin_2 = servoPins_2[i];
          moveServos(currentPin_2, targetAngle_2);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów 
      for (uint8_t j = 0; j < sizeof(servoPins_2) / sizeof(servoPins_2[0]); j++) {
          pwm.setPWM(servoPins_2[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }

    // Warunek dla wariantu numer 2
    if (stan == "2") {
      int targetAngle_3 = 180;  // Docelowy kąt dla wariantu 2

      // Poruszanie serwomechanizmami dla wariantu 2
      for (uint8_t i = 0; i < sizeof(servoPins_3) / sizeof(servoPins_3[0]); i++) {
          uint8_t currentPin_3 = servoPins_3[i];
          moveServos(currentPin_3, targetAngle_3);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów
      for (uint8_t j = 0; j < sizeof(servoPins_3) / sizeof(servoPins_3[0]); j++) {
          pwm.setPWM(servoPins_3[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }

    // Warunek dla wariantu numer 3
    if (stan == "3") {
      int targetAngle_4 = 180;  // Docelowy kąt dla wariantu 3

      // Poruszanie serwomechanizmami dla wariantu 3
      for (uint8_t i = 0; i < sizeof(servoPins_4) / sizeof(servoPins_4[0]); i++) {
          uint8_t currentPin_4 = servoPins_4[i];
          moveServos(currentPin_4, targetAngle_4);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów
      for (uint8_t j = 0; j < sizeof(servoPins_4) / sizeof(servoPins_4[0]); j++) {
          pwm.setPWM(servoPins_4[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }

    // Kod obsługujący sterowanie serwomechanizmami na odgórnie ustalone kąty

    // Warunek dla wariantu numer 4 (Serwomechanizm nr. 1: 90 stopni)
    if (stan == "4") {
      int targetAngle_5 = 90;  // Docelowy kąt dla wariantu 4

      // Poruszanie serwomechanizmem dla wariantu 4
      for (uint8_t i = 0; i < sizeof(servoPins_5) / sizeof(servoPins_5[0]); i++) {
          uint8_t currentPin_5 = servoPins_5[i];
          moveServos(currentPin_5, targetAngle_5);  // Ruch serwomechanizmu do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmu
      }

      // Wyłączenie sekwencji serwomechanizmu
      for (uint8_t j = 0; j < sizeof(servoPins_5) / sizeof(servoPins_5[0]); j++) {
          pwm.setPWM(servoPins_5[j], 0, 0);  // Zatrzymanie serwomechanizmu
      }
    }
 
    // Warunek dla wariantu numer 5 (Serwomechanizm nr.1 : 180 stopni)
    if (stan == "5") {
      int targetAngle_5 = 180;  // Docelowy kąt dla wariantu 5

      // Poruszanie serwomechanizmem dla wariantu 5
      for (uint8_t i = 0; i < sizeof(servoPins_5) / sizeof(servoPins_5[0]); i++) {
          uint8_t currentPin_5 = servoPins_5[i];
          moveServos(currentPin_5, targetAngle_5);  // Ruch serwomechanizmu do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmu
      }

      // Wyłączenie sekwencji serwomechanizmu
      for (uint8_t j = 0; j < sizeof(servoPins_5) / sizeof(servoPins_5[0]); j++) {
          pwm.setPWM(servoPins_5[j], 0, 0);  // Zatrzymanie serwomechanizmu
      }
    }

    // Warunek dla wariantu numer 6 (Serwomechanizm nr.2 : 90 stopni)
    if (stan == "6") {
      int targetAngle_6 = 90;  // Docelowy kąt dla wariantu 6

      // Poruszanie serwomechanizmami dla wariantu 6
      for (uint8_t i = 0; i < sizeof(servoPins_6) / sizeof(servoPins_6[0]); i++) {
          uint8_t currentPin_6 = servoPins_6[i];
          moveServos(currentPin_6, targetAngle_6);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów
      for (uint8_t j = 0; j < sizeof(servoPins_6) / sizeof(servoPins_6[0]); j++) {
          pwm.setPWM(servoPins_6[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }

    // Warunek dla wariantu numer 7 (Serwomechanizm nr.2 : 180 stopni)
    if (stan == "7") {
      int targetAngle_7 = 180;  // Docelowy kąt dla wariantu 7

      // Poruszanie serwomechanizmami dla wariantu 7
      for (uint8_t i = 0; i < sizeof(servoPins_6) / sizeof(servoPins_6[0]); i++) {
          uint8_t currentPin_6 = servoPins_6[i];
          moveServos(currentPin_6, targetAngle_7);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów
      for (uint8_t j = 0; j < sizeof(servoPins_6) / sizeof(servoPins_6[0]); j++) {
          pwm.setPWM(servoPins_6[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }

    // Warunek dla wariantu numer 8 (Serwomechanizm nr.3 : 90 stopni)
    if (stan == "8") {
      int targetAngle_8 = 90;  // Docelowy kąt dla wariantu 8

      // Poruszanie serwomechanizmami dla wariantu 8
      for (uint8_t i = 0; i < sizeof(servoPins_7) / sizeof(servoPins_7[0]); i++) {
          uint8_t currentPin_7 = servoPins_7[i];
          moveServos(currentPin_7, targetAngle_8);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów
      for (uint8_t j = 0; j < sizeof(servoPins_7) / sizeof(servoPins_7[0]); j++) {
          pwm.setPWM(servoPins_7[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }


    // Warunek dla wariantu numer 9 (Serwomechanizm nr.3 : 180 stopni)
    if (stan == "9") {
      int targetAngle_9 = 180;  // Docelowy kąt dla wariantu 9

      // Poruszanie serwomechanizmami dla wariantu 9
      for (uint8_t i = 0; i < sizeof(servoPins_7) / sizeof(servoPins_7[0]); i++) {
          uint8_t currentPin_7 = servoPins_7[i];
          moveServos(currentPin_7, targetAngle_9);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów
      for (uint8_t j = 0; j < sizeof(servoPins_7) / sizeof(servoPins_7[0]); j++) {
          pwm.setPWM(servoPins_7[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }

    // Warunek dla wariantu numer 10 (Serwomechanizm nr.4 : 90 stopni)
    if (stan == "10") {
      int targetAngle_10 = 90;  // Docelowy kąt dla wariantu 10

      // Poruszanie serwomechanizmami dla wariantu 10
      for (uint8_t i = 0; i < sizeof(servoPins_8) / sizeof(servoPins_8[0]); i++) {
          uint8_t currentPin_8 = servoPins_8[i];
          moveServos(currentPin_8, targetAngle_10);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów
      for (uint8_t j = 0; j < sizeof(servoPins_8) / sizeof(servoPins_8[0]); j++) {
          pwm.setPWM(servoPins_8[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }

    // Warunek dla wariantu numer 11 (Serwomechanizm nr. 4 : 180 stopni)
    if (stan == "11") {
      int targetAngle_11 = 180;  // Docelowy kąt dla wariantu 11

      // Poruszanie serwomechanizmami dla wariantu 11
      for (uint8_t i = 0; i < sizeof(servoPins_8) / sizeof(servoPins_8[0]); i++) {
          uint8_t currentPin_8 = servoPins_8[i];
          moveServos(currentPin_8, targetAngle_11);  // Ruch serwomechanizmów do docelowego kąta
          delay(2000);  // Opóźnienie między ruchami serwomechanizmów
      }

      // Wyłączenie sekwencji serwomechanizmów
      for (uint8_t j = 0; j < sizeof(servoPins_8) / sizeof(servoPins_8[0]); j++) {
          pwm.setPWM(servoPins_8[j], 0, 0);  // Zatrzymanie serwomechanizmów
      }
    }
   
  }

  //Kod do testów pierwszego serwomechanizmu
  //pwm.setPWM(0, 90, pulseWidth(180));
}
