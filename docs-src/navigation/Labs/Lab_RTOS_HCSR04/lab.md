# LAB - RTOS HC-SR04

| Pasta          |
|----------------|
| `Lab9-HC-SR04` |

A ideia deste laboratório é refazermos o LAB do sensor de distância, só que agora usando o RTOS e o display LCD.
Para realizarmos a leitura correta do sensor, iremos utilizar os seguintes periféricos (com interrupção):

!!! info
    Para mais informações consulte o `Lab 5 - HC-SR04`

Vamos usar de código base o `
[SAME70-examples/Screens/RTOS-TFT-LCD-ILI9341-LVGL/`](https://github.com/Insper/SAME70-examples/tree/master/Screens/RTOS-TFT-LCD-ILI9341-LVGL) que já possui o freeRTOS e a parte de acesso do display e o LVGL.

## Portando o código

Usando como base o código do lab 5 incorpore a lógica de leitura do sensor (RTT handler e lógica de controle) para o projeto atual com o freeRTOS e o LCD. Lembre de não incorporar a parte referente ao OLED. Crie uma tarefa dedicada para a leitura do sensor.

!!! info
    Use printf para validar a leitura da distância.

### RTOS

Agora vamos fazer uso correto do RTOS. Para isso vocês devem implementar uma fila para envio do `dT` pelo RTT handler para a task de controle e pensar se devem substituir o `delay_us` pelo o `vTaskDelay`.

!!! info "timeout"
    Pensem no timeout da fila, qual deve ser o valor? O que significa o dado não chegar no tempo certo?

!!! question choice
    Para gerar o sinal do TRIG vocês usaram a função `delay_us`, vocês devem portar para `vTaskDelay`?
    
    - [x] Não
    - [ ] Sim
    
    !!! details ""
        Não devem por alguns motivos:
        
        - A funcão `vTaskDelay` usa como base de tempo o TICK do RTOS, que pode não ter resolucão para gerar o sinal de trigger.
        - O `vTaskDelay` é um valor aproximado.

### Melhorando

Agora vamos fazer melhorias no projeto.

1. Use um label para exibir o valor da distância lida pelo sensor.
1. Adicione um botão para "Ligar" / "Desligar" a leitura.
1. Exibe se o sensor está funcionando corretamente ou está desconectado.

!!! info
    Até aqui é C.

## Extras:

> Cada item vale como um conceito a mais.

- Mostre um gráfico da distância
- Permite configurar o intervalo entre as leituras (tempo entre o echo)



