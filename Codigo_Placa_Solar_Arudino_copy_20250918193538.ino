#include <Servo.h> // Inclui a biblioteca Servo para controlar motores servo

Servo meuServo; // Cria um objeto do tipo Servo para controlar o servo motor

// Define os pinos analógicos onde os LDRs estão conectados
int ldrEsquerda = A0; // LDR da esquerda
int ldrDireita = A1;  // LDR da direita

int posicaoServo = 70; // Posição inicial do servo motor (graus)
int passo = 3; // Define o quanto o servo se move a cada ajuste (quanto maior, mais rápido)

void setup() {
  pinMode(ldrEsquerda, INPUT); // Define o pino do LDR esquerdo como entrada
  pinMode(ldrDireita, INPUT);  // Define o pino do LDR direito como entrada
  Serial.begin(9600);          // Inicia a comunicação serial para monitoramento

  meuServo.attach(6);          // Associa o servo motor à porta digital 6
  meuServo.write(posicaoServo); // Define a posição inicial do servo
}

void loop() {
  // Lê os valores analógicos dos sensores LDR
  int leituraEsquerda = analogRead(ldrEsquerda);
  int leituraDireita = analogRead(ldrDireita);

  // Exibe os valores dos LDRs no monitor serial
  Serial.print("LDR Esquerda: ");
  Serial.print(leituraEsquerda);
  Serial.print(" | LDR Direita: ");
  Serial.println(leituraDireita);

  // Calcula a diferença entre os dois LDRs
  int diferenca = leituraEsquerda - leituraDireita;
  int tolerancia = 50; // Define uma margem de erro para evitar ajustes desnecessários

  // Só ajusta o servo se a diferença for maior que a tolerância
  if (abs(diferenca) > tolerancia) {
    // Se a esquerda estiver mais clara e não ultrapassar o limite máximo, move para a esquerda
    if (leituraEsquerda > leituraDireita && posicaoServo < 150) {
      posicaoServo += passo;
    } 
    // Se a direita estiver mais clara e não ultrapassar o limite mínimo, move para a direita
    else if (leituraDireita > leituraEsquerda && posicaoServo > 70) {
      posicaoServo -= passo;
    }

    // Garante que a posição do servo fique entre 70 e 150 graus
    posicaoServo = constrain(posicaoServo, 70, 150);

    // Move o servo para a nova posição
    meuServo.write(posicaoServo);
    delay(20); // Pequeno atraso para suavizar o movimento do servo
  }

  delay(50); // Tempo entre as próximas leituras dos sensores
}

