# LAB - HC-SR04

| Pasta              |
|--------------------|
| `Lab5-HC-SR04` |

Neste laboratório iremos trabalhar com o sensor de distância HC-SR04, que é muito utilizado em projetos de robótica e similares. O sensor é um módulo ultrasonico e que possibilita medirmos a distância entre o sensor e um objeto.

![](http://wiki.sunfounder.cc/images/1/1f/Ultrasonic_.jpg)

Para realizarmos a leitura correta do sensor, iremos utilizar os seguintes periféricos (com interrupção):

- PIO: Acionamento do sensor (pino TRIG) e leitura do pulso de echo (pino ECHO)
- TC: Contarmos o tempo do pulso de echo
- TC/ RTT: Determinar a cadência de coleta de dados
- RTC: Fornecendo o data log

## HC-SR04

Refs:

- http://wiki.sunfounder.cc/index.php?title=Ultrasonic_Module
- https://www.filipeflop.com/produto/sensor-de-distancia-ultrassonico-hc-sr04/

O Sensor de Distância Ultrassônico HC-SR04 é capaz de medir distâncias de 2cm a 4m com ótima precisão e baixo preço. Este módulo possui um circuito pronto com emissor e receptor acoplados e 4 pinos (VCC, Trigger, ECHO, GND) para medição.

Para começar a medição é necessário alimentar o módulo e colocar o pino Trigger em nível alto por mais de 10us. Assim, o sensor emitirá uma onda sonora que, ao encontrar um obstáculo, rebaterá de volta em direção ao módulo. Durante o tempo de emissão e recebimento do sinal, o pino ECHO ficará em nível alto. Logo, o cálculo da distância pode ser feito de acordo com o tempo em que o pino ECHO permaneceu em nível alto após o pino Trigger ter sido colocado em nível alto.

Distância = [Tempo ECHO em nível alto * Velocidade do Som] / 2

A velocidade do som poder ser considerada idealmente igual a 340 m/s, logo o resultado é obtido em metros se considerado o tempo em segundos. Na fórmula, a divisão por 2 deve-se ao fato de que a onda é enviada e rebatida, ou seja, ela percorre 2 vezes a distância procurada.

Especificações:

- Alimentação: 5V DC
- Corrente de Operação: 2mA
- Ângulo de efeito: 15°
- Alcance.: 2cm ~ 4m
- Precisão.: 3mm

> Descricão extraída do site do filipflop: https://www.filipeflop.com/produto/sensor-de-distancia-ultrassonico-hc-sr04/

!!! info
    No Brasil s sensor custa em torno de R$14 (https://www.filipeflop.com/produto/sensor-de-distancia-ultrassonico-hc-sr04/)

### Montagem

O sensor possui dois pinos (TRIG e ECHO) que devem ser ligados no uC os outros são para alimentacão (GND e VCC), como o módulo opera com 5V teremos que fazer um divisor de tensão no pino do ECHO para não danificar o nosso uC que possui tensão máxima nos pinos de 3v3.

Você deve seguir a montagem a seguir, sugerimos utilizar uma protoboard para isso. Os pinos X e Y podem ser qualquer um do EXT-2.

=== "Esquemático"
    ![](montagem.svg){width=600}

=== "Protoboard"
    ![](proto.jpg){width=600}

!!! warning
    Você deve escolher os pinos X e Y que irão ligar no uC.

### Interagindo

Após feita a montagem você deverá escrever um programa que faz o controle do sensor ultrasonico, para iniciar uma nova leitura você deve gerar um pulso de `10 us` no pino de Trig (**Pin Y**) e então aguardar pela subida do sinal do Echo (**Pin X**) e então contar o tempo (**dT**) que ele fica em alto. O valor de **dT** é proporcional ao tempo que o som levou para chegar até o obstáculo e voltar.

A figura a seguir demonstra como funciona a leitura do sensor.

![](wave.svg){width=600}

!!! question short
    Qual o tempo **mínimo** e **máximo** que o sinal de **Echo** pode ficar em '1'? Lembre de verificar o range do sensor.
    
    !!! details ""
        
        Das informações fornecidas do sensor:
        
        - Distância mínima: 0.02 m
        - Distância máxima: 4 m
        
        Sabendo que a velocidade do som é aproximadamente 340 m/s, podemos aplicar uma regra de 3 e $x [s] = dist / 340$. Lembre que o sensor fornece a distância x2!
        
        Ou seja:
        
        - Tempo mínimo: $2 \times 0,000058$s --> 0,116 us
        - Tempo máximo: $2 \times 0,011764$s --> 23,4 us

!!! question long
    Com as informações coletadas até aqui você consegue imaginar como deve ser o firmware para fazer a leitura do sensor? Não existe uma única maneira de fazer, mas algumas soluções podem não ser muito boas!
    
    Descreva aqui como você geraria o sinal do Trig e como você faria a leitura do sinal do Echo, quais periféricos usaria para isso?
    
    !!! details ""
        Uma das soluções possíveis (e indicadas) é:
        
        Sinal do **Echo** gerar via `pio_set(), delay_us(10), pio_clear()`. Como o sinal do pino de Echo pode ser aproximadamente 10 us, não tem muito problema em usar a função de delay para isso!
        
        Já o sinal do Trig carrega informações importantes e devemos contar corretamente o tempo. Para isso sugerimos configurar uma interrupção de boarda no pino e inicar o RTT quando ocorrer uma borda de descida e parar a contagem do tempo quando ocorrer uma borda de subida. 
        
        ==Um ponto importante é a configuração da frequência na qual o RTT irá operar. Pense um pouco a respeito....==

## Lab

Nesse laboratório vocês devem usar o exemplo do OLED e realizando a leitura periódica do HCSR04 exibir a distância entre o sensor e um objeto no display. Sempre que você apertar o botão da placa, uma nova leitura começa.

Lembrem de copiar o exemplo do OLED para o seu repositório e renomear para: `Lab5-HC-SR04`, ou se preferir, podem usar um dos labs passados que possui OLED e já tem os botões configurados, só lembrem de fazer uma cópia e renomear.

!!! tip
    Step: 
    
    1. Fazer a montagem na protoboard
    1. Escolher dois pinos para Echo e Trig
    1. Configurar Trig como output e Echo como input
    1. Configurar irq de boarda no pino Echo
        - lembre da função de callback!
    
    Trig:
    
    1. Gerar o pulso do Trig com `delay_us`
    
    Echo:
    
    1. Iniciar o RTT em borda de descida do pino Echo
        - Qual prescale usar?
    1. Parar o RTT em borda de subida do pino Echo

    Conta: 
    
    1. Realizar o cálculo da distância usando o valor que o RTT contou
    1. Exibir no OLED
    
!!! progress
    Até aqui é C
    
### B 

Estamos lidando com um sensor que pode ter falhas, o que acontece se o sensor não estiver operando direito, ou se der mal contato na ligação? ou se o som não voltar (espaçõ aberto). Identifique esse tipo de erro e exiba no OLED.

### A

Exibir gráfico com últimos valores da distância.
