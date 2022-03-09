# LAB - TC - RTC - RTT  

Neste laboratório iremos trabalhar com os periféricos de contagem de tempo
do nosso microcontrolador.

| Pasta                      |
|----------------------------|
| `Lab4-TC-RTC-RTT`          |
| **Data da entrega:** 18/03 |

Os periféricos apresentados neste laboratório são:

- Real Time Clock - RTC
- Timer Counter - TC
- Real Time Timer - RTT

O laboratório é formado por duas partes:

- Parte 1 (mínimo): 
    1. Entender os exemplos (TC/RTT/RTC)
    1. Incorporar todos os exemplos em um único projeto
    1. Pisca pisca 
    
- Parte 2:
    - **C+**: fazer outro LED piscar com TC
    - **B** : Exibir a hora atual no OLED 
    - **A** : Usar IRQ do segundos do RTC

## Exemplos

!!! warning "SAME70-examples"
    Antes de continuar atualize o repositório de exemplos ele pode ter tido melhorias.

Nesse lab iremos trabalhar com três periféricos que lidam com 'tempo': o TimerCounter (TC) que temos no total de quatro unidades TC (TC0 ~ TC3) e cada um com três contadores; o Real-time Timer (RTT) que só temos um e o Real-time Clock (RTC) que também só temos um e funciona como um relógio/ calendário. 

Um pouco mais sobre os periféricos:

- TC: Faz várias coisas, mas na disciplina iremos o utilizar para gerar interrupções de tempo maiores que 2Hz (**ele não consegue gerar tempos muito lentos!**)
- RTT: É um contador que consegue gerar praticamente qualquer frequência (vamos usar para gerar frequências lentas)
- RTC: É um como um calendário com relógio, ele conta anos, meses, dias, horas, minutos e segundos. E possui um alarme que pode ser configurado para gerar uma interrupção em um determinado momento. 

Nós fornecemos para cada periférico um exemplo diferente:

| Periférico exemplos                                                                                   |
| ----------             ----                                                                           |
| [`Perifericos/TC-IRQ `](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/TC-IRQ)  |
| [`Perifericos/RTT-IRQ`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/RTT-IRQ) |
| [`Perifericos/RTC-IRQ`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/RTC-IRQ) |

Cada exemplo possui o seu próprio `README` que explica de forma ampla os periféricos. Note que todos esses exemplos estão operando por interrupção! Onde cada periférico possui o seu `handler` para resolver a interrupção.

!!! exercise self "dawdwadaw"
    Para cada exemplo (TC,RTT e RTC):
    
    1. Leia o README
    1. Programe a placa (e veja os LEDs piscando!)
    1. Entenda o código


!!! exercise choice
    Como deve ser a chamada de função para usarmos o TC2 canal 2 gerando interrupção a 20Hz?
    
    ```c
    void TC_init(Tc * TC, int ID_TC, int TC_CHANNEL, int freq){
    ```
    
    - [ ] `TC_init(TC2, ID_TC2, 1, 20);`
    - [x] `TC_init(TC2, ID_TC8, 2, 20);`
    - [ ] `TC_init(TC8, ID_TC8, 8, 20);`
    - [ ] `TC_init(TC8, ID_TC2, 3, 20);`

    !!! answer
        O TC funciona diferente do PIO, onde o PIO possuia apenas uma conexão com o NVIC para avisar a interrupcão em qualquer um dos 32 pinos. O TC possui um sinal de conexão com o NVIC para cada canal e esses canais possuem um ID único, conforme figura a seguir:

        ![](https://raw.githubusercontent.com/Insper/SAME70-examples/master/Perifericos-uC/TC-IRQ/imgs/TC/tc.png)
        
!!! exercise choice

    Se usarmos o TC1 canal 0 qual deve ser a funcão de handler?
    
    - [ ] `TC0_Handler`
    - [ ] `TC1_Handler`
    - [ ] `TC2_Handler`
    - [x] `TC3_Handler`
    - [ ] `TC4_Handler`
    - [ ] `TC5_Handler`
    
    !!! answer
        O handler a ser usado tem realacão com o ID do canal, no caso do canal 0 do TC1 o ID é o ID_TC3 e o handler o `TC3_Handler`.

!!! exercise choice
    Um colega está desenhando uma solução para um sistema embarcado que precisa processar dados nas frequências: 1Hz, 2Hz e 44200Hz. Pensando em otimizar o uso energético do uC ele propôs usar um único TC e configurar para cada canal uma frequência diferente:
    
    - `TC0` / `ID_TC0` @ 1Hz
    - `TC0` / `ID_TC1` @ 2Hz
    - `TC0` / `ID_TC2` @ 44200Hz 
    
    O que você faz?
    
    - [ ] Aprova achando uma boa ideia!
    - [ ] Fica desconfiado e não sabe responder.
    - [x] Reprova sabendo o porque não funciona.
    
    !!! answer
        Aqui tem uma pegadinha! Para o TC contar "tempo" ele precisa usar como base um clock gerado pelo PMC, o TC não consegue usar mais de uma base de tempo por periférico (a mesma base se aplica a todos os canais que ele controla). Para as frequêncais 1Hz e 2Hz pode ser que funcione usar o mesmo TC pois a base de tempo que a funcão tc_init vai encontrar deve ser a mesma, mas já para a frequência de 44200Hz a base deve ser outra (é ordens de grandeza maior que as outras frequências) e usar o mesmo TC não vai funcionar!
        
        A melhor solucão aqui seria, usar um TC para as frequências mais baixas e outro apenas para a maior frequência:
        
        - `TC0` / `ID_TC0` @ 1Hz
        - `TC0` / `ID_TC1` @ 2Hz
        - `TC1` / `ID_TC3` @ 44200Hz 
    
        Essa parte da escolha da frequência é realizado dentro da funćão TC_init nas linhas:
        
        ```c
        /** Configura o TC para operar em  freq hz e interrupçcão no RC compare */
        tc_find_mck_divisor(freq, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
        tc_init(TC, TC_CHANNEL, ul_tcclks | TC_CMR_CPCTRG);
        ```
    
!!! progress
    Click para continuar....

## Lab

O lab faz uso da placa `OLED1` e de um código exemplo. Para começar você deve copiar o código exemplo: [`SAME70-examples/Screens/OLED-Xplained-Pro-SPI/`](https://github.com/Insper/SAME70-examples/tree/master/Screens/OLED-Xplained-Pro-SPI) para a pasta da entrega do seu repositório `Lab4-TC-RTC-RTT`.

### Conceito C: TC, RTT e RTC 

Com o código do OLED1 copiado, vocês devem configurar os botões e os LEDs da placa OLED e então utilizando os periféricos fazer:

- Que o `LED1` pisque na frequência de 4Hz, para isso utilize o **TC**;
- Fazer com que o `LED2` pisque a uma frequência de 0.25Hz, para isso utilize o **RTT**;
- Piscar o `LED3` depois de 20 segundos do botão 1 da placa OLED ter sido pressionado, para isso utilize o alarme do RTC.

Fazer o uC entrar em sleepmode sempre que não tiver nada para fazer.

!!! example "Tarefa"
    No código do OLED1:
    
    1. Configurar os pinos e os LEDs da placa OLED1
    1. Faça o LED da placa piscar a 5Hz usando um TC.
    1. Fazer com que o `LED1` pisque a 4Hz usando o TC
    1. Fazer com que o `LED2` inverta seu estado a cada 4s usando o RTT
    1. Fazer com o que o `LED3` inicie apagado e pisque uma vez após 20 segundos do botão 1 ter sido pressionado, use o RTC.
    1. Entrar em sleepmode sempre que possível

!!! tip
    Abrir o código atual e o exemplo e ir trazendo as funções e defines que precisa usar, não esqueça de chamar as funções no `main`

!!! tip
    Você vai precisar incluir no `ASF WIZARD` os drivers do ~~TC~~, RTT e RTT
    
    ==O TC já foi adicionado no código exemplo (OLED-Xplained-Pro-SPI), não adicone o outro que vai dar problema!!!!==
    
    ![](imgs/ASF.png)

!!! tip
    O RTC tem uma função que você consegue buscar no periférico a hora atual: [`rtc_get_time()`](https://asf.microchip.com/docs/latest/same70/html/group__sam__drivers__rtc__group.html#ga91b1a1ac85e5bb5effefe275b824fe6a), você pode então configurar um alarme para daqui 20s. 
    
    - Leia a função e entenda os seus parâmetros!! 

!!! info "Ao terminar o lab preencha:"
    <iframe src="https://docs.google.com/forms/d/e/1FAIpQLSdqlv2DlWFJSuB4ShjY5CrkCwClt9UOuZTPVeG_kWT5qAwssQ/viewform?embedded=true" width="840" height="320" frameborder="0" marginheight="0" marginwidth="0">Carregando…</iframe>


!!! progress
    Até aqui é C ....

### Conceito B: Exibindo HH:MM:SS

!!! example "Tarefa"
    Exiba a hora no formato (HH:MM:SS) no display OLED

!!! tip 
    Para executar isso você deverá ser capaz de saber quando que o segundo mudou, duas são as opções:
    
    1. Usar um novo TC configurado com 1hz
    1. Pedir para o RTC gerar uma IRQ a cada mudança de segunda
    
    A segunda opção você faz modificando a função de init_rtc:
    
    ```c
    RTC_init(RTC, ID_RTC, rtc_initial, RTC_IER_ALREN | RTC_IER_SECEN);
    ```
    
    E agora você consegue dentro do `RTC_handler` saber quando você entrou
    na IRQ pelo segundo:
    
    ```c
    /*  Verifica por qual motivo entrou
    *  na interrupcao, se foi por segundo
    *  ou Alarm
    */
    if ((ul_status & RTC_SR_SEC) == RTC_SR_SEC) {
        
        //    
        //  Entrou por segundo! 
        // 
    	rtc_clear_status(RTC, RTC_SCCR_SECCLR);
    }
    ```

!!! warning
    Você nunca deve atualizar display dentro de interrupção (**handler**)! Sempre no main.
    
### Conceito A: Melhorando

Quando o botão 1 da placa OLED for pressionado, após 20 segundos, faça o LED 3 piscar 
com um novo TC.
