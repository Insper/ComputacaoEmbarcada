# LVGL

Dicas sobre o LVGL.

!!! tip ""
    - https://docs.lvgl.io/latest/en/html/widgets/index.html

## Orientação do LCD (landscape/ portrait)

Para alteramos a orientação do LCD de horizontal para vertical será necessário fazermos as seguintes mudanças no código do `main.c`:

=== "defines"
    ```diff
    /*************************************************/
    /* LCD / LVGL                                    */
    /*************************************************/
    
    - #define LV_HOR_RES_MAX          (320)
    - #define LV_VER_RES_MAX          (240)
    + #define LV_HOR_RES_MAX          (240)
    + #define LV_VER_RES_MAX          (320)
    ```
=== "Leitura do Touch"
    ```diff
    void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data) {
      ...
      ...
    -   data->point.y = px;
    +   data->point.x = 320 - py;
    }
    ```
=== "Driver do LCD"
    ```diff
    int main(void) {
      ....
      ....
    
      /* LCd, touch and lvgl init*/
      configure_lcd();
    + ili9341_set_orientation(ILI9341_FLIP_Y | ILI9341_SWITCH_XY);
    
      ...
    }
    ```

!!! tip
    Com isso o LCD passa a ter as dimensões `240x320` e para o LVGL não existe diferença nenhuma.

## Mudando a cor do fundo

Para mudarmos a cor do background basta alterarmos a cor do background da tela principal:

```c
    // configura um fundo vermelho.
    lv_obj_t * screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN );
```

!!! info "Cores"
    Para criar ou usar uma cor consulte:
    
    https://docs.lvgl.io/master/overview/color.html#palette   

## Multiplas telas

No LVGL podemos criar multiplas telas e associar ao mesmo display, as telas podem ser exibidas conforme necessário. Os widgets são associados a uma tela, então quando a tela em questão for exibida apenas os widgets associados a ela serão ativados. 

=== "Criando as telas:"
    ```c
    // declarar a tela como global e estática
    static lv_obj_t * scr1;  // screen 1
    static lv_obj_t * scr2;  // screen 2

    static void task_lcd(void *pvParameters) {
        // Criando duas telas
        scr1  = lv_obj_create(NULL);
        scr2  = lv_obj_create(NULL);

        // ....
    }
    ```

=== "Associando widgets"
    Para dizer em qual tela os widgets serão associados, basta substituir o `lv_scr_act()` usado na criação dos widgets pela tela em questão:

    ```diff
    - lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    + lv_obj_t * btn1 = lv_btn_create(scr1);          // botao criado na primeira tela
    ```
    
=== "Exibindo"
    Para exibir uma das telas use a função `lv_scr_load(lv_obj_t * scr)` como demonstrado a seguir:

    ```c
    static void task_update(void *pvParameters) {
        for (;;)  {
            lv_scr_load(scr1); // exibe tela 1
            vTaskDelay(500);
            lv_scr_load(scr2); // exibe tela 2
            vTaskDelay(500);
        }
    }
    ```

!!! tip
    Você pode modificar as funções que criam os widgets na tela para receber como parametro o screen associado a eles:

    ```diff
    - lv_ex_btn_1(void) {
    + void create_scr(lv_obj_t * screen) {
    -   lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    +   lv_obj_t * btn1 = lv_btn_create(screen);
        lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
        lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

        label = lv_label_create(btn1);
        lv_label_set_text(label, "Corsi");
        lv_obj_center(label);

    -   lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
    +   lv_obj_t * btn2 = lv_btn_create(screen);
        lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
        lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
        lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
        lv_obj_set_height(btn2, LV_SIZE_CONTENT);

        label = lv_label_create(btn2);
        lv_label_set_text(label, "Toggle");
        lv_obj_center(label);
    }

    tatic void task_lcd(void *pvParameters) {
        scr1  = lv_obj_create(NULL);
    -   lv_ex_btn_1();
    +   create_scr(scr1);
        lv_scr_load(scr1);
        
        ...
    }
    ```

!!! tip
    Você pode fazer a transição entre telas dado um evento de um botão!


!!! tip
    Se quiser usar scrol para mudar de tela tente o widget tile view, eu testei o exemplo do site aqui e funciona bem:

    <iframe width="560" height="315" src="https://www.youtube.com/embed/aSL4HxRbGjk" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

    https://docs.lvgl.io/master/widgets/extra/tileview.html#tileview-with-content

## Exibindo uma imagem

!!! warning
    Esse procedimento não funciona com imagens no formato PNG **sem fundo**, a imagem precisa ter fundo, mesmo que branco.
    
Exibindo uma imagem estática no LCD, sem interação.

!!! tip
    Se quiser usar uma imagem como botão utilize o widget `Image button`:
    
    - https://docs.lvgl.io/master/widgets/extra/imgbtn.html
    
Usar o conversor online disponível em https://lvgl.io/tools/imageconverter e seguir os passos:

- No site configurar: 
    - `File names`: Nome que quer dar para imagem, exemplo: `img1`
    - `True Color`: ==On==
    - `Output Format`: ==C Array==
    
!!! info ""
    Clicar em `Convert` e salvar o arquivo no computador (fora da pasta do projeto);
 
- Mudar a extensão do arquivo baixo de `.c` para `.h`

- Abrir o arquivo e editar a primeira linha:

```diff
- #include "lvgl/lvgl.h"
+ #include "lvgl.h"
```

- Adicionar o arquivo da imagem no projeto do MicrochipStudio (pode arrastar)

- No `main.c` incluir o `.h` da imagem. 

```
#include "img1.h"
```

- Agora basta executar as linhas de código a seguir para exibir a imagem:

```c
lv_obj_t * img = lv_img_create(lv_scr_act());
lv_img_set_src(img, &img1);
lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
```

!!! info
    - Para testar, incluir as linhas na `task_lcd`
    - No exemplo o nome da imagem utilizada no site foi `img1`
    - Alinhamos a imagem no centro da tela

<!--
## Modificações no tema de um widget específico

!!! warning
    Ainda não atualizado para a versao do LVGL que estamos usando.

- Controlar raio objeto (ex: botao quadrado):

`lv_obj_set_style_local_radius(btn1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);`

- Mudar cor de fundo (ex: background do lcd):

`lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);`

Talvez seja necessário mudar a transparência (ex: label):

```
lv_obj_set_style_local_bg_color(label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_YELLOW);
v_obj_set_style_local_bg_opa(label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_100);
```

- Mudar tamanho da fonte (ex: label):

`lv_obj_set_style_local_text_font(label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &dseg70);`

- Mudar cor da fonte (ex: label):

 `lv_obj_set_style_local_text_color(label1, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_YELLOW);`
 -->
