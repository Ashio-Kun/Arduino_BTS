#include <math.h>

int pinCapt = 0;

float Bmodel = 3627;
float T0 = 296.25;
float R0 = 11000;
float Rc;
float Tmod;
float U;
float N;

void setup() {
  
  pinMode(1, INPUT);
  Serial.begin(9600);

}

void loop() {

  N = analogRead(0);

  U = N * 5/ 1023.0;

  Rc = 680 * (7 / U) - 680;

  Tmod = 1000000.0 / ((1000000.0 / T0) + (1000000.0 / Bmodel) * (log(1000000 * Rc / R0) - log(1000000.0)))-273.15;

  Serial.print("Température mesurée : ");
  Serial.println(Tmod);
  Serial.println(1000000/Bmodel);
  Serial.println(1000000/T0);

  delay(500);

}

/*

  boucle for de 10 fois {

    Programme calcul

  }

*/
