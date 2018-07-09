  //Leds
  #define LED_VERMELHO 4

  //Buttons
  #define BOTAO_VERMELHO 10

  //Timers
  #define UM_SEGUNDO 1000
  #define MEIO_SEGUNDO 500

void setup() {
  Serial.begin(9600);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BOTAO_VERMELHO, INPUT_PULLUP);

  digitalWrite(LED_VERMELHO, HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(LED_VERMELHO, LOW);
}

void loop() {
  int estadoBtn = digitalRead(BOTAO_VERMELHO);  
  Serial.println(estadoBtn);
  delay(MEIO_SEGUNDO);
}
