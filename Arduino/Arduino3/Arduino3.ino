// ████████╗         ████████╗     ████████╗     ██████████████╗
// ████████║         ████████║     ████████║     ████████████████╗
// ████████║         ████████║     ████████║     ██████     ██████╗
// ████████║   ██╗   ████████║     ████████║     ██████     ██████║
// ████████║ ██████╗ ████████║     ████████║     ████████████████╔╝
// ██████████████████████████║     ████████║     ██████████████╔═╝
// ██████████████████████████║     ████████║     ██████╔═══════╝
// ████████████╔═████████████║     ████████║     ██████║
// ██████████╔═╝  ╚██████████║     ████████║     ██████║
// ████████╔═╝      ╚████████║     ████████║     ██████║
//  ╚══════╝          ╚══════╝      ╚══════╝      ╚════╝


const int pbuPin = 2;           // Pin du bouton poussoir
const int ledPin = 3;           // Pin de la LED pour indiquer les clics
int previousState = LOW;        // État précédent du bouton
unsigned long pressStartTime = 0; // Temps où le bouton a été appuyé
unsigned long lastClickTime = 0;  // Temps du dernier clic pour le double clic
unsigned long doubleClickStart = 0; // Temps de début du clignotement pour double-clic
bool isButtonPressed = false; //Définition d'une variable booléenne "isButtonPressed" à la valeur "false"
bool isDoubleClick = false; //Définition d'une variable booléenne "isDoubleClick" à la valeur "false"
unsigned long pressDuration; //Définition d'une variable stockant la valeur de la durée d'une pression sur le bouton

void setup() {
  pinMode(pbuPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int currentState = digitalRead(pbuPin);   // Lecture de l'état actuel du bouton
  unsigned long currentTime = millis();     // Temps actuel en millisecondes

  // Détection de l'appui sur le bouton (transition de LOW à HIGH)
  if (currentState == HIGH && previousState == LOW && !isButtonPressed) {
    pressStartTime = currentTime;          // Enregistre l'heure de l'appui
    isButtonPressed = true;
  }

  // Détection du relâchement du bouton (transition de HIGH à LOW)
  if (currentState == LOW && previousState == HIGH && isButtonPressed) {
    pressDuration = currentTime - pressStartTime; // Durée de l'appui
    isButtonPressed = false;

    // Détection du clic court
    if (pressDuration < 500) {
      digitalWrite(ledPin, HIGH);          // Allume la LED pour indiquer le clic court
        // Détection du double clic
      if (currentTime - lastClickTime <= 500) { // Délai de 500 ms pour double clic
        
        doubleClickStart = currentTime;     // Début du clignotement pour double-clic
        isDoubleClick = true;               // Active le mode double clic
      }

      lastClickTime = currentTime;          // Met à jour le dernier clic pour le double clic
    }

    // Détection du clic long
    else if (pressDuration >= 2500) {
      digitalWrite(ledPin, LOW);           // Éteint la LED après le clic long
    }
  }

  // Gestion du clignotement pour le double clic
  if (isDoubleClick) {
    if (currentTime - doubleClickStart < 10000) { // Clignote pendant 3 secondes
      if ((currentTime / 250) % 2 == 0) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    } else {
      isDoubleClick = false;               // Désactive le mode double clic après 3 secondes
      digitalWrite(ledPin, LOW);           // Éteint la LED après le clignotement
    }
  }

  previousState = currentState; // Met à jour l'état précédent pour la prochaine boucle
}