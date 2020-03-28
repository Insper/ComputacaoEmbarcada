
| ENTREGA |
|---------|
| ~19/3~  |
| 31/3    |

Um sistema embarcado que reproduz uma [música monofonia](https://en.wikipedia.org/wiki/Monophony)

Um pouco de história:

<iframe width="1280" height="720" src="https://www.youtube.com/embed/jvIzIAgRWV0" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Rubrica

- A (1 item embarcado + 1 item C)
    - Embarcado
        - Utiliza dois falantes (para fazer uma música mais complexa)
        - Utiliza interrupção nos botões
    - `C`
        - Cria um arquivo `.c` `.h` com as funções de reprodução musical
        - Músicas organizadas em vetores de `structs` (ponteiros)
- B+
    - Uma terceira música
- B 
    - `README.md` explica o que é o projeto e como o software foi estruturado.
    - Música separada em `.h`
    - Utiliza `struct` para organizar as músicas
    - Código organizado em funções e que recebem `struct` contendo música
    - Utiliza `#define` sempre que necessário 
    - Fecha todos os `issues` que forem abertos no repositório (pelo professor)
- C
    - Repositório contém `README.md` com ligações elétrica e passos de como usar o projeto, assim como link para o vídeo.
    - Funcionalidade de `PAUSE`/ `PLAY`
    - Botão de seleção musical
    - Reproduz duas músicas (de forma inteligível)
    - LED piscando de acordo com a música
    - Indicação visual de qual música foi selecionada
- D
    - Faltando um item de C
- I
    - Mais que dois itens de C faltando


## Descrição

A entrega final deverá ser um sistema embarcado que via a adição de um [`buzzer`](https://en.wikipedia.org/wiki/Buzzer) ao uC o mesmo deve ser capaz de reproduz algumas músicas 'conhecida' de forma monofônica. Além do buzzer deve-se adicionar dois botões ao kit. Esses botões serão utilizados para: 

1. mudar de música
2. parar / iniciar a música.

!!! note "Entrega"
     Entrega:
     
    - Pode ser feito em dupla (não pode trio!!)
    - Cada grupo deve possuir um repositório (a entrega será feita ai)
    - **Deve entregar um vídeo da entrega funcionando.**
   
!!! warning "Direitos"   
    Todo código que for utilizado e não é de autoria da dupla, deve ser referenciado no projeto. Isso inclui músicas!
   
## Materiais

![](imgs/APS-1/falante.jpeg){width=500}

- 1x falante
- 2x botões (push buttons)
- 1x protoboard

!!! note "Retirar"
    Retirar com o Marco no Lab. de Arquitetura de Computadores.

## Entrega

Ao finalizar o projeto, preencher o forms a seguir:

- https://forms.gle/f7ZuBvc9tozxZRnaA

<iframe src="https://docs.google.com/forms/d/e/1FAIpQLSfShGFPTaxkz8oruUbTrAiY71d7v8xgtt8BbVqw4lEJe332fw/viewform?embedded=true" width="640" height="300" frameborder="0" marginheight="0" marginwidth="0">Loading…</iframe>


## Dicas

- https://www.youtube.com/watch?v=-kkxs_fekWM
- https://www.princetronics.com/supermariothemesong/
- https://www.hackster.io/muhammed-shameel-k-v/how-to-play-music-with-a-buzzer-and-arduino-b9a25d
- https://github.com/xitangg/-Pirates-of-the-Caribbean-Theme-Song/blob/master/Pirates_of_the_Caribbean_-_Theme_Song.ino

!!! tip
    Alunos dos alunos anteriores criaram um programa que converte automaticamente uma música (pode ser arquivo midi) para o embarcado (`.h`)
