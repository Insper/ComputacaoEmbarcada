![Roland Kirk](figs/ADC/Roland-Kirk.png)

Ao final do lab você deve ter um sistema embarcado que faz a leitura de dois valores analógicos: Temperatura interna do uC e Valor da resistência de um potenciômetro, enviando esses valores para o terminal.

Código base **SAME70-Examples**:

| SAME70-examples |
|-----------------|
| [`Perifericos-uC/ADC-Temperatura`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/ADC-Temperatura) |

Copiar para:

| Pasta      |
|------------|
| `Labs/ADC` |

- LAB ADC: 
    1. Executar código exemplo `ADC-Temperatura`
    1. Portar exemplo para LCD
    1. Exibir temperatura no LCD
    1. Inserir timer 
    1. Conectar um potenciômetro no uC
    1. Configurar um AFEC para ler o valor do potenciômetro  
    1. Converter bits -> resistência 
    1. Exibir no LCD de forma gráfica o valor da temperatura e resistência

# Laboratório

O código exemplo [`SAME70-exemples/Perifericos-uC/ADC-Temperatura`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/ADC-Temperatura) demonstra como configurar um dos ADCs (AFEC) do nosso uC para fazer uma conversão A/D de um sensor de temperatura interno ao chip.


!!! example "Execute"
    Copie esse exemplo para a pasta do
    seu repositório.

!!! note "LEIA"
    Leia o
    [README](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/ADC-Temperatura)
    desse exemplo!
    
!!! example ""
    1. Execute o exemplo na placa!
    1. Entenda como ele funciona!

## Programando 

Ao final do lab você deve ter um sistema embarcado que faz a leitura de dois valores analógicos: Temperatura interna do uC e Valor da resistência de um potenciômetro, enviando esses valores para o terminal. 

A taxa de amostragem da temperatura deve ser 1Hz e do potenciômetro 10Hz. Utilize dois **TC** para gerar a taxa de amostragem correta. Fique o maior tempo possível em `sleepmode`.

### Roteiro

Sugestão de passos de implementação. Leia tudo antes de sair fazendo! Visão do todo é muito importante...

1. Migre o `delay_s(1)` do exemplo para ser executado por um TimerCounter `TC`
1. Escolha um pino que possa ser usado como analógico
    - Busque no manual `SAME70.pdf` na secção **50** referente ao AFEC
1. Conecte um potenciômetro ao pino (pode ser um joystick)
1. Configure o AFEC para realizar a leitura desse pino
    - não esqueça do callback 
1. Insira outro **TC** para realizar a leitura desse **ADC** 
1. Escreva uma função que converta BITs -> Resistência
1. Formate e envie tudo pela serial

Além? 

1. Exiba graficamente no LCD os valores analógicos
1. Insira um time stamp nos dados (RTC)
