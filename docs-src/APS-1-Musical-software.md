# APS 1 - Musical - Firmware

A seguir iremos explicar os conceitos e dicas de como vocês deverem prosseguir para
executarem esta APS.

## Músicas monofonica

Músicas monofonicas[^1] são aquelas que só possuem uma única nota tocada por vez, como indicado na partitura a seguir:

![](https://upload.wikimedia.org/wikipedia/commons/4/4a/Pop_Goes_the_Weasel_updated.png){width=400}

> ref: wikipidia

[^1]:  https://en.wikipedia.org/wiki/Monophony

A música monofonica tem a textura a seguir:

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

[^2]: https://en.wikipedia.org/wiki/Loudspeaker

<iframe width="560" height="315" src="https://www.youtube.com/embed/77h1JhD9Syw" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Gerando som

Podemos fazer com que o buzzer oscile em uma determinada frequência, para isso basta gerarmos um sinal de onda quadrada  no terminal positivo do dispositivo, isso irá fazer com que o piezo movimente na mesma frequência, gerando o tom desejado.

!!! info "Frequências"
    Lembre que uma onda quadrada pode ser decomposta em infinitas senoides pela
    transformada de Fourier. 
    ![](https://mathworld.wolfram.com/images/eps-gif/FourierSeriesSquareWave_800.gif){width=300}
    
    Sendo a componente principal (de maior energia) centrada na frequência da onda quadrada:
    
    ![](https://mathworld.wolfram.com/images/equations/FourierSeriesSquareWave/NumberedEquation3.gif)

    Portanto o som que iremos escutar será composto da frequência principal mais as secundárias e harmónicas.

    > ref: https://mathworld.wolfram.com/images/eps-gif/FourierSeriesSquareWave_800.gif

Existem algimas maneiras de gerarmos uma onda quadrada em um pino do microcontrolador, a que estamos sugerindo aqui não envolve nenhum periférico específico do microcontrolador, logo iremos fazer tudo por código:


!!! example "Exemplo:"
    Onda quadrada de 1000 Hz:
    
    ```c
    while(1){
        pio_set(...);
        delay_ms(1);
        pio_clear(...);
        delay_ms(1);
    }
    ```
