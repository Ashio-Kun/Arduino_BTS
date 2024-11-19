int ledPin = 3;     //Définition du numéro de pin qui sera affecté à la LED
int pbPin = 2;      //Définition du numéro de pin qui sera affecté au bouton poussoir
int lstStt = LOW;   //Définition d'une variable "last state" stockant le dernier état du bouton

void setup() {
  
  pinMode(ledPin, OUTPUT);    //Le pin 3 "ledPin" est définit en tant que sortie
  pinMode(pbPin, INPUT);      //Le pin 2 "pbPin" est définit en tant qu'entrée

}

void loop() {
  
  int state = digitalRead(pbPin);    //Définiton d'une variable stockant l'état actuel du bouton

  if (state != lstStt) {    //L'état actuel est différent de l'ancien ?
    //Si oui, exécution du programme ci-dessous
    if (state) {    //L'étant actuel est-il un front montant ? (égal à 1 = True)
      digitalWrite(ledPin, !digitalRead(ledPin));    //Changement de l'état de la LED à l'état opposé de l'actuel
      lstStt = state;                                //Définition de la variable à l'état du bouton actuel
    }

  }

}
