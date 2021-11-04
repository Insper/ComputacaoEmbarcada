# Lab - Parte 2

!!! info
    Não podemos esquecer nossa referencia!
 
    ![](imgs/lab.svg){width=400}

Vamos implementar os itens que são apenas "Labels (a)": Temperatura atual, relório, set-point. Mas antes será preciso escolhermos a fonte que iremos usar na interface, o lvgl possui algumas fontes disponíveis por padrão, mas nem sempre atendem a necessidade da interface. As fontes padrões do LVGL estão no link a seguir:

- https://docs.lvgl.io/master/overview/font.html

!!! info
    Lembre que para usar as fontes padrões do LVGL é necessário editar o arquivo: `config/lv_conf.h`

Para a interface proposta sugiro usarmos a fonte DSEG (open source) e que lembra um display de sete segmentos:

https://github.com/keshikan/DSEG

![](https://raw.githubusercontent.com/keshikan/DSEG/master/sample/all_DSEG_list.png){width=500}

!!! example "Tarefa"
    1. Baixe a fonte para o seu computador
       - https://github.com/keshikan/DSEG/releases/download/v0.46/fonts-DSEG_v046.zip
    1. Extrai a pasta

!!! progress
    Click para continuar....

### Floor Temp

Vamos agora implementar o label da temperatura atual do piso, e iremos seguir os passos a seguir:

1. Converter fonte para uso no lvgl
1. Adicionar no lvgl/ Microchip studio
1. Criando label e usando fonte

#### 1. Convertendo

Com a fonte escolhida precisamos agora converter para o formato que o LVGL consegue interpretar (bitmap), para isso usaremos a ferramenta online do LVGL. Acesse o site:

- https://lvgl.io/tools/fontconverter

Vamos criar uma fonte de **tamanho 70** -> **DSEG7-Modern/DSEG7Modern-Regular.ttf**, esse arquivo será usada no site e foi extraído na etapa anterior. Configure a interface como no exemplo a seguir:

- Name: `dseg70`
- Size: `70`
- Bpp: `1 bit-per-pixel`
- TTF: `DSEG7-Modern/DSEG7Modern-Regular.ttf`
- Symbols: `-./0123456789 :` (o espaço  é necessário pq ele é um caráter)

!!! info "Symbols"
    A fonte gerada terá somente esses símbolos, se você quiser usar por exemplo a letra C não vai poder. Gerar somente os símbolos que vai usar é importante porque o uC possui pouca memória e não seria possível ter várias fontes diferentes com todos os símbolos.

O site irá gerar um arquivo `dseg70.c` salve o mesmo dentro da pasta `src/` do projeto (a mesma que contém o arquivo main.c) que estamos trabalhando.

!!! progress
    Click para continuar....

#### 2. Adicionando no Microchip Studio

Agora é necessário adicionar o arquivo ao MS:

1. Clique com o botão direito em src e clique em Add > Existing Item...
1. Encontre o arquivo dseg120.c que foi baixado e clique em Add
1. Verifique se o arquivo dseg120.c foi adicionado

![](imgs/add_file.png){width=400}

![](imgs/add_file_2.PNG){width=400}

![](imgs/add_file_3.PNG){width=300}
    
!!! info
    O exemplo foi feito para a fonte de tamanho 120, mas depois resolvemos trocar por uma menor, note que onde na imagem tem dseg120 você deve colocar a dseg70.
    
!!! progress
    Click para continuar....
    

#### 3. Criando label e usando fonte

Agora podemos utilizar a nova fonte no nosso projeto, ainda dentro da `lv_termostato` vamos criar um novo label que irá exibir o valor da temperatura atual. Fazemos isso similar ao botão, porém agora iremos associar o label a tela e não ao botão e também iremos customizar a fonte para usarmos o `dseg70`.

Crei a variável global que irá apontar para o label:

```c
lv_obj_t * labelFloor;
```

E então modifique a função termostato:

```c
  void lv_termostato(void){
    // ....
    // ....
    
    
    labelFloor = lv_label_create(lv_scr_act());
    lv_obj_align(labelFloor, LV_ALIGN_LEFT_MID, 35 , -45);
    lv_obj_set_style_text_font(labelFloor, &dseg70, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(labelFloor, lv_color_white(), LV_STATE_DEFAULT);
    lv_label_set_text_fmt(labelFloor, "%02d", 23);
   }
```

Para usarmos a fonte devemos indicar ao LVGL que a fonte existe, para isso adicione a linha a seguir no topo (após os #include) do arquivo `main.c`:

```c
LV_FONT_DECLARE(dseg70);
```

Antes de continuar temos que editar o começo arquivo da fonte `dseg70`, incluindo o define a seguir:

```diff
+#define LV_LVGL_H_INCLUDE_SIMPLE
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
```

!!! example "Tarefa"
    1. Crie o novo label como indicado anteriormente
    1. Modifique o arquivo `dseg70.h`
    1. Declare a fonte nova no main.c: `LV_FONT_DECLARE(dseg70);`
    1. Teste na placa

    Resultado esperado:
    
    ![](imgs/label-floor.jpeg){width=300}

!!! progress
    Click para continuar....


!!! info
    Notem que nós criamos um label e então customizamos algumas propriedades dele. O jeito feito neste exemplo é diferente do que fizemos com o botão na qual criamos um estilo novo e aplicamos a ele. Vocês podem escolher qualquer um dos dois jeitos para modificar um objeto.


#### Demais labels

Agora vocês precisam criar os outros dois labels: Relógio e Temperatura configurada, para isso será necessário gerar outras duas fontes de tamanhos diferentes e criar os labels.

!!! example "Tarefa"
    1. Crie o label temperatura referência: `labelSetValue`
    1. Crie o label para o relógio: `labelClock`
    
    ==Para cada label você terá que converter uma nova fonte de tamanho diferente, consulte os passos anteriores.==
    
    Resultado esperado:
    
    ![](imgs/labels-all.jpeg){width=300}

!!! progress
    Click para continuar....

## Handlers

Até agora estávamos apenas criando a interface no LCD, agora precisamos adicionar inteligência a ela. Isso será feito pelos callbacks dos botões. Vamos focar apenas nos botões UP e DOWN que configuram a temperatura de referência (da direita).

Vamos implementar o código para o `up_handler`, callback do botão de aumento de temperatura.

!!! info 
    Eu dei o nome de `up_handler` você pode ter dado outro nome, precisa ficar atento a isso.
    
### up_handler

Existem várias maneiras de fazermos com que o handler altera o valor do label, eu sugiro o código a seguir:

```c
static void up_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    char *c;
    int temp;
    if(code == LV_EVENT_CLICKED) {
        c = lv_label_get_text(labelSetValue);
        temp = atoi(c);
        lv_label_set_text_fmt(labelSetValue, "%02d", temp + 1);
    }
}
```

!!! info
    A vantagem da implementação sugerida é que não precisamos de uma variável global para armazenar o valor da temperatura, nós recuperamos o valor lendo o que estava salvo no label e convertendo para inteiro.
    
!!! example "Tarefa"
    1. Implemente o handler
    1. Teste na placa
       - Aperte o botão de up e verifique se a referência muda.
    
    !!! warning
        A fonte utilizada tem um problema, o carácter vazio (espaço: ` `) não apaga 100% o último valor, por exemplo: Quando o digito muda de 2 para 1 acontece de ficar uma barra em baixo.
        
        Depois vemos como resolver isso! Eu ainda não sei como fazer. =/

!!! progress
    Click para continuar....

### down_handler

Agora implemente a ação do botão down.

!!! example "Tarefa"
    1. Implemente o `down_handler`
    1. Teste na placa

### relógio 

Temos um relógio na interface, vamos fazer ele funcionar? Para isso terão que incluir o RTC no projeto e fazer uso dele.

!!! example "Tarefa"
    Inclua o RTC no projeto e faça o relógio funcionar!
    
    O relǵio deve exibir HH:MM, o **:** deve piscar uma vez por segundo.
    
    Dicas:
    
    1. Incluir RTC
    1. Criar task dedicada para atualizar o RTC
    1. Inicializar RTC na task
    1. Task fica esperando semáforo do tick de segundos e atualiza o label do relógio.

!!! progress
    ==Até aqui é C!==

## Extras

Temos muito o que fazer na interface, vou sugerir algumas coisas que irão dar nota a mais para vocês neste lab, ==cada item é meio conceito a mais.==

- [ ] Implementar o digito da Temperatura: 23 **.4**
     - Dica: use uma das fontes menores para isso
- [ ] O botão de `settings` deve possibilitar o usuário configurar a hora certa (usando as setas v e ^).
- [ ] Incluir demais labels e logos
- [ ] Gerar um logo para o relógio e usar no lugar do de `settings`
- [ ] Implementar o botão de `Power` que desliga a tela
- [ ] Colocar um potenciômetro que altera o valor da temperatura atual.

!!! note "Preencher ao finalizar o lab"
   <iframe src="https://docs.google.com/forms/d/e/1FAIpQLSepoeGumLbNxyigluS1JLWLbjhCEc_b53huFl3HzdAXE_J58A/viewform?embedded=true" width="640" height="320" frameborder="0" marginheight="0" marginwidth="0">Carregando…</iframe>

