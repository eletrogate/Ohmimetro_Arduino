int R1 = 9845; // Valor medido no multimetro

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  double resistencia, aux;
  aux = (float)analogRead(A0)/1023;
  resistencia = aux * (float) R1 / (1 - aux);
  Serial.println("O valor da resistencia é: "+ String(resistencia) + " Ω");
  delay(2000);
}