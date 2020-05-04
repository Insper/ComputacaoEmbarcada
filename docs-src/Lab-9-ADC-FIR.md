# RTOS - ADC - FIR

![](https://www.mathworks.com/matlabcentral/mlc-downloads/downloads/submissions/53983/versions/5/previews/html/ExampleECGBitalino_02.png)

>Fonte: https://www.mathworks.com/matlabcentral/mlc-downloads/downloads/submissions/53983/versions/5/previews/html/ExampleECGBitalino.html

Nesse lab iremos modificar o lab original que fazia a leitura do potenciometro via o periférico AFEC e fazia a exibição do valor no LCD. Será aplicado um filtro passa baixas ao sinal, e o mesmo será exibido no LCD de forma temporal.

!!! note "Preencher ao finalizar o lab"
    - MARCO Inserir link plz
    
## Lab    

| LAB                   |
|-----------------------|
| `Labs/9-RTOS-ADC-FIR` |

!!! warning "Código exemplo"
    - Vamos modificar **o seu lab** Lab-5-RTOS-ADC (aquele do potenciometro), faça uma cópia do seu lab para a nova pasta no seu seu repositório `Labs/9-RTOS-ADC-FIR`
    
!!! note "Terminal"
    Esse exemplo faz uso da comunicação UART para debug de código (via printf), para acessar o terminal no atmel estúdio clique em:  :arrow_right: View :arrow_right: Terminal Window
    
    Configure o terminal para a porta que (COM) correta (verificar no windiows) e para operar com um BaudRate de `115200`.

### FIR

Filtragem de sinal pertence a uma grande área do conhecimento que é processamento de sinais, nesse laboratório iremos tratar do tema de forma superficial.

!!! tip
    Para saber mais, leia: [The Scientist and Engineer's Guide to
Digital Signal Processing](http://www.dspguide.com/)

O [`Finite Impulse Response` (FIR)](https://en.wikipedia.org/wiki/Finite_impulse_response) é uma técnica de processamento digital de sinais (DSP) que é capaz de realizar filtragens em um sinal. Com o FIR somos capazes de aplicar um filtro do tipo: 

- passa baixas: Elimina as altas frequências
- passa altas: Elimina as baixas frequências
- mata faixa: Elimina uma faixa de frequências do sinal

Filtros digitais do tipo FIR possuem as seguintes vantagens:


1. São estáveis por natureza
1. Podem ser projetados para ter fase linear
1. Possuem flexibilidade no seu projeto
1. São fáceis de implementar 

O filtro possui a seguinte estrutura:

$$y[n] = b_0*x[n] + b_1*x[n-1] + .... b_n*x[n-N]$$

Onde:

- $y[n]$: Valor filtrado
- $x[n-N]$: Valor do dado não filtrado, atrasado de N amostras
- $b_n$: Coeficiente do filtro
- $N$: Ordem do filtro

Podemos representar a equação graficamente:

![](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9b/FIR_Filter.svg/600px-FIR_Filter.svg.png)
> Fonte: https://en.wikipedia.org/wiki/Finite_impulse_response

- $Z^{-1}$: Significa um atraso na amostra

#### Projeto do filtro

Podemos realizar o projeto do filtro FIR (achar a ordem N e os coeficientes B) de diversas maneiras diferentes, cada um possui uma vantagem sobre a outra. Vamos utilizar o [`Equiripple Algorithm`](https://www.weisang.com/en/documentation/firfilterremezalgorithm_en/#) que possui `ripples` em torno da frequência de corte (`fc`).

![](https://www.recordingblogs.com/rbdocs/wiki/equiripplefilter-initialmagnituderesponse.png)

> Fonte: https://www.recordingblogs.com/wiki/equiripple-filter

O projeto do filtro envolve vários parâmetros, vamos verificarmos os mais importantes:

- $f_s$: Frequência de amostragem do sinal 
- $f_c$: Frequência de corte, quando a componente espectral já possui um ganho baixo e não influencia 'tanto' no sinal. Na $f_c$ o ganho do sinal é geralmente -3dB, o que significa em volts, que o sinal possui $sqrt(1/2)=0.707$ do seu valor inicial.

!!! note
    A filtragem não só altera o valor absoluto de um dado, como também afeta sua frequência! Dependendo do sinal, isso pode afetar o resultado.
    
Para o projeto do filtro vamos utilizar uma ferramenta em python [`pyfda`](https://github.com/chipmuenk/pyFDA/) que vai nos ajudar encontrar os coeficientes `b` e `N`. 

1. Download do programa
1. Instalar `requirements` 
1. Projetar FIR
1. Extrair B e N

Faça o download do repositório, instale dependências e execute o programa:

```bash
git clone  https://github.com/chipmuenk/pyFDA/
cd pyFDA
pip3 install -r requirements.txt --user
python3 -m pyfda.pyfdax
```

Configure o filtro para:

### Modificando RTOS-UART (entrega)

!!! tip
    Estou supondo que o lab RTOS-UART entregue até C.
    
Vamos fazer a seguinte modificação:

1. Inserir um TC e ele fará a chamada da conversão do sinal analógico
1. 

!!! note
    Iremos usar o TC inicializando a conversão no lugar de fazer isso na task, pelos seguinte motivos:
    1. Garantir que a aquisição 
    
    
#### 
