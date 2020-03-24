# TC - RTC - IRQ 

!!! warning
    Esse lab já possui entrega com nota!

| Pasta              |
|--------------------|
| `Labs/TC-RTC-IRQ/` |

- Parte 1: 
    - [ ] Entra em sleep mode
    - [ ] Led pisca mais rápido
    - [ ] Pisca Pisca 
- Parte 2:
    - [ ] Corrigido uso de flag para parar o pisca pisca
    - [ ] Usar placa OLED
    - [ ] Para cada LED um TC diferente
    - [ ] Cada LED é controlado por um botão
    - [ ] Exibir hora atual no OLED1 

## Entenda o exemplo

| SAME70-Examples                                                                                                |
|----------------------------------------------------------------------------------------------------------------|
| [`Perifericos-uC/TC-RTC-IRQ`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/TC-RTC-IRQ) |


O firmware disponível no repositório de exemplos chamado de [`TC-RTC-IRQ`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/TC-RTC-IRQ) configura o TimerCounter (TC) e o RTC do mircontrolador. O TC0 canal 1 é configurado para gerar uma interrupção (**TC1_Handler**) a cada 250ms (f=1/T -> de 4Hz) já o RTC é configurado para operar em modo de alarme, gerando uma interrupção (**RTC_Handler**) em um determinado momento. Inicialmente o RTC está configurado para gerar uma interrupção um minuto após o início do microcontrolador.

O TimerCounter faz com o o led pisque na frequência de 4Hz enquanto não ocorrer o alarme do RTC, após o acontecimento do alarme (interrupção do RTC) o piscar do led é desligado.

![](imgs/TC/overview.png){width=500}

!!! note "Entenda e execute"
    1. Copie esse exemplo para a pasta do seu repositório [`Labs/TC-RTC-IRQ`].
    1. Leia o [README](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/TC-RTC-IRQ) desse exemplo!
    1. Execute o exemplo na placa!
    1. Responda:
        - Quais periféricos são utilizados?
        - O que o firmware faz?
        - Quantas interrupções são usada, quais são elas?

!!! warning
    Não continue sem ter feito a etapa anterior

## Programando

Vamos agora trabalhar com o código exemplo, modificando e incorporando novas funcionalidades. 

!!! warning ""
    Nesse laboratório, não é permitido utilizar funções de delay por software:  `delay_s()` / `delay_ms()` / ...

#### 1. Sleep 

Vamos fazer nosso uc entrar em sleep sempre que não tiver nada para fazer. Para isso utilize a função `pmc_sleep(..)` no `while(1)`, como ilustrado a seguir.

```c
while(1){
  // trecho de codigo a ser executado antes de dormir
  // ...

  // entra em sleep
  pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);

  // trecho de codigo a ser executado depois de acordar
  // ...
}
```

O modo **Wait for Interrupt** WFI é um dos modos de powersave mais básicos e menos eficientes do SAME70. Nele o CORE ainda é mantido energizado porém sem clock. A grande vantagem desse modo é que qualquer interrupção pode acordar o core, diferente de outros modos mais agressivos que desabilita complemente o CORE implicando em um menor gasto energético.

Toda vez que essa função for chamada o CORE entrará em modo sleep e ficará "bloqueada" esperando por alguma interrupção. Após detectada a interrupção, o CORE irá acordar e resolver todas as interrupções que estão pendentes e então irá liberar essa função, ou seja, continuará a executar o código.

!!! example "Modifique e teste"
    1. Faça o exemplo fazendo com o que o uC entre em modo sleep enquanto estiver ocioso.
    1. Compile, programe e teste


#### 2. Mais rápido !

Vamos fazer com o que os LEDs pisquem mais rápidos, para isso será necessário modificar a frequência na qual o TimerCounter (TC) gera a interrupção.

!!! example "Modifique e teste"
    1. Faça com que o LED pisque ainda mais rápido! Escolha uma frequência que achar adequado.
    1. Compile, programe e teste

!!! tip
    De uma olhada nos parâmetros da função `tc_init()`

#### 3. Piscar durante 1 minuto e parar durante 1 minuto - cíclico

O objetivo agora é fazermos com que o LED da placa pisque por um minuto, e depois, pare de piscar por um minuto, e depois volte a piscar por um minuto (uma coisa cíclica), como ilustrado a seguir:

![Led da placa](imgs/TC/led.png)

!!! example "Modifique e teste"
    1. Faça com que o led pisque durante um minuto e fique um minuto sem piscar eternamente, faça isso de forma cíclica.
    1. Compile, programe e teste

!!! tip
    - Use o alarme do RTC para isso!
    - Utilize a função `[rtc_get_time()](http://asf.atmel.com/docs/latest/same70/html/group__sam__drivers__rtc__group.html#ga91b1a1ac85e5bb5effefe275b824fe6a)` para saber a hora atual.
    - Cuidado ao mudar de Hora/ Dia/ Mês

------------------

> Até aqui é C

------------------

#### 4. Flag é a melhor maneira ?

A tomada de decisão se o LED está em modo "pisca pisca" é feita por uma variável global `flag_led0`:

``` c
/************************************************************************/
/* VAR globais                                                          */
/************************************************************************/
uint8_t flag_led0 = 1;
```

Dentro da interrupção do TC1 verificamos a flag:

``` c
void TC1_Handler(void){
    ....

	/** Muda o estado do LED */
    if(flag_led0)
        pin_toggle(LED_PIO, LED_PIN_MASK);
```

O problema aqui é que a interrupção do TC1 continua ocorrendo mesmo com o piscar do LED desativado, o que pode ter um impacto no consumo e performance do projeto.

!!! example "Modifique e teste"
    1. Proponha e implemente uma solução para não usar mais flag.
    1. Compile, programe e teste

!!! tip
    - Que tal fazer com que o `TC` pare de executar? Procure por uma função que faça isso.
    - A função que faz o `TC` começar é a `tc_start()`



#### 5. Várias frequências

 Utilizando a placa OLED1 conectada ao kit de desenvolvimento, faça com que cada LED pisque nas frequências determinadas na tabela a baixo, utilize para cada LED um TC diferente.

    | LED OLED1 | Frequência  (Hz) |
    |-----------|------------------|
    | LED 1     | 8                |
    | LED 2     | 11               |
    | LED 3     | 17               |

!!! example "Modifique e teste"
    1. Faça com que os LEDs da placa OLED pisquem em diferentes frequências, usando 3 TCs
    1. Compile, programe e teste

!!! tip
    A função `tc_init()` do código exemplo recebe como argumento:

    - Um `TC`: 
        - `TC0`, `TC1`, `TC2`

    - Um ID do canal:  
    
    | TC    | Canal 0  | Canal 1  | Canal 2   |
    |-------|----------|----------|-----------|
    | `TC0` | `ID_TC0` | `ID_TC1` | `ID_TC2 ` |
    | `TC1` | `ID_TC3` | `ID_TC4` | `ID_TC5 ` |
    | `TC2` | `ID_TC6` | `ID_TC7` | `ID_TC8 ` |

    - Um canal:
        - `0`, `1`, `2`
        
    - E uma frequência
    
    --------------
    
    Caso queira usar por exemplo o canal 1 do TC2 gerando uma interrupção a 10Hz, você deve chamar a função da seguinte maneira:
    
    `TC_init(TC2, ID_TC7, 1, 10)`
       
    Uma vez feito isso, você deve definir a função de handler desse canal:
     
    ```c
    void TC7_Handler(void){

    /* Devemos indicar ao TC que a interrupção foi satisfeita. */
    volatile uint32_t ul_dummy = tc_get_status(TC2, 1);
    
    /* seu código vem aqui */

    }
    ```
       
#### 6. Botões

Cada botão da placa OLED deve comandar o seu LED, uma vez apertado esse botão faça o LED relacionado a esse botão parar de piscar, quando apertar o botão novamente, o LED volta a piscar. Você deve tratar os botões com interrupção.

!!! example "Modifique e teste"
    1. Faça com que os botões (relacionados a cada LED) pare ou inicialize o piscar dos LEDs, utilize para isso interrupção do PIO.

    - Não use flags para isso!

#### 7. OLED1 - Exibir hora

!!! example "Modifique e teste"
    Utilize o `OLED1` para exibir a hora atual no display!

    - Dica: 
        - Ative a interrupção de segundos do RTC (além da de alarme)
        - No handler, verifique o motivo de entrar na interrupção
        - Trabalhe com flags, atualize o LCD no `while(1){}`

    Para verificar se a interrupção foi referente a segundos (precisa ativar antes!):

    ```
      // Second increment interrupt
      if ((ul_status & RTC_SR_SEC) == RTC_SR_SEC)
      {
      /* limpa interrupcao segundos */
          rtc_clear_status(RTC, RTC_SCCR_SECCLR);
      }
```
