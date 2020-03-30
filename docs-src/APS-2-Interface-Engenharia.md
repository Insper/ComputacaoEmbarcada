# APS - 2 - Engenharia

Além do design com o usuário, você deve ter os seguintes cuidados com a
engenharia do protótipo. A seguir dicas de implementação:

### Velocidade instantânea 

Será necessário realizar a leitura da velocidade da bicicleta, existem algumas
soluções que podem ser utilizadas:

A velocidade da bicicleta (v) é decorrente da velocidade angular (w) de sua
roda, sendo calculado por: `v = w*r [m/s]`.

Existem duas maneiras de se calcular a velocidade angular: 

- mede-se o tempo (`t`) entre dois pulsos e a partir da frequência (`f=1/t`) calcula-se `w = 2*pi*f [rad/s]`
- acumula-se pulsos (`N`) em um determinado tempo (`dT`): `w = 2*pi*N/dT`

Como só conseguimos medir um pulso por rotação, é necessário que esse `dT` seja:
suficiente alto  para medirmos uma velocidade relativamente baixa, mas não pode
ser tão elevado, caso contrário teremos uma taxa de atualização da velocidade muito lenta.

!!! note
    Nesses dois casos não podemos utilizar o TC para medirmos a frequência (`f`) ou
    gerar o `dT` pois  a menor frequência na qual o TC operar/medir é de 0.5Hz (o
    que daria  uma velocidade mínima de 3.3Km/h).
    
    Vamos usar um novo periférico chamado de RTT (detalhes a seguir)

### Indicação de aceleração

É a derivada da velocidade, se positiva indica que a bicicleta está ganhando
velocidade, negativa perdendo e próxima a zero a velocidade está estável. Para
derivarmos a velocidade de forma discreta, utilizamos a equação a seguir:

`a(t) = K * (x[N] - x[N-1])/Ts`

onde:

- `a(t)`: é a aceleração instantânea 
- `K`: constante opcional (ganho)
- `x[N]` : valor da velocidade atual
- `x[N-1]` : valor da velocidade no instante passado
- `Ts`: Período de amostragem

Com essa informação, você será capaz de indicar na interface a indicação de aceleração.

### Velocidade média

Pode ser calculada por quantas revoluções a roda deu em um determinado delta de tempo:

`vm = Pulsos/dT`

- `dT` deve ser o valor na qual você deseja atualizar a informação de velocidade média.

### Distância

A distância (`d`) percorrida pela bicicleta é: `d = 2*pi*r*N [m]`.

### RTT

O **Real Time Time** (RTT) é um timer similar ao TC, mas bem mais simples. Serve
apenas para contar `clocks`. Possui um registrador de 32 bits, ao contrário do
TC que o  registrador é de 12 bits. O RTT pode ser alimentado por dois clocks
distintos.  O que permite gerarmos interrupções com grandes períodos de tempo
vamos usar para medir `f` ou  gerar o `dT`)!

O RTT pode gerar interrupção por duas fontes distintas: `Alarme` ou `Mudança no
valor do relógio`. O Alarme funciona similar ao alarme do RTC,
podemos especificar um valor e quando o contador chegar nesse valor,
gera uma interrupção, ou podemos gerar uma interrupção toda vez que o valor
do timer mudar (tick). Isso vai depender da frequência 
na qual ele foi configurado (funcionando similar ao TC).

Utilize o exemplo disponibilizado em `SAME70-Examples/Perifericos-uC/RTT`
que inicializa e configura o RTT do SAME70 para resolver a questão do calculo de velocidade.

