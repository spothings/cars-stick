#include <PS4Controller.h>

//pin logika
const int m1 = 16; // HITAM
const int m2 = 17; // MERAH
const int m3 = 5; // HITAM
const int m4 = 18; // KUNING

// adc stik
int l2 = 0; int r2 = 0;
int analogr = 0; int analogl = 0;

int r = 255;
int g = 0;
int b = 0;
void pelangi() {
  if (r > 0 && b == 0) {
    r--;
    g++;
  }
  if (g > 0 && r == 0) {
    g--;
    b++;
  }
  if (b > 0 && g == 0) {
    r++;
    b--;
  }
}
void setup() {
  Serial.begin(115200); // coba 9600

  PS4.begin("5c:d0:6e:05:e9:c5");
  Serial.println("Ready to Connect!");

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
}

void loop() {
  if (PS4.isConnected()) {
    pelangi();
    PS4.setLed(r, g, b);

    analogr = map(PS4.LStickX(), 0, 128, 0, 255);
    analogl = map(PS4.LStickX(), 0, -128, 0, 255);
    r2 = PS4.R2Value();
    l2 = PS4.L2Value();

    majumundur();
    kirikanan();
    //rem();
    //getar();

    PS4.sendToController();
  }
}

void majumundur() {

  if (r2 > 50) {
    Serial.println("MAJU");
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    PS4.setRumble(0, r2);
  }

  if (l2 > 50) {
    Serial.println("MUNDUR");
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    PS4.setRumble(0, l2);
  }

  if (r2 < 50 && l2 < 50 && analogr < 50 && analogl < 50) {
    Serial.println("DIAM");
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    PS4.setRumble(0, 0);
  }
}

void kirikanan() {
  if (analogr > 50) {

    Serial.println("KANAN");
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    PS4.setRumble(analogr, 0);
  }

  if (analogl > 50) {

    Serial.println("KIRI");
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    PS4.setRumble(analogl, 0);
  }
}
//void rem() {
//  if (PS4.Square())
//  Serial.println("BRAKE");
//  digitalWrite(m1, HIGH);
//  digitalWrite(m2, HIGH);
//  digitalWrite(m3, HIGH);
//  digitalWrite(m4, HIGH);
//PS4.setRumble(0, 0);
//}

//void getar() {
//  if (r2 > l2) {
//    PS4.setRumble(0, r2);
//  }
//  else if (r2 < l2) {
//    PS4.setRumble(0, l2);
//  }
//  else if (analogr > 50) {
//    PS4.setRumble(analogr, 0);
//  }
//  else if (analogl > 50) {
//    PS4.setRumble(analogl, 0);
//  }
//  else {
//    PS4.setRumble(0, 0);
//  }
//}
