## Praticando - OLED

| Pasta               |
|---------------------|
| `Led3-OLED-PIO-IRQ` |

Agora vamos praticar um pouco o uso de interrupção, para isso vocês deverão abrir/ criar um novo projeto.

Copie o projeto localizado no repositório de exemplos: [`SAME70-examples/Screens/OLED-Xplained-Pro-SPI/`](https://github.com/Insper/SAME70-examples/tree/master/Screens/OLED-Xplained-Pro) para a pasta do seu repositório de laboratórios da disciplina `Lab3-OLED-PIO-IRQ`.

Iremos trabalhar com esse exemplo que configura o OLED (que deve ser conectado na placa no **EXT1**) e incorporar o exemplo da interrupção aqui (vamos ampliar sua funcionalidade!).

A entrega final (conceito A) deve possuir três botões externos a placa que irão configurar a frequência na qual o LED irá piscar (via interrupção é claro). Um dos botões irá aumentar a frequência do piscar do LED e o outro irá diminuir a frequência que o LED deverá piscar. O OLED deverá exibir a frequência atual do LED. 

- O código deve funcionar por interrupção nos botões **e sempre que possível, entrar em sleep mode**.

### Conceito C

Agora você deve adicionar o botão 1 da placa OLED para alterar a frequência na qual o LED irá piscar. Além disso, você precisa exibir o valor da frequência no display do OLED.

1. Botão OLED1: Modifica a frequência do LED (por IRQ)
    - Se usuário aperta e solta: Aumenta a freq em uma unidade ( `delay -= 100` )
    - Se usuário aperta e segura: Diminui a freq em uma unidade ( `delay += 100` )
3. Exibir o valor da frequência no OLED

!!! tip
    Para escrevermos uma string no OLED devemos usar a função:
    
    ```c
    void gfx_mono_draw_string(const char *str, const gfx_coord_t x, const gfx_coord_t y, const struct font *font);
    ```
    
    Que recebe como parâmetro:
    
    - `cont char str`: String com o texto a ser escrito no OLED
    - `gfx_coord_t x`: Coordenada pixel **X** de onde a string irá ser escrita
    - `gfx_coord_t y`: Coordenada pixel **Y** de onde a string irá ser escrita
    - `const struct font *font`: Fonte a ser utilizada, a configuração dela está em `src/config/conf_sysfont.h`
    
    Notem que a função recebe uma string e não um inteiro, então vocês ==NÃO PODEM== fazer isso:
    
    ```c
    // ------------------
    // - ATENCÃO ERRADO -
    // ------------------
    int cnt = 5;
    gfx_mono_draw_string(cnt, 0, 0, &sysfont);
    //                   (1)
    ```
    
    1. :warning: Não pode pois não é uma string!!
    
    Lembrem que em C uma string é um vetor de char em ASCII terminado em NULL, então precisamos converter o valor inteiro 5 em uma string.
    
    Existe uma função muito interessante em C que é a `sprintf`, que funciona de forma similar ao `printf` só que no lugar de enviar a string formatada para o terminal a `sprintf` formata a string em um vetor. Veja o exemplo a seguir:
    
    ```c
    int cnt = 5;
    char str[128]; // (1)
    
    sprintf(str, "%d", cnt); // (2)
    gfx_mono_draw_string(str, 0, 0, &sysfont);
    ```
    
    1. Declaramos um vetor (`str`) para armazenar a string formatada. 
    2. Agora usamos a função `sprintf` para formatar uma string no vetor `str`. Podemos formatar a string como de forma similar ao printf, exe: `sprintf(str, "O cnt é: %d", cnt);`
    
    Alguns detalhes:
 
    - O OLED possui dimensões de 128x32 pixels, o texto não pode passar desse tamanho!
    - Tome cuidado com o tamanho da string pois ele deve ser capaz de armazenar toda o texto formatado.
    
    
!!! exercise choice 
    Podemos chamar as funções que manipulam o OLED dentro de interrupção/ callback do botão?
    
    - [x] **NÃO** podemos.
    - [ ] **SIM** podemos.
    
    !!! answer
        Não podemos atualizar o OLED dentro de interrupções e callbacks de HW, pois é um evento demorado e as funções não são reentrantes.
        
        A solução é atualizar o display no main via uso de flags.

!!! exercise self
    Comecando:
    
    1. Configure o LED e Botão da placa OLED para operar com IRQ.
    1. Faca o exemplo anterior funcionar (com o novo led e botão)
    1. Crie uma variável para frequência, exiba o valor no OLED
    1. Implemente apenas o incremento da frequência, teste.
    1. Pense na lógica de como identificar uma aperto longo
    1. Implemente o decremento da frequência.
    1. Teste sempre na placa.
    
    !!! tip ""
        Utilize o DEBUG: https://www.youtube.com/watch?v=dMm4CmQkqPI
    
    !!! warning ""
        Lembrem:
        
        - Não podemos ter delay dentro de interrupção.
        - O OLED não pode ser atualizado dentro de irq.

    Display Oled: 
    
    - Você deve usar [sprintf](http://www.cplusplus.com/reference/cstdio/sprintf/) para formatar a string que irá exibir no OLED
    - Para exibir uma string no OLED use a função `gfx_mono_draw_string`

<iframe src="https://docs.google.com/forms/d/e/1FAIpQLSdkaentSBXvZlMgnyHKyI77-YC67N8jyH7Z1ZJ2-K7UUKSD2w/viewform?embedded=true" width="640" height="320" frameborder="0" marginheight="0" marginwidth="0">Carregando…</iframe>

### Conceito B

!!! exercise self
    Acrescente os outros dois botões do oled (2 e 3) do OLED para:

    - Botão 2: Para o pisca pisca
    - Botão 3: Diminuir a frequência

### Conceito A

!!! exercise self
    Exiba no OLED não só a frequência, mas uma barra indicando quando o LED irá parar de piscar (como uma barra de progresso).
