
-----

# Projeto de Painel Solar com Rastreamento de Luz

### Descrição do Projeto

Este projeto demonstra a criação de um sistema de rastreamento de luz que simula o movimento de um painel solar seguindo a fonte luminosa mais intensa. Utilizando dois sensores de luz **LDR (Light Dependent Resistor)** e um **micro servo motor SG90** controlado por um **Arduino**, o sistema se ajusta automaticamente para captar a maior quantidade de luz possível.

### Componentes Utilizados

  * Arduino (Uno, Nano ou similar)
  * 2x Sensores de Luz LDR
  * 1x Micro Servo Motor SG90
  * 1x Protoboard
  * Jumpers (fios)

### Como o Código Funciona

O código do Arduino foi projetado para ler as informações de dois sensores LDR e, com base na diferença de luminosidade entre eles, ajustar a posição do servo motor. A seguir, detalhamos cada parte do código:

```c++
#include <Servo.h>

Servo meuServo;
```

A linha `#include <Servo.h>` importa a biblioteca necessária para controlar o servo motor. A linha `Servo meuServo;` cria um objeto chamado `meuServo` que será usado para se comunicar com o servo motor.

```c++
int ldrEsquerda = A0; // LDR da esquerda
int ldrDireita = A1;  // LDR da direita
```

Aqui, declaramos duas variáveis inteiras para armazenar os pinos analógicos do Arduino aos quais os sensores LDR estão conectados. O LDR da esquerda está no pino **A0** e o da direita no pino **A1**.

```c++
int posicaoServo = 70; // Posição inicial
int passo = 3; // Aumenta a velocidade (era 1, agora é 3)
```

  * `posicaoServo`: Define a posição inicial do servo motor em 70 graus. Este valor pode ser ajustado dependendo da montagem física do projeto.
  * `passo`: Controla a "velocidade" de movimento do servo. Quanto maior o valor, mais rápido o servo se move em direção à luz. Um valor de 3 foi escolhido para um rastreamento mais ágil.

<!-- end list -->

```c++
void setup() {
  pinMode(ldrEsquerda, INPUT);
  pinMode(ldrDireita, INPUT);
  Serial.begin(9600);

  meuServo.attach(6);
  meuServo.write(posicaoServo);
}
```

A função `setup()` é executada uma única vez ao iniciar o Arduino:

  * `pinMode()`: Configura os pinos dos LDRs como entradas (`INPUT`).
  * `Serial.begin(9600)`: Inicia a comunicação serial para que possamos monitorar as leituras dos sensores no Monitor Serial do Arduino IDE.
  * `meuServo.attach(6)`: Conecta o objeto `meuServo` ao pino digital 6 do Arduino, que será usado para enviar os sinais de controle ao servo.
  * `meuServo.write(posicaoServo)`: Move o servo para a sua posição inicial, definida anteriormente.

<!-- end list -->

```c++
void loop() {
  int leituraEsquerda = analogRead(ldrEsquerda);
  int leituraDireita = analogRead(ldrDireita);

  Serial.print("LDR Esquerda: ");
  Serial.print(leituraEsquerda);
  Serial.print(" | LDR Direita: ");
  Serial.println(leituraDireita);
```

A função `loop()` é executada repetidamente e é o "coração" do programa:

  * `analogRead()`: Lê o valor de luminosidade de cada LDR. O valor retornado está entre 0 (pouca luz) e 1023 (muita luz).
  * `Serial.print()` e `Serial.println()`: Imprimem os valores dos sensores no Monitor Serial, o que é útil para depuração e para entender o comportamento do sistema.

<!-- end list -->

```c++
  int diferenca = leituraEsquerda - leituraDireita;
  int tolerancia = 50;
```

  * `diferenca`: Calcula a diferença entre as leituras dos dois LDRs.
  * `tolerancia`: Define um limite para que o servo só se mova quando a diferença de luz for significativa. Isso evita que o servo fique tremendo com pequenas variações de luz.

<!-- end list -->

```c++
  if (abs(diferenca) > tolerancia) {
    if (leituraEsquerda > leituraDireita && posicaoServo < 150) {
      posicaoServo += passo;
    } else if (leituraDireita > leituraEsquerda && posicaoServo > 70) {
      posicaoServo -= passo;
    }

    // Garante que o valor fique dentro do limite permitido
    posicaoServo = constrain(posicaoServo, 70, 150);

    meuServo.write(posicaoServo);
    delay(20); // Reduzido para acelerar a resposta (era 50)
  }

  delay(50); // Intervalo entre as leituras
}
```

Esta é a parte principal do controle do sistema:

1.  **Verificação de Diferença**: O `if (abs(diferenca) > tolerancia)` verifica se a diferença entre as leituras é maior que a tolerância. Se for, o código dentro do `if` é executado.
2.  **Ajuste do Servo**:
      * Se o `leituraEsquerda` for maior que `leituraDireita` (ou seja, há mais luz à esquerda), o servo se move para a esquerda (`posicaoServo += passo`).
      * Se o `leituraDireita` for maior, ele se move para a direita (`posicaoServo -= passo`).
3.  **Restrição de Movimento**: `posicaoServo = constrain(posicaoServo, 70, 150)` garante que o servo não se mova além dos ângulos de 70 e 150 graus, protegendo o motor de movimentos excessivos.
4.  **Movimento do Servo**: `meuServo.write(posicaoServo)` envia o comando para o servo se mover para a nova posição.
5.  **Atrasos (delays)**:
      * `delay(20)`: Um pequeno atraso dentro do `if` para controlar a velocidade do servo.
      * `delay(50)`: Um atraso entre as leituras dos sensores, permitindo que o sistema tenha um intervalo de tempo para processar as informações.

-----
### Exemplo da montagem realizada
![Imagem de exemplo 1](https://i.postimg.cc/KvJ9Qfkd/Whats-App-Image-2025-09-17-at-19-33-48.jpg)
<img src="https://i.postimg.cc/KvJ9Qfkd/Whats-App-Image-2025-09-17-at-19-33-48.jpg" alt="Texto alternativo" width="300" height="200" />
-----
### Como Usar

1.  Monte o circuito conectando os LDRs e o servo ao Arduino conforme o código.
2.  Carregue o código no Arduino através do Arduino IDE.
3.  Abra o **Monitor Serial** para visualizar os valores de leitura dos sensores.
4.  Teste o sistema iluminando os sensores com uma lanterna ou a luz do celular para ver o painel se ajustando em direção à fonte de luz.

-----

### Autores

  * Kaio Alves
  * Miguel Duarte
  * Yhan Phillipe
  * Luis Ivan
