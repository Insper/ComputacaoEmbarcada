# Simulado Avaliação prática 1

Esse é um simulado de como será a avaliação prática aplicada na disciplina de Computação Embarcada. Sugerimos você fazer como se fosse a avaliação de verdade, assim terá uma ideia de como está indo na disciplina. Essa avaliação cobre os objetivos de aprendizagem da disciplina:

1.	Criar softwares para microcontroladores utilizando suas especificidades;
2.	Avaliar e melhorar soluções embarcadas integrando hardware/software levando em conta adequação a uma aplicação;
3.	Integrar em um protótipo hardware, software básico, sistema operacional de tempo real e módulos de interfaceamento com usuários, de comunicação e de alimentação.

Secundários: 

4.	Compreender as limitações de microcontroladores e seus periféricos;
5.	Buscar e analisar documentação (datasheet) e extrair informações relevantes.

!!! note "Regas"
    - Consulta a colegas/ internet constituirão violações ao Código de Ética e de Conduta e acarretarão sanções nele previstas. **Faça o seu trabalho de maneira ética!**
    - **A cada 15 minutos você deverá fazer um commit no seu código!**
        - Códigos que não tiverem commit a cada 15min ou que mudarem drasticamente entre os commits serão descartados (conceito I) !!
        - Você deve inserir mensagens condizentes nos commits!
    - **Duração: 2h**

## AV1-Simulado

!!! note "Começando"
    - Atualize o `SAME70-examples`
    - Atualize o arquivo `ALUNO.json` com seu nome e email e faça um **commit** imediatamente.

Nessa avaliação iremos criar um cronometro regressivo e utilizaremos o módulo OLED para
exibir os valores,  
para isso copie o projeto `same70-examples/screens/OLED-Xplained-Pro-SPI/`para 
o repositório criado para entregar a avaliação. 

Nessa avaliação iremos trabalhar com um sensor chamado de encoder. O Encoder é
um componente eletrônico muito utilizado, ele basicamente gera pulsos conforme o
deslocamento (angular ou linear, depende do modelo). Já pensou como é
implementando o volume do som dos carros? É com um enconder rotativo! 

Iremos utilizar o encoder K1-040 nessa APS, esse componente além do encoder
possui uma chave (SW) totalizando 5 pinos:

- GND: terra
- VCC: 3v3
- SW: Push button do encoder, precisa ativar pull-up
- DT: Direção
- CLK: pulsos (20/ rotação)

## C

O encoder servirá para configurar os minutor do seu cronometro, o sistema deve
começar com o valor 0 e a cada pulso do enconder (pino `clk`) ele deve aumentar em 1
segundo o tempo total do cronometro (até no máximo 60), quando o usuário apertar
o botão do encoder `SW` o sistema deve começar uma contagem regressiva, e quando
o valor da contagem for 0, o mesmo deve piscar todos os LEDs da placa OLED a uma
frequência de 6HZ até que o usuário aperte o botão `SW` do enconder novamente.

Ao mesmo tempo que exibe a contagem do cronometro, você deve exibir a hora atual
no display OLED.

Resumo:

- Exibir valor do cronometro
- Valor do cronometro deve ser ajustado com pulsos do Encoder
    - usar pino de CLK do encoder
    - leitura por interrupção
- A contagem do cronometro deve inicializar quando usuário apertar a chave do
  encoder
      - usar pino SW do encoder (ativar pullup nesse pino)
      - SW deve funcionar por interrupção
- Piscar LEDs da placa OLED até usuário apertar a chave SW
- Exibir hora no display: HH:MM:SS
 
    
## C+

- Piscar LED do kit de desenvolvimento enquanto o cronometro estiver ativado

## B

- Usar um botão da placa OLED para possibilitar que escolha a direção do ajuste do cronometro
  (para cima ou para baixo)

## A

- Usar o pino DT do enconder que indica a direção da rotação.
