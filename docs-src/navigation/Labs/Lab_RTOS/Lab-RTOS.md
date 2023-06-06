# LAB - RTOS (freeRTOS)


|                       Pastas: | `/Lab4-RTOS-PIO-IRQ`        | `/Lab4-RTOS-IRQ-ADC` |
|------------------------------:|:-----------------------|:-------------|
| **Data <span style="color:red">LIMITE</span> para entrega:**  | `{{lab04_deadline}}` |              |

!!! warning
    Atualize o repositório de exemplos: `same70-examples` antes de continuar.
    
O repositório está organizado por categorias: comunicação, demos, periféricos, screens, sensores, ... e assim por diante.

Na primeira parte deste laboratório iremos trabalhar com o código exemplo [`SAME70-examples/Perifericos-uC/RTOS-PIO-IRQ/`]([https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/PIO-IRQ]). Esse código será a base da primeira parte do laboratório.

Na segunda parte, iremos trabalhar com o código exemplo [`SAME70-examples/Perifericos-uC/RTOS-IRQ-ADC/`]([[https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/PIO-IRQ]). Esse código será a base da segunda parte do laboratório.


!!! tip "Embedded FM - episódio 175"
    **How Hard Could It Be?**
    
    Jean Labrosse of Micrium (@Micrium) spoke with us about writing a real time operating system (uC/OS), building a business, and caring about code quality.
    
    - https://embedded.fm/episodes/175

!!! video
    ![Video](https://www.youtube.com/embed/F321087yYy4)

Neste laboratório iremos trabalhar com o uso de um sistema operacional de tempo real (RTOS). O sistema operacional a ser utilizado é o [FreeRtos (www.freertos.org)](http://freertos.org), um sistema operacional muito utilizado pela industria, sendo o segundo sistema operacional (**20%**) mais utilizado em projetos embarcados, perdendo só para o [Linux](https://m.eet.com/media/1246048/2017-embedded-market-study.pdf).

!!! progress 
    Continuar ...

## LAB

O laboratório consiste em:

1. Executar uma demo de RTOS
1. Entender e modificar o exemplo
1. Praticar

### Setup

!!! exercise "OLED1"
    Plugue a placa OLED1 no EXT1, vamos usar seus botões e LEDs.

!!! exercise "Terminal" 
    Esse exemplo faz uso da comunicação UART para debug de código (via printf), para acessar o terminal no microchip estúdio clique em:

    1. No microchip studio: :arrow_right: View :arrow_right: Terminal Window
    1. Configure o terminal para a porta COM correta (verificar no windows) para operar com um BaudRate de 115200.

    Caso não tenha essa opção, instale o [pacote extra do microchip studio](https://gallery.microchip.com/packages/EFC4C002-63A3-4BB9-981F-0C1ACAF81E03/2.8.4)

!!! progress 
    Continuar ...

## RTOS

Para dicas de como usar o RTOS acesse:

[Util/Freertos](https://insper.github.io/ComputacaoEmbarcada/navigation/Dicas/Util-freertos/)

### PIO-IRQ-RTOS

- https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/RTOS-PIO-IRQ

Vamos usar esse código exemplo para aprenderemos os principais recursos do RTOS, nele criamos duas tasks: `task_but` e `task_led` que se comunicam via uma fila. O botão da placa é configurado para operar com interrupção de borda, liberando um semáforo para a `task_but`, que processa a informação e envia um novo valor de delay para a `task_led`:

![](https://raw.githubusercontent.com/Insper/SAME70-examples/master/Perifericos-uC/RTOS-PIO-IRQ/doc/diagrama.svg)

!!! exercise "Executando"
    1. Compile e grave o código no uC
    2. Abra o ![terminal](https://insper.github.io/ComputacaoEmbarcada/navigation/Util/Util-Erros/#instalando-terminal-window-no-atmel-studio) e configure a UART (baudrate 115200).
    1. Veja o LED piscar! 
    1. Aperte o botão da placa e veja a frequência mudar.

Antes de seguir analise um pouco o código e tente entender o que está acontecendo, para isso consulte a página desse lab chamada de Teoria.

!!! exercise "Praticando - semáforo"
    Faça uma cópia desse código para `Lab4-pio-irq-rtos` e vamos mexer nele!
    
    A ideia aqui é possibilitar diminuirmos a frequência através de outro botão! Para 
    isso teremos que adicionar mais um semáforo que irá se comunicar com a task but.
    
    Tarefa:
    
    1. Modifique o código adicionando um botão da placa OLED (interrupcao, callback...)
    1. Crie um novo semáforo e libere ele quando o botão novo for apertado.
    1. Na task but processe o semáforo aumentado o valor da frequência
    
    Dicas:
    
    - Você ==NÃO== deve criar outra task, tem que fazer tudo na `task_but`
    - As interrupções de HW devem possuir prioridade maior que 4.


!!! exercise "Praticando - queue"
    Agora vamos usar fila no lugar de semáforo para comunicar os botões com a `task_but`. 
    
    Tarefa:
    
    1. Crie uma mais uma fila
    1. Cada callback deve colocar o valor do incremento na fila (ou o id do botão)
    1. A task_but recebe o valor, faz o cálculo e envia para a task_led

!!! progress 
    Continuar ...

### ADC-IRQ-RTOS

- https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/RTOS-IRQ-ADC

Outro exemplo que vamos usar como base é o ADC-IRQ-RTOS que faz a leitura de um valor analógico do pino do uC, você deve ler o README que possui o diagrama de ligações e uma pequena explicação. 

![](https://raw.githubusercontent.com/Insper/SAME70-examples/master/Perifericos-uC/RTOS-IRQ-ADC/diagrama.svg)

!!! exercise "Executando"
    1. Leia o README do exemplo e ligue conforme indicado
    1. Compile e grave o código no uC
    2. Abra o terminal e configure a UART (baudrate 115200).
    1. Aperte o botão da placa e veja a frequência mudar.

Antes de seguir analise um pouco o código e tente entender o que está acontecendo, analise a task, as interrupções e também o uso da fila.

!!! exercise "Praticando"
    Faça uma cópia desse código para `Lab4-adc-irq-rtos` e vamos mexer nele!
    
    A ideia agora é criarmos uma task intermediária (task_proc) que irá fazer o processamento dos dados 
    recebidos pelo ADC, conforme o diagrama atualizado a seguir:
    
    
    ![](imgs/diagrama2.svg)
    
    A `task_proc` deverá calcular a média móvel (N=10) dos dados do ADC e então enviar esses dados para para a task `task_adc` via uma nova fila, com o objetivo de ser exibido. A ideia da média móvel é aplicar um filtro passa baixas para remover ruídos do sinal.
    
    - Referência: https://www.analog.com/media/en/technical-documentation/dsp-book/dsp_book_ch15.pdf
    
    Tarefas/dicas:
    
    1. Modifique o código adicionando a task_proc
    1. Faça a leitura do dado do AFEC nessa nova tarefa 
    1. Crie uma nova fila, e envie o dado da task_proc para a task_adc (dado bruto, ainda sem processamento)
    1. Na task_adc exiba o dado via printf
    1. Agora na task proc calcule a média móvel e o envie para a task_adc.
    
!!! info "Ao terminar o lab preencha:"
    <iframe src="https://docs.google.com/forms/d/e/1FAIpQLSdGoa5m16sRpQoNlXlTbvxKjyGFp0hHgSuRKQ43AG5W3aL0XA/viewform?embedded=true" width="640" height="800" frameborder="0" marginheight="0" marginwidth="0">Carregando…</iframe>

## Projeto

Agora que vocês já entendem um pouco melhor os recursos do RTOS podem e ==devem== aplicar esses conceitos no projeto. Por exemplo, para os botões vocês podem usar semáforos ou filas, para a leitura do valor analógico uma fila.
