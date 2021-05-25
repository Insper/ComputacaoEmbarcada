# LVGL

Dicas sobre o LVGL.

!!! tip ""
    - https://docs.lvgl.io/latest/en/html/widgets/index.html
  
## Configurações gerais

### Cores principais do tema

- fonte
- cor

### Orientação do LCD (landscape/ portrait)

- TODO

## Lista de Widgets

| Widget               | Example                                 |
| ------               | -------                                 |
| Button (`lv_btn`)    | ![](imgs/lvgl/lv_button.png){width=100} |
| LED (`lv_led`)       | ![](imgs/lvgl/lv_leds.png){width=100}   |
| Roller (`lv_roller`) | ![](imgs/lvgl/lv_roller.png){width=100} |
| Bar (`lv_bar`)       | ![](imgs/lvgl/lv_bar.png){width=100}    |

## Modificações no tema de um widget específico

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

## Extras

### Como importar uma imagem do seu computador?

Usar o conversor online disponível em https://lvgl.io/tools/imageconverter

1. Deixar True Color e C Array
1. Copiar o arquivo .c gerado para o projeto e incluir. 
1. Abrir o arquivo .c, remover o include do topo (que tem um #ifdef) e deixar apenas ```#include "lvgl.h"```
1. Criar um arquivo .h com mesmo nome do .c
1. 1. Colocar no topo do .h,  ```#include "lvgl.h"```  e depois a linha da estrutura ```const lv_img_dsc_t imagem_nome```;
1. Abrir o arquivo .c e copiar o nome da estrutura que está final do .c. (exemplo: ```const lv_img_dsc_t imagem_nome;```)
1. No main.c, incluir o .h da imagem. Usar exemplo do site do lvgl como usar:

```c
  lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img1, &imagem_nome);
  lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, -20);
```
