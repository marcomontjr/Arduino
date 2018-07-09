//LEDS
#define LED_VERDE 2
#define LED_AMARELO 3
#define LED_AZUL 4
#define LED_VERMELHO 5

//Buttons
#define BOTAO_VERDE 8
#define BOTAO_AMARELO 9
#define BOTAO_AZUL 10
#define BOTAO_VERMELHO 11

//TIMERS
#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

//REGRAS
#define TAMANHO_SEQUENCIA 4
#define INDEFINIDO -1

enum Estados
{
  PRONTO_PARA_PROXIMA_RODADA,
  USUARIO_RESPONDENDO,
  JOGO_FINALIZADO_SUCESSO,
  JOGO_FINALIZADO_FALHA  
};

int sequenciaLuzes[TAMANHO_SEQUENCIA];
int rodada = 0;
int LedsRespondidos = 0;

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  IniciaPortas();  
  IniciaJogo();
}

void IniciaJogo(){
  int jogo = analogRead(0);
  randomSeed(jogo);
  for(int index = 0; index < TAMANHO_SEQUENCIA; index++)
  {
    sequenciaLuzes[index] = SorteiaCor(); 
  }
}

int SorteiaCor()
{
  return random(LED_VERDE, LED_VERMELHO + 1);
}

void IniciaPortas(){
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  pinMode(BOTAO_VERDE, INPUT_PULLUP);
  pinMode(BOTAO_AMARELO, INPUT_PULLUP);
  pinMode(BOTAO_AZUL, INPUT_PULLUP);
  pinMode(BOTAO_VERMELHO, INPUT_PULLUP);
}

void loop() {
  switch(EstadoAtual())
  {
    case PRONTO_PARA_PROXIMA_RODADA:
      Serial.println("PRONTO_PARA_PROXIMA_RODADA");     
      PreparaNovaRodada();       
      break;
    case USUARIO_RESPONDENDO:
      Serial.println("USUARIO_RESPONDENDO");
      ProcessaRespostaUsuario();      
      break;
    case JOGO_FINALIZADO_SUCESSO:
      Serial.println("JOGO_FINALIZADO_SUCESSO");
      JogoFinalizadoSucesso();
      break;
    case JOGO_FINALIZADO_FALHA:
      Serial.println("JOGO_FINALIZADO_FALHA");
      JogoFinalizadoFalha();
      break;
  };

  delay(500);
}

void JogoFinalizadoSucesso()
{
    piscaLed(LED_VERDE);
    piscaLed(LED_AMARELO);
    piscaLed(LED_AZUL);
    piscaLed(LED_VERMELHO);
    delay(MEIO_SEGUNDO);
}

void PreparaNovaRodada()
{
    rodada++;
    LedsRespondidos = 0;
    if(rodada <= TAMANHO_SEQUENCIA)
    {
      TocaLeedsDaRodada();  
    }
}

void ProcessaRespostaUsuario()
{
    int resposta = ChecaRespostaJogador();

    if(resposta == INDEFINIDO)
    {
        return;
    }
    
    if(resposta == sequenciaLuzes[LedsRespondidos])
    {
        LedsRespondidos++;
    }else {
      Serial.println("Resposta Errada");
      rodada = TAMANHO_SEQUENCIA + 2;
    }
}

int EstadoAtual()
{
  if(rodada <= TAMANHO_SEQUENCIA)
  {
    if(LedsRespondidos == rodada)
    {
      return PRONTO_PARA_PROXIMA_RODADA;      
    }else{
      return USUARIO_RESPONDENDO;  
    }      
  } else if(rodada == TAMANHO_SEQUENCIA + 1) {
    return JOGO_FINALIZADO_SUCESSO;
  }else{
    return JOGO_FINALIZADO_FALHA;
  }
}

void TocaLeedsDaRodada()
{
  for(int indice = 0; indice < rodada; indice++)
  {
      PiscaLed(sequenciaLuzes[indice]);
  }
}

int ChecaRespostaJogador()
{
  if(digitalRead(BOTAO_VERDE) == LOW)
  {
    return PiscaLed(LED_VERDE);  
  }  

  if(digitalRead(BOTAO_AMARELO) == LOW)
  {
    return PiscaLed(LED_AMARELO);
  }

  if(digitalRead(BOTAO_AZUL) == LOW)
  {
    return PiscaLed(LED_AZUL);
  }

  if(digitalRead(BOTAO_VERMELHO) == LOW)
  {
    return PiscaLed(LED_VERMELHO);  
  }

  return INDEFINIDO;
}

int PiscaLed(int portaLed){
  digitalWrite(portaLed, HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(portaLed, LOW);
  delay(MEIO_SEGUNDO);
  return portaLed;
}

void JogoFinalizadoFalha(){
  for(int i = 0; i < TAMANHO_SEQUENCIA; i++){
     digitalWrite(sequenciaLuzes[i], HIGH);
  }
  
  delay(UM_SEGUNDO);

   for(int i = 0; i < TAMANHO_SEQUENCIA; i++){
     digitalWrite(sequenciaLuzes[i], LOW);
  }
  
  delay(UM_SEGUNDO);
}
