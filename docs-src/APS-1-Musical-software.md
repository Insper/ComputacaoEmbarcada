# APS 1 - Musical - Firmware

A seguir iremos explicar os conceitos e dicas de como vocês deverem prosseguir para
executarem esta APS.

!!! info
    1. Lembrem de trabalhar no repositório criado pelo classroom:
        - https://classroom.github.com/g/jRtKiGWA
        
    1. Leia atentamente como trabalhar no repositório:
    
        - [APS HowTo](/ComputacaoEmbarcada/APS-howto/)
        
## Músicas monofonica

Músicas monofonicas[^1] são aquelas que só possuem uma única nota tocada por vez, como indicado na partitura a seguir:

![](https://upload.wikimedia.org/wikipedia/commons/4/4a/Pop_Goes_the_Weasel_updated.png){width=400}

> ref: wikipidia

[^1]:  https://en.wikipedia.org/wiki/Monophony

A música monofonica tem o som como a seguir:

<figure>
    <figcaption>Pop Goes the Weasel.ogg (wiki)</figcaption>
    <audio
        controls
        src="https://upload.wikimedia.org/wikipedia/commons/d/d5/Pop_Goes_the_Weasel.ogg">
            Your browser does not support the
            <code>audio</code> element.
    </audio>
</figure>

Esse tipo de música foi muito utilizada nos primeiros videogames, quando a sintetização de músicas ainda estava no começo.  Veja como era feito nos Nintendo, aqui já era possível gerar mais de um tom por vez:

<iframe width="520" height="320" src="https://www.youtube.com/embed/jvIzIAgRWV0" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Buzzer

Para gerarmos o som é necessário termos algum dispositivo capaz de gerar movimentação no ar, o buzzer é um dispositivo simples que a partir de uma bobina (controlada por um terminal) conseguimos movimentar um disco que por sua vez movimentar o ar. Os buzzers podem ser de duas categorias (piezoelétricos):

- **Ativo:** basta energizar o terminal que o dispositivo vibra automaticamente em uma determinada frequência, muito usado para alarmes.
- **Passivo:** Um circuito externo (ou microcontrolador) deve gerar a frequência de vibração, usado para gerar som.

Buzzers são diferentes de altofalantes[^2] em vários aspectos (mecânico, eletromecânico): não necessitam de tensão negativa; possuem um espectro de operação menor; baixa resistência; baixa potência ... .

A conexão do buzzer com um microcontrolador se da por dois pinos: Um conectado no terra (gnd) e outro conectado
em um pino que o microcontrolador possui controle, conforme ilustração a seguir:

![image](https://user-images.githubusercontent.com/1039615/109496798-e660e380-7a6f-11eb-831d-604cce45f5f6.png){width=500}

[^2]: https://en.wikipedia.org/wiki/Loudspeaker

<iframe width="560" height="315" src="https://www.youtube.com/embed/77h1JhD9Syw" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Gerando som

Podemos fazer com que o buzzer oscile em uma determinada frequência, para isso basta gerarmos um sinal de onda quadrada  no terminal positivo do dispositivo, isso irá fazer com que o piezo movimente na mesma frequência, gerando o tom desejado.

!!! tip "Notas"
    As notas musicais são definidas pela frequência principal que elas emitem, um Dó-4 é definido por 262 Hz, um Lá-4 por 440Hz e assim por diante (o 4 se refere ao meio do piano). Além da frequência principal, cada instrumento musical emite outras frequências que compõem o som, gerando um som único para cada instrumento.
    
    Iremos usar a notacao americana para as notas:
    
    | Dó | Ré | Mi | Fá | Sol | Lá | Sí |
    |----|----|----|----|-----|----|----|
    | C  | D  | E  | F  | G   | A  | B  |
    
    ![](https://upload.wikimedia.org/wikipedia/commons/thumb/6/65/Frequency_vs_name.svg/350px-Frequency_vs_name.svg.png)
    
    > Ref: https://upload.wikimedia.org/wikipedia/commons/thumb/6/65/Frequency_vs_name.svg/350px-Frequency_vs_name.svg.png Wikipidia 

!!! info "Frequências"
    Lembre que uma onda quadrada pode ser decomposta em infinitas senoides pela transformada de Fourier. 
    
    ![](https://mathworld.wolfram.com/images/eps-gif/FourierSeriesSquareWave_800.gif){width=300}
    
    Sendo a componente principal (de maior energia) centrada na frequência da onda quadrada (no nosso caso):
    
    ![](https://mathworld.wolfram.com/images/equations/FourierSeriesSquareWave/NumberedEquation3.gif)

    Portanto o som que iremos escutar será composto da frequência principal mais as harmónicas.

    > ref: https://mathworld.wolfram.com/images/eps-gif/FourierSeriesSquareWave_800.gif
    
    <iframe width="560" height="315" src="https://www.youtube.com/embed/3IAMpH4xF9Q" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Existem diversas maneiras de gerarmos uma onda quadrada em um pino do microcontrolador, a que estamos sugerindo aqui não envolve nenhum periférico específico do microcontrolador, logo iremos fazer tudo por código.

Por exemplo, para gerar uma onda quadrada de 1000 Hz:
    
```c
while(1){
    pio_set(...);
    delay_us(500);
    pio_clear(...);
    delay_us(500);
}
```

!!! info 
    Tudo depende do microcontrolador, mas podemos gerar uma onda quadrada com os periféricos: PWM, TimerCounter. As vantagens de fazermos isso são:
    
    - Não inutilizamos o CORE com as funcoes de delay
    - Conseguimos facilmente ter mais de uma frequência gerada.
    - Menor gasto energético

## Música

Eu fiz por anos aula de sax alto e meu professor falava que para começar a tocar uma música bastava: `tocar a nota certa no momento certo e não tocar quando não for para tocar`, para quem tem prática é fácil, mas para mim não era. Trouxe este assunto para explicar um pouco como iremos reproduzir uma música. Cada música será formada por notas (frequências), pela duração da nota e por um silêncio entre notas (que também tem duração ). Toda essa informação está presente na partitura:

![](https://cdn.statically.io/img/www.musicnotes.com/now/wp-content/uploads/2018/02/4.png?quality=80&f=auto)

> ref: https://www.musicnotes.com/now/tips/how-to-read-sheet-music/

Portanto para reproduzirmos uma música teremos que para cada intervalo de tempo:

1. Reproduzir uma nota (gerar a frequência da nota no pino do buzzer) ou não tocar nada (pausa)
1. Manter a nota/pausa pelo tempo determinado
1. Ir para o próximo intervalo de tempo

## Referência

Nesta APS é para utilizarem as músicas fornecidas no repositório a seguir: 

- https://github.com/robsoncouto/arduino-songs

> Fornecido por:  Robson Couto, 2019

!!! info
    Os exemplos deste repositório só funcionam em Arduino, não conseguimos usar de maneira direta no nosso kit de desenvolvimento.

!!! warning
    Lembre de referenciar o repositório quando utilizar as músicas por ele fornecido. Como descrito no próprio README.
    
    > Every sketch here has been written by myself, although based on scores I found online or books I own. These scores are linked in each file when possible. You can use the sketches for anything, I only kindly ask that you give credit if you use these codes on a tutorial, video, example, etc.
 
## Analisando firmware 

O desenvolvedor disponibiliza diversas músicas de vários temas diferentes: Filmes, Jogos, Clássicas, ... . Vamos analisar como as músicas são disponibilizadas. Para isso iremos pegar como exemplo a música tema do Mário:

- https://github.com/robsoncouto/arduino-songs/blob/master/supermariobros/supermariobros.ino

### Notas

No comece do arquivo temos as definições das notas:

```c
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
```

### Música

No arquivo disponível um vetor chamado `melody` que possui nos index pares (`0`, `2`, ...) as notas e nos index ímpares ( `1`, `3`, ... ) o tempo de furacão da nota (com base em uma referência).

```c
// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Super Mario Bros theme
  // Score available at https://musescore.com/user/2123/scores/2145
  // Theme by Koji Kondo
  
  
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
  NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,

```

### Tempo

Os tempos são definidos em partes de uma **Semibreve/wholenote**[^3]  (que é a nota de maior duração), ou seja, o valor 4 refere-se a $1/4$ da semibreve, 8 a $1/8$ do tempo total... .

[^3]: https://pt.wikipedia.org/wiki/Semibreve

O valor da semibreve/wholenote é definida no próprio código:

```c
// change this to make the song slower or faster
int tempo = 200;

// hide code
// ....

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;
``` 

Valores negativos de tempo (**-4**, **-8**, ... ) representam que a nota tem a duração dela mais meio tempo.  

No código do repositório, ele implementa o cálculo da duracão da nota da seguinte maneira:

```c
// calculates the duration of each note
divider = melody[thisNote + 1];
if (divider > 0) {
    // regular note, just proceed
    noteDuration = (wholenote) / divider;
} else if (divider < 0) {
    // dotted notes are represented with negative durations!!
    noteDuration = (wholenote) / abs(divider);
    noteDuration *= 1.5; // increases the duration in half for dotted notes
}
```

- `thisNote` é o index da nota atual.

!!! tip
    Eu reescreveria este trecho de código da seguinte maneira, com o objetivo
    de ficar mais simples e compacto:
    
    ```c
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    noteDuration = (wholenote) / abs(divider);
    if (divider < 0) {
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    ```
    
### Reproduzindo

Agora já temos tudo para reproduzir a música, precisamos varrer o vetor `melody` e para cada nota (index par) gerar a onda quadrada no pino pelo tempo determinado em: `noteDuration`, para isso definem o tamanho do vetor:

```c

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
```

!!! info "C: tipos"
    
    A linguagem C opera com tipos de dados multiplos de um byte (8 bits), e possui
    duas maneiras de indicar o tipo da variável:
    
    | byte     | half word | word      | duble word |
    |----------|-----------|-----------|------------|
    | `char`   | `short`   | `int`     | ` long`    |
    | `int8_t` | `int16_t` | `int32_t` | `int64_t`  |

!!! info "C: sizeof"
    `sizeof(type)` recebe como parâmetro um tipo (pode ser uma variável, vetor ou struct) e retorna **quantos bytes** o tipo ocupa! Veja os exemplos a seguir: 
    
    ```c
    uint32_t foo;
    printf("Tamanho foo em bytes: %d \n", sizeof(foo));
    // $ Tamanho foo em bytes: 4
    
    uint32_t bar[2];
    printf("Tamanho bar em bytes: %d \n", sizeof(bar))
    // $ Tamanho bar em bytes: 8
    ```
    
    Note que a variável `foo` ocupa **4 bytes** (pois é um inteiro: $32/8=4$) e o vetor
    `bar` ocupa **8 bytes**, pois aloca dois enderecos de memória do tipo int.
    
    O `sizeof` é executado em tempo de compilação, não podemos usar para memórias
    alocadas dinâmicamente:
    
    ```c
    // não podemos fazer isso!
    int *foo = malloc(32);
    printf("Tamanho bar em bytes: %d \n", sizeof(foo))
    ```
    
E então interage no vetor e reproduz a nota usando a função `tone`

```c
  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    // ...
    // ... hide
    
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
```

A função `tone` do Arduino gera uma onda quadrada em um pino (`buzzer`), de frequência `melody[thisNote]` e duração `noteDuration * 0.9`. 

!!! tip "tone"
    Vocês vão ter que implementar uma função  `tone` própria!
    
### `tone`

!!! tip
    Apenas uma sugestão de como implementar.

Sugerimos implementarem uma função que receba como parâmetro uma frequência e um tempo (em milissegundos) e que reproduza uma onda quadrada em um pino do microcontrolador, na frequência e tempo passado como argumento para a função.

```c
/**
 * freq: Frequecia em Hz
 * time: Tempo em ms que o tom deve ser gerado
 */
void tone(int freq, int time){
    ....
    ....
}
```

!!! info
    Como fazer? O melhor jeito é contar quantos pulsos (freq) existem dentro de um tempo (time) e então
    fazer um loop que gere a quantidade de pulsos (na frequência certa).
