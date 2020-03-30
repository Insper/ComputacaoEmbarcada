# Simulado Avaliação prática 1

Esse é um simulado de como será a avaliação prática aplicada na disciplina de Computação Embarcada. Sugerimos você fazer como se fosse a avaliação de verdade, assim terá uma ideia de como está indo na disciplina. Essa avaliação cobre os objetivos de aprendizagem da disciplina.

Nessa avaliação iremos trabalhar com o módulo OLED1 (botões/ LEDs e Display), o mesmo já está disponível no repositório da avaliação. 

- Atualize o arquivo `ALUNO.json` com seu nome e e-mail e faça um commit imediatamente.

!!! note "Regras"
    Faça o seu trabalho de maneira ética!

    - **A cada 30 minutos você deverá fazer um commit no seu código!**
        - Códigos que não tiverem commit a cada 15min ou que mudarem drasticamente entre os commits serão descartados (conceito I) !!
        - Você deve inserir mensagens condizentes nos commits!
    - Duração: 2h

## AV1-Simulado

!!! example "Botões e Leds"
    - Configurar os três botões do OLED1 com interrupção e função de callback, sendo:
        - Button0: Subida 
        - Button1: Descida
        - Button2: Subida
    - Configurar os três LEDs do módulo OLED1 como saída

!!! example "Piscando Leds"
    - Faça o LED2 e LED3 **piscarem** sendo que cada um é controlados por um TC cada (cada um inicializado em uma frequência):
        - LED2: RTT : 0.2 Hz
        - LED3: TC  : 1Hz
    -
 
 
- Fazer o microcontrolador entrar em sleepmode
 
## C

Agora com o projeto inicializado vamos começar a implementar. A ideia é de que o display do kit OLED1 exiba uma informação contendo a frequência atual em que os 3 LEDs da placa estarão piscando.

Resumo:

- Efetuar a leitura dos botões para controlar a frequência com que os LEDs da placa piscam.
- Utilizar o OLED como interface gráfica
      
## C+

- Controlar a frequência dos LEDs através dos botões.
- Mostra a frequência com que os LEDs estão piscando no OLED.

## B

- Utilizar IRQ para ler os botões.
- Utiliza TC para piscar os LEDs.

## B+

- Implementar pause/play através dos botões.
- Utilizar RTC e implementar HH:MM no display do OLED.

## A

- Exibir a frequência atual do LED por meio de um Bargraph no display OLED: 

![bargraf3](imgs/AV-0-Simulado-2020-1/bargraf3.jpg) ![bragraph](imgs/AV-0-Simulado-2020-1/bragraph.png)
