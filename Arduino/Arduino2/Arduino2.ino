int pbPin = 2;                         //Définiton du pin qui sera affecté au bouton
int ledPin = 3;                        //Définiton du pin qui sera affecté à la LED
int lstStt;                            //Déclaration d'une variable stockant l'ancien état du bouton
int state;                             //Déclaration d'une variable stockant l'état actuel du bouton
int buttonState;                       //Déclaration d'une variable différente stockant l'état actuel du bouton
unsigned long lastDebounceTime = 0;    //Définition d'une variable qui sera utilisée pour contrer l'effet de rebond électronique du bouton
unsigned long debounceDelay = 50;      //Idem
int ledState = HIGH;                   //Définition de l'état de la LED allumé par défaut


void setup() {

  pinMode(pbPin, INPUT);          //Le pin 2 "pbPin" est définit en tant qu'entrée
  pinMode(ledPin, OUTPUT);        //Le pin 3 "ledPin" est définit en tant que sortie
  digitalWrite(ledPin, HIGH);     //Allumage par défaut de la LED
  lstStt = digitalRead(pbPin);    //Définition de la valeur de "last state" à celle lue sur le pin du bouton

}

void loop() {

  int reading = digitalRead(pbPin);    //Définition d'une variable stockant la valeur lue sur le pin du bouton

  if (state != lstStt) {            //L'état actuel est différent du précedant ?
    lastDebounceTime = millis();    //Définition de "lastDebounceTime" à la valeur renvoyée par la fonction "millis()"
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {    //Si la valeur renvoyée par "millis()" moins "lastDebounceTime" est plus grande que 50 millisecondes

    if (reading != buttonState) {    //"reading" est différent de "buttonState" ?
      buttonState = reading;         //Définition de "buttonState" à la valeur de "reading"

      if (buttonState == HIGH && ledState == HIGH) {    //"buttonState" est égal à "HIGH" ET "ledState" est égal à "HIGH" ?
        while (buttonState == HIGH) {                   //Tant que le bouton est pressé                             -|
          buttonState = digitalRead(pbPin);             //Définition de "buttonState" à la valeur lue sur le pin 2   |-- Ces trois lignes permettent de n'éteindre la LED que lorsqu'on relâche le bouton
        }                                               //                                                          -|
        ledState = !ledState;                           //L'état de "ledState" est inversé
      } else if (buttonState == HIGH) {                 //Si SEUL "buttonState" est égal à "HIGH"
        ledState = !ledState;                           //L'état de "ledState" est inversé
      }
    }
  }

  digitalWrite(ledPin, ledState);    //Changement de l'état de la LED à "ledState"

  lstStt = reading;    //Définition de "last state" à la valeur de "reading"

  state = digitalRead(pbPin);    //Définitoon de "state" à la valaur lue sur le pin 2

}
