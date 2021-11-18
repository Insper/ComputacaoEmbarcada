# Entrega 2: Engenharia

Além do design com o usuário, você deve ter os seguintes cuidados com a engenharia do protótipo. 

## Sobre a bicicleta

Iremos validar o projeto em uma bicicleta modelo [Tilt 100](https://www.americanas.com.br/produto/3087029593?epar=bp_pl_00_go_pla_teste_b2wads&opn=YSMESP&WT.srch=1&aid=6185afd7fe31a700171587e7&sid=2314041002202&pid=3087029593&chave=vnzpla_6185afd7fe31a700171587e7_2314041002202_3087029593&gclid=Cj0KCQiAkNiMBhCxARIsAIDDKNVfVowdYU_P6cwRM0FcRJMaNN_S35yhc55RV4zygtigrtenWDL29aMaAlnwEALw_wcB&tamanho=Unico&cor=Vermelha) que compramos para essa finalidade. Na bicicleta nós plugamos uma placa e um LCD, e também colocamos um sensor magnético na roda junto com um imã (para detectar rotacão).


| Bike | Diagrama |
|------|----------|
|![Placeholder](tilt120.png){width=300 } | ![](diagrama.png){width=300} |


!!! info
    O raio da nossa bicicleta é 20"


Você deve assumir as conexões a seguir no seu projeto:

| Item             | Conexão   |
|------------------|-----------|
| LCD              | EXT-2     |
| Sensor magnético | EXT-1 PB3 |
| LED R            | ?         |
| LED G            | ?         |
| LED B            | ?         |

A seguir detalhes sobre cada um dos dispositivos da bicicleta.

### Sensor magnético

O sensor magnético gera um pulso elétrico sempre que a roda fizer uma rotacão completa, você deve tratar esse pulso como um sinal digital, o sensor foi ligado no pino ==PB3 do EXT-1==.
![](onlysignal.png)
![](sensor.png){width=500}

!!! info
    Quando for configurar o pino para realizar a leitura do sensor ==DESABILITAR== o PULL_UP

### Fita NEON RGB

!!! warning
    TODO

## Medicões

A seguir detalhes de como podem ser realizadas a medições necessárias ao projeto:

### Velocidade instantânea 

Será necessário realizar a leitura da velocidade da bicicleta, existem algumas soluções que podem ser utilizadas:

A velocidade da bicicleta (v) é decorrente da velocidade angular (w) de sua roda, sendo calculado por: `v = w*r [m/s]`.

Existem duas maneiras de se calcular a velocidade angular: 

- mede-se o tempo (`t`) entre dois pulsos e a partir da frequência (`f=1/t`) calcula-se `w = 2*pi*f [rad/s]`
- acumula-se pulsos (`N`) em um determinado tempo (`dT`): `w = 2*pi*N/dT`

Como só conseguimos medir um pulso por rotação, é necessário que esse `dT` seja: suficiente alto  para medirmos uma velocidade relativamente baixa, mas não pode ser tão elevado, caso contrário teremos uma taxa de atualização da velocidade muito lenta.

!!! note
    Nesses dois casos não podemos utilizar o TC para medirmos a frequência (`f`) ou     gerar o `dT` pois  a menor frequência na qual o TC operar/medir é de 0.5Hz (o que daria uma velocidade mínima de 3.3Km/h).
    
    Vamos usar um novo periférico chamado de RTT (detalhes a seguir)

### Indicação de aceleração

É a derivada da velocidade, se positiva indica que a bicicleta está ganhando velocidade, negativa perdendo e próxima a zero a velocidade está estável. Para derivarmos a velocidade de forma discreta, utilizamos a equação a seguir:

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
