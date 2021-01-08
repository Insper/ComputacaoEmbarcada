# APS 1 - Musical

Nesta APS vocês irão desenvolver um sistema embarcado que reproduz uma [música monofonia](https://en.wikipedia.org/wiki/Monophony), para isso, irão utilizar um 
buzzer conectado a um pino do microcontrolador.

!!! info "Um pouco de história:"
    <iframe width="520" height="320" src="https://www.youtube.com/embed/jvIzIAgRWV0" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Regras

Leia atentamente as regras a seguir:

!!! warning "Plágio"
    - Você não pode copiar código (parcial ou total) de outro grupo (do mesmo ou de outro semestre).
    - Você pode usar qualquer código fornecido pela equipe.
    - Código da internet? Você não pode copiar grandes trechos.
    - Código da internet? Se usou alguma coisa, referencie no README.
    
    A regra completa pode ser acessada em: https://www.insper.edu.br/portaldoaluno/wp-content/uploads/2018/08/orientacoes_integridade_intelectual-Engenharias.pdf
    
!!! info "Atraso"
    - Para cada 3 dias de atraso será descontado meia rubrica.
 
!!! tip "Dupla"
    - A APS pode ser realizada em dupla.
    - Você não vai poder repetir dupla na próxima APS.
    - O desenvolvimento do projeto deve ser feito em um repositório git (a entrega também)

!!! tip "Entrega"
    - Ao finalizar o projeto preencher o forms: https://forms.gle/f7ZuBvc9tozxZRnaA

## Descrição

A entrega final deverá ser um sistema embarcado que via a adição de um [`buzzer`](https://en.wikipedia.org/wiki/Buzzer) ao uC o mesmo deve ser capaz de reproduzir músicas 'conhecidas'. Além do buzzer deve-se adicionar dois botões ao kit, para ser usado: 

- mudar de música
- parar / iniciar a música.

## Materiais

Os materiais a seguir estão disponíveis no kit de embarcados e são necessários para realizar a APS:

- 2x botões (push buttons)
- 1x protoboard
- 1x buzzer 

![](imgs/APS-1/falante.jpeg){width=200}



## Referências

A seguir algumas referências:

- https://github.com/robsoncouto/arduino-songs/
- https://www.youtube.com/watch?v=-kkxs_fekWM
- https://www.princetronics.com/supermariothemesong/
- https://www.hackster.io/muhammed-shameel-k-v/how-to-play-music-with-a-buzzer-and-arduino-b9a25d
- https://github.com/xitangg/-Pirates-of-the-Caribbean-Theme-Song/blob/master/Pirates_of_the_Caribbean_-_Theme_Song.ino

## Rubrica

!!! info "Entrega"
    - Ao finalizar o projeto preencher o forms: https://forms.gle/f7ZuBvc9tozxZRnaA

A rubrica a seguir será aplicada a nota da entrega:

- A (1 item de **Embarcado** + 1 item de **Linguagem C**)
    - **Embarcado**
        - Utiliza dois falantes (para fazer uma música mais complexa)
        - Utiliza interrupção nos botões
    - **Linguagem C**
        - Cria um arquivo `.c` `.h` com as funções de reprodução musical
        - Músicas organizadas em vetores de `structs` (ponteiros)
- B+
    - `README.md` explica como o software foi estruturado
    - Faz uso de `#define` sempre que possível 
    - Terceira música
- B 
    - Música separadas em arquivos `.h`
    - Utiliza `struct` para organizar as músicas
    - Código organizado em funções e que recebem `struct` contendo música
    - Fecha todos os `issues` que forem abertos no repositório (pela equipe)
- C
    - Repositório contém `README.md`com ligações elétrica e passos de como usar o projeto, assim como link para o vídeo e **referência a outros códigos**
    - Funcionalidade de `PAUSE`/ `PLAY`
    - Botão de seleção musical
    - Reproduz duas músicas (de forma inteligível)
    - LED piscando de acordo com a música
    - Indicação visual de qual música foi selecionada
- D
    - Faltando um item de C
- I
    - Mais que dois itens de C faltando

