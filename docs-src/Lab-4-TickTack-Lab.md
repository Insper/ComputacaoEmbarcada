# TC - RTC - RTT  

!!! success "2020-2"
    Material atualizado.

<!--
!!! Repositório
    Criar repositório para entregar o lab e preencher o formulário a seguir:
    
    <iframe src="https://docs.google.com/forms/d/e/1FAIpQLSfS3x4QLibvCgUAiekQi0_cjWPZqwZ2j5xQwS_MG3QLSJzmUg/viewform?embedded=true" width="640" height="571" frameborder="0" marginheight="0" marginwidth="0">Loading…</iframe>
-->

| Pasta              |
|--------------------|
| `Labs/TC-RTC-RTT/` |

- Parte 1: 
    1. Entender os exemplos (TC/RTT/RTC)
    1. Incorporar todos os exemplos em um único projeto
    1. Pisca pisca 
    
- Parte 2:
    1. fazer outro LED piscar com TC
    1. Exibir a hora atual no lcd
    1. Usar IRQ do segundos do RTC

<!--
- Parte 2 
    - C+ : fazer outro LED piscar com TC
    - B : Exibir a hora atual no lcd
    - A : Usar IRQ do segundos do RTC
 -->
## Periféricos / Exemplos

!!! warning "SAME70-examples"
    Antes de continuar atualize o repositório de exemplos, teve alteração.

Nesse lab iremos trabalhar com três periféricos que lidam com 'tempo', o TimerCounter - TC (temos no total e 4x3=12 no uC) o Real-time Timer - RTT (temos um) e o Real-time Clock RTC (temos um). Cada um possui sua especifidade:

- TC: Faz várias coisas, nesse lab iremos usar para gerar interrupções maiores que 2Hz (**ele não consegue gerar tempos muito lentos!**)
- RTT: É um contador que consegue gerar praticamente qualquer frequência (vamos usar para gerar frequências lentas)
- RTC: É um como um calendário com relógio, ele conta anos, meses, dias, horas, minutos e segundos.

Cada periférico está em um exemplo diferente:

| Periférico exemplos                                                                                   |
| ----------             ----                                                                           |
| [`Perifericos/TC-IRQ `](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/TC-IRQ)  |
| [`Perifericos/RTT-IRQ`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/RTT-IRQ) |
| [`Perifericos/RTC-IRQ`](https://github.com/Insper/SAME70-examples/tree/master/Perifericos-uC/RTC-IRQ) |

Cada exemplo possui o seu próprio `README` que da uma visão geral dos periféricos. Note que todos esses exemplos estão operando por interrupção! Onde cada periférico possui o seu `handler` para resolver a interrupção.

!!! example "Tarefa"
    Para cada exemplo (TC,RTT e RTC):
    1. Leia o README
    1. Programe a placa (e veja os LEDs piscando!)
    1. Entenda o código

## Lab

O lab faz uso da placa `OLED1` e de um código exemplo. Para começar você deve copiar o código exemplo: [`SAME70-examples/Screens/OLED-Xplained-Pro-SPI/`](https://github.com/Insper/SAME70-examples/tree/master/Screens/OLED-Xplained-Pro-SPI) para a pasta da entrega do seu repositório `Labs/TC-RTC-RTT`.

### 1. TC, RTT e RTC 

Com o código do OLED1 copiado (eu dei uma simplificada nele nessa nova versão), vocês devem configurar os botões e os LEDs da placa OLED, e então utilizando um `TC` fazer com que o `LED0` pisque a uma frequencia de 4 HZ; usando o RTT fazer com que o `LED1` pisque a uma frequência de 0.5Hz e com que o LED da placa pisque por 5x após 20s do sistema ter inicializado, fazer o uC entrar em sleepmode sempre que não tiver nada para fazer.

!!! example "Tarefa"
    No código do OLED1:
    
    1. Configurar os pinos e os LEDs da placa OLED1
    1. Fazer com que o `LED1` pisque a 4HZ usando o TC
    1. Fazer com que o `LED2` pisque a cada 4s usando o RTT
    1. Fazer com o que o `LED PLACA` pisque por 5 vezes após 20 segundos (USAR RTC)
    1. Entrar em sleepmode

!!! tip
    Abrir o código atual e o exemplo e ir trazendo as funções e defines que precisa usar, não esqueça de chamar as funções no `main`

!!! tip
    Você vai precisar incluir no `ASF WIZARD` os drivers do TCC e RTT
    
    Quando você fizer a busca vai reparar que tem dois drivers de `TC`,
    para isso você deve clicar em `Details` e ver o TC que adiciona só
    dois arquivos `tc.h` e `tc.c` como na figura a seguir
    
    ![](imgs/TC/ASF.png)
    
!!! info
    Aqui já é C!
    
----------------------------

### 2. Piscar mais um LED

!!! example "Tarefa"
    Faça o `LED2` da placa OLED piscar a 5Hz usando um novo TC

### 3. Exibindo HH:MM:SS

!!! example "Tarefa"
    Exiba a hora no formato (HH:MM:SS) no display OLED
    
!!! tip
    O RTC tem uma função que você consegue buscar no periférico a hora atual: [`rtc_get_time()`](http://asf.atmel.com/docs/latest/sam.drivers.rtc.example.samv71_xplained_ultra/html/group__sam__drivers__rtc__group.html#ga91b1a1ac85e5bb5effefe275b824fe6a)
    
!!! tip 
    Para executar isso você deverá ser capaz de saber quando que o segundo mudou, duas são as opções:
    
    1. Usar um novo TC configurado com 1hz
    1. Pedir para o RTC gerar uma IRQ a cada mudança de segunda
    
    A segunda opção você faz modificando a função de init_rtc:
    
    ```
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
    
### 4. IRQ de segundos
    
Usar a IRQ do RTC por segundo para atualizar o display.

