# Lab - Parte 1

| LAB                  |
| -------------------- |
| `Lab8-RTOS-LCD-LVGL` |

Neste laboratório iremos:

Agora vamos começar mexer com o LVGL e criar nossa interface. A ideia é recriar uma interface de um termostato inspirado no produto a seguir:

!!! info ""
     KKmoon LCD Touch Screen Termostato Sistema de Aquecimento de Piso Elétrico Aquecimento de Água Termorregulador AC85-240 V Controlador de Temperatura Preto 
    
     - https://www.amazon.com.br/KKmoon-Aquecimento-Termorregulador-Controlador-Temperatura/dp/B07X3CDM83

![](https://images-na.ssl-images-amazon.com/images/I/51iNUfjxJDL._AC_SL1000_.jpg){width=500}

## Etapas

Quando começamos projetar uma [interface homem máquina (IHM)](https://en.wikipedia.org/wiki/Human%E2%80%93computer_interaction) é necessário analisarmos várias frentes:

- Usabilidade
- Acessibilidade
- Branding
- Implementação

A usabilidade irá indicar como as funções do produto estarão disponíveis e serão exibidas aos usuários, isso deve estar atrelada aos conceitos da marca do produto. O público alvo deve ser analisado e o produto deve ser acessível, para isso, muitos testes de usabilidade devem ser feitos para validar o conceito.

Muitas vezes o protótipo da interface esbarra em problemas técnicos e de implementação, muitas imagens e fontes impactam no tamanho total do firmware que pode impossibilitar a implementação da interface proposta, ou necessitar a adição de formas alternativas de armazenamento de dados. Microcontroladores de forma geral não possuem GPU (alguns sim, exemplo: [STM32MP157](https://www.st.com/en/microcontrollers-microprocessors/stm32mp157.html) ) e isso impacta na performance da interface e muito provavelmente no gasto energético.

## Implementando

!!! tip
    Vamos usar muito a documentação do lvgl é importante que você tenha o site aberto e a consulte sempre:
    
    - https://docs.lvgl.io/latest/en/html/overview/index.html

O LVGL possui vasta documentação e muitos bons exemplos (testamos vários e todos funcionaram no embarcado), neste laboratório iremos usar alguns widgets do LVGL e aos poucos vamos customizando eles.

### Preparando firmware

Vamos criar uma nova função chamada de `void lv_termostato(void){ }` onde iremos fazer a implementação da interface do termostato. Além de criarmos esta função, teremos que modificar a `task_lcd` para chamar a nova função.

!!! example "Tarefa"
    Modifique o fimrware original incluindo a função `lv_termostato` e modificando a `task_lcd`:
    
    ```diff
    
    +void lv_termostato(void) {
    +    lv_obj_t * labelBtn1;

    +    lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    +    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    +    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

    +    labelBtn1 = lv_label_create(btn1);
    +    lv_label_set_text(labelBtn1, "Teste");
    +    lv_obj_center(labelBtn1);
    +
    +}

    static void task_lcd(void *pvParameters) {
    
    -  lv_ex_btn_1();
    +  lv_termostato();
    
      ....
      ....
    }
    ```

!!! progress
    Conclua as tarefas antes de prosseguir.

#### Background

Notem que a interface a ser recriada possui fundo preto, para atingirmos tal objetivo com o LVGL iremos modificar a configuração padrão do LVGL que está localizada em `config/lv_conf.h`. Neste arquivo procure pelo define `LV_THEME_DEFAULT_DARK` e modifique para 1.

!!! example "Tarefa"
    1. Modifique o define `LV_THEME_DEFAULT_DARK` de `0` para `1`
    1. Teste no uC
    
    Agora deve estar mostrando um fundo preto.
    
!!! progress
    Conclua as tarefas antes de prosseguir.

#### Tamanho da fonte

Vocês notaram que a fonte padrão do LCD está meio pequena? Conseguimos ajustar isso no LVGL escolhendo uma fonte maior. O LVGL disponibiliza alguns tamanhos de fonte de uma mesma classe (MontSerrat). A lista de fontes está no arquivo de configuração `src/config/lv_conf.h`. Neste arquivo dvocê deve encontrar algo como:

```c linenums="289"
/*Montserrat fonts with ASCII range and some symbols using bpp = 4
 *https://fonts.google.com/specimen/Montserrat*/
#define LV_FONT_MONTSERRAT_8  0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 0
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 0
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 0
...
```

Para recriar a interface iremos usar um tamanho de fonte um pouco maior que o padrão (14) do LVGL, para isso iremos utilizar a fonte de tamanho 24. Isso é feito em duas etapas:

1. Ativando a fonte no arquivo de configuração
1. Configurando a nova fonte como padrão

!!! info "Sistemas Embarcados"
    O LVGL não inclui todas as fontes por padrão (para o código não ficar muito grande). Sistemas embarcados sofrem com falta de memória. 
    
    | Fonte padrão | Program Memory Usage  |
    | ------ | --------------------  |
    |  14    | Program Memory Usage : 235852 bytes   11,2 % Full |
    |  24    | Program Memory Usage : 250904 bytes   12,0 % Full |
    
    O LVGL não lida com fontes de forma avanç©ada, cada letra da fonte é uma matriz que contém os pxs a serem assionados. Quanto maior a fonte maior precisa ser essa matrix e mais memória de programna utiliza.
    
    ==Parece pouca diferença né? Mas não é! Vamos sofrer um pouco com isso na nossa próxima APS.==

!!! example "Tarefa"
    Modifique o arquivo `lv_conf.h` para:
    
    1. Incluir a a fonte tamanho 24 no projeto
    ```diff
    #define LV_FONT_MONTSERRAT_12    0
    #define LV_FONT_MONTSERRAT_14    0
    ...
    +#define LV_FONT_MONTSERRAT_24   1
    ```
    2. Torne a fonte tamanho 24 padrão
    ```diff
    /*Always set a default font*/
    +#define LV_FONT_DEFAULT &lv_font_montserrat_24
    ```
    3. Teste no uC.

!!! progress
    Conclua as tarefas antes de prosseguir.

## Identificando widgets

A primeira etapa após ter a interface definida é identificar quais widgets podem ser utilizados para montar a interface. 

!!! question short
    Identifique quais widgets você usaria para reconstruir a imagem a seguir:
    
    ![](imgs/lab.svg){width=400}
    
    !!! tip
        Acesse a página do LVGL e de uma explorada nos widths que estão disponíveis:
        
        - https://docs.lvgl.io/master/widgets/core/index.html
        
    !!! details ""
        Podemos construir a tela toda usando apenas Botões e Labels.
        
        - (a): lv_label
        - (b): lv_button
        
        Os botões de power,.... podem ser botões com "símbolos" no lugar do texto.

!!! progress
    Click para continuar....
    
## Botões

!!! info ""
    https://docs.lvgl.io/master/widgets/btn.html

O `lv_button` permite que criemos um ou mais botões, os botões podem ou não ter um label associado a ele. Podemos associar para cada botão uma função de handler que será chamada assim que um evento neste botão for detectado, a seguir alguns eventos que podem ser gerados por um objeto:

- `LV_EVENT_PRESSED` An object has been pressed
- `LV_EVENT_PRESSING` An object is being pressed (called continuously while pressing)
- `LV_EVENT_PRESS_LOST` An object is still being pressed but slid cursor/finger off of the object
- `LV_EVENT_SHORT_CLICKED` An object was pressed for a short period of time, then released. Not called if scrolled.
- `LV_EVENT_LONG_PRESSED` An object has been pressed for at least the long_press_time specified in the input device driver. Not called if scrolled.
- A lista completa pode ser acessada na página de Events: https://docs.lvgl.io/master/overview/event.html

O exemplo fornecido na função (`lv_ex_btn_1`) cria um botão chamado `btn1` e o alinha no centro da tela, a função `event_handler` foi associada como callback deste widget, assim que um evento ocorrer a mesma será executada.

``` c
lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);
```

Depois cria um `label` e o associa ao botão:

``` c
label = lv_label_create(btn1);
lv_label_set_text(label, "Teste");
lv_obj_center(label);
```

Conforme a [documentação do lvgl para objetos](https://docs.lvgl.io/master/widgets/obj.html) Podemos alinhar um objeto em vários locais diferentes na tela. Isso é feito pela função `lv_obj_align(obj, obj_ref, LV_ALIGN_________, x_ofs, y_ofs)` que recebe como parâmetro:

- `obj` is the object to align.
-  `obj_ref` is a reference object. obj will be aligned to it. If `obj_ref = NULL`, then the parent of `obj` will be used.
-  The third argument is the type of alignment. These are the possible options: 

![](https://docs.lvgl.io/master/_images/align.png){width=500}

> Extraído da documentação.

!!! progress
    Click para continuar....

### Botão de power

Agora vamos criar os botões da interface proposta, primeiro iremos criar o botão de **power** modificando o botão atual de teste.

#### 1. Posição

Na primeira etapa iremos alinhar o botão no canto inferior esquerdo conforme figura a seguir:

![](imgs/lab-botoes.svg){width=500}

Um objeto pode ser alinhado com relação a um *screen* ou a um outro objetivo de referência. Nesse caso vamos usar o botão de power alinhado ao canto inferior da tela.

- Para alinhar com relação a tela usar: `lv_obj_align(obj, align, x, y);`
- Para alinhar com relação a outro objeto usar: `lv_obj_align_to(obj_to_align, reference_obj, align, x, y);`

 Os parâmetros X e Y são um deslocamento do alinhamento e o argumento *aling* pode ser qualquer uma dos itens a seguir:
 
=== "Interno"
    Utilizando a referência interna de um objeto:

    - `LV_ALIGN_TOP_LEFT`
    - `LV_ALIGN_TOP_MID`
    - `LV_ALIGN_TOP_RIGHT`
    - `LV_ALIGN_BOTTOM_LEFT`
    - `LV_ALIGN_BOTTOM_MID`
    - `LV_ALIGN_BOTTOM_RIGHT`
    - `LV_ALIGN_LEFT_MID`
    - `LV_ALIGN_RIGHT_MID`
    - `LV_ALIGN_CENTER`

=== "Externo"
    Utilizando a referência externa de um objeto:
    
    - `LV_ALIGN_OUT_TOP_LEFT`
    - `LV_ALIGN_OUT_TOP_MID`
    - `LV_ALIGN_OUT_TOP_RIGHT`
    - `LV_ALIGN_OUT_BOTTOM_LEFT`
    - `LV_ALIGN_OUT_BOTTOM_MID`
    - `LV_ALIGN_OUT_BOTTOM_RIGHT`
    - `LV_ALIGN_OUT_LEFT_TOP`
    - `LV_ALIGN_OUT_LEFT_MID`
    - `LV_ALIGN_OUT_LEFT_BOTTOM`
    - `LV_ALIGN_OUT_RIGHT_TOP`
    - `LV_ALIGN_OUT_RIGHT_MID`
    - `LV_ALIGN_OUT_RIGHT_BOTTOM`

!!! question choice
    Supondo dois objetos como ilustrado a seguir.
    Qual deve ser a função para alinharmos o obj2 ao lado do obj1?
    
    - A ideia é usar o btn1 como referência.
    
    ```
        +-------++-------+  
        |  btn1 ||  btn2 | 
        |       ||       | 
        +-------++-------+ 
    ```
    
    
    - [ ] `lv_obj_align_to(btn1, btn2, LV_ALIGN_BOTTOM_RIGHT, 0, 0);`
    - [ ] `lv_obj_align_to(btn2, btn1, LV_ALIGN_BOTTOM_RIGHT, 0, 0);`
    - [x] `lv_obj_align_to(btn2, btn1, LV_ALIGN_RIGHT, 0, 0);`
    - [ ] `lv_obj_align_to(btn1, btn2, LV_ALIGN_RIGHT, 0, 0);`

    !!! details ""
        
        - O primeiro parametro é o obj a ser alinhado: `obj2`
        - O segundo o obj a ser usado de referência: `obj1`
        - Queremos alinhas a direita e no meio.
        - Queremos o botão 2 "colado" no botão 1

!!! question choice
    Supondo dois objetos como ilustrado a seguir. 
    Qual deve ser a função para alinharmos o obj2 ao lado do obj1?
    
    - A ideia é usar o btn1 como referência.
    
    ```
        +-------+ 
        |  btn1 | 
        |       | 
        +-------+ +-------+
                  |  btn2 |
                  |       |
                  +-------+
    ```
    
    
    - [ ] `lv_obj_align_to(btn1, btn2, LV_ALIGN_BOTTOM_RIGHT, 0, 0);`
    - [x] `lv_obj_align_to(btn2, btn1, LV_ALIGN_BOTTOM_RIGHT, 0, 0);`
    - [ ] `lv_obj_align_to(btn2, btn1, LV_ALIGN_RIGHT, 0, 0);`
    - [ ] `lv_obj_align_to(btn2, btn1, LV_ALIGN_RIGHT, 0, 0);`

    !!! details ""
        Agora o truque é que queremos alinhar com o "Bottom" do botão 1. Por isso
        usamos o `LV_ALIGN_BOTTOM_RIGHT`
        
!!! progress
    Click para continuar....

!!! task
    Alinhe o botão `btn1` da função `lv_termostato` para o canto esquerdo
    inferior da tela.
    
    - Use a funcão `lv_obj_align` (a referência vai ser a tela).
    - Notem que o botão original da figura está um pouco deslocado para direita e para cima.
        - Modifiquem o X e o Y da funcão para obterem esse comportamento.
    - Teste no uC

!!! progress
    Click para continuar....

#### 2. Label/ Símbolo

No nosso código colocamos um "Label" dentro do objeto do botão, é por isso que aparecer o texto "Teste" no botão:

```c
labelBtn1 = lv_label_create(btn1);
lv_label_set_text(labelBtn1, "[  " LV_SYMBOL_POWER);
lv_obj_center(labelBtn1);
```

Notem que utilizamos o `lv_lavel_create` e passamos o `btn1` para a funcão. Isso faz com que o label pertenća ao objeto btn1.

Agora vamos trocar o label do btn1 para ser mais condizente com o do nosso modelo de referência. No LVGL podemos utilizar alguns símbolos já pré definidos, os detalhes estão na [documentação de fonts](https://docs.lvgl.io/master/overview/font.html) e listados aqui:

![](https://docs.lvgl.io/master/_images/symbols.png){width=300}

Notem que podemos usar o símbolo `LV_SYMBOL_POWER` para recriar o botão da interface planejada, para isso é necessário alterar a linha que estamos escrevendo `Teste` para usar o símbolo em questão. Por exemplo, para adicionarmos o [ seguido do símbolo de power:

```c
lv_label_set_text(labelBtn1, "[  " LV_SYMBOL_POWER);
```

Vocês podem definir o label como variável global, permitindo assim que outra parte do código altera o valor escrito.

```c
// global
static  lv_obj_t * labelBtn1;
```

!!! task
    1. Altere o label para ser global
    1. Modifique o label do botão para mostrar o [ ⏻
    1. Teste na placa
 
!!! tip
    O truque aqui foi juntar o [ e o power no mesmo botão, 
    
    ```
        +--------+  
        |        | 
        | [   ⏻ | 
        |        | 
        +--------+ 
           ^        
           | Botão
    ```
 
    Poderíamos ter feito diferente:
    
    ```
        +-------++-------+  
        |       ||       | 
        |   [   ||   ⏻  | 
        |       ||       | 
        +-------++-------+ 
           ^         ^
           |         | Botão
           | Apenas um label 
    ```
    
 
!!! progress
    Click para continuar....

#### 3. Formatando

Iremos agora criar um estilo próprio e aplicar no botão, um estilo pode conter várias configurações de Tema para um objeto (ou para vários). O exemplo a seguir cria um `style` com um fundo ROXO e uma borda VERDE.

```c
void lv_termostato(void) {
	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_PURPLE));
	lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREEN));
	lv_style_set_border_width(&style, 5);
```

E então aplicamos o novo estilo ao botão:

```diff
	lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
	lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
	lv_obj_align(btn1, LV_ALIGN_BOTTOM_LEFT, 0, 0);
+   lv_obj_add_style(btn1, &style, 0);
```

Também podemos mudar o tamanho de um objeto, como no exemplo a seguir:

```
	lv_obj_set_width(btn1, 60);  lv_obj_set_height(btn1, 60);
```

!!! tip "Cores"
    Existem cores pré definidas no LVGL e para cada cor uma plate entre no link a seguir para acessar a paleta:
    
    - https://docs.lvgl.io/master/overview/color.html#palette
    
    Para usar branco ou preto existe uma função:
    
    - lv_color_white() 
    - lv_color_black()
    
    Se quiser, pode formatar a sua própria cor em RGB, usando: `lv_color_make(red, green, blue);`

!!! task
    Crie um novo tema para o botão faca sentido para o nosso termostato. Precisamos de fundo preto e sem borda!
    
    1. Crie o novo estilo
    1. Aplique ao botão
    1. Teste e verifique o resultado

!!! progress
    Click para continuar....

### Demais botões

!!! example "Tarefa: Demais botões"
    Agora você é capaz de recriar os demais botões da interface, para cada botão criei uma função de callback (similar ao `event_handler`). 
    
    Implemente:
    
    - `M` (`btnMenu`/ `menu_handler`): Menu 
    - `Clock` (`btnClk`/ `clk_handler`): Relógio 
    - `^` (`btnUp`/ `up_handler`): Aumentar (temperatura/ alarme): 
    - `v` (`btnDown`/ `down_handler`): Baixar (temperatura/ alarme)
      
    ==Lembre de testar na placa! Vai precisar de ajustes.==
    
    !!! tip 
        
        Handlers:
        
        - ==Crie um handler diferente por botão.==
    
        Alinhamento:
        
        - Pense em como usar o alinhamento a seu favor.
    
        Símbolos:
        
        - Relógio: Você pode usar um outro símbolo no lugar.
        - v, ^: Tem símbolos prontos para isso
        
    Resultado esperado:
    
    > O seu pode ficar diferente, mas lembre que a ideia é chegar o mais perto do que da nossa referencia!
    
    | Meu | Referencia |
    | ---- | ---------- |
    | ![](imgs/btn_all.jpeg){width=300} | ![](https://images-na.ssl-images-amazon.com/images/I/51iNUfjxJDL._AC_SL1000_.jpg){width=300} | 
