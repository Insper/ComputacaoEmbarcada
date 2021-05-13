# LVGL

Dicas sobre o LVGL.

!!! tip ""
    - https://docs.lvgl.io/latest/en/html/widgets/index.html

## Orientação



## Cor do tema




## Widgets

| Widget               | Example                                 |
| ------               | -------                                 |
| Button (`lv_btn`)    | ![](imgs/lvgl/lv_button.png){width=100} |
| LED (`lv_led`)       | ![](imgs/lvgl/lv_leds.png){width=100}   |
| Roller (`lv_roller`) | ![](imgs/lvgl/lv_roller.png){width=100} |
| Bar (`lv_bar`)       | ![](imgs/lvgl/lv_bar.png){width=100}    |


## Como importar uma imagem do seu computador?

- Usar o conversor online disponível em https://lvgl.io/tools/imageconverter
- Deixar True Color e C Array
- Copiar o arquivo .c gerado para o projeto e incluir. 
- Abrir o arquivo .c, remover o include do topo (que tem um #ifdef) e deixar apenas ```#include "lvgl.h"```
- Criar um arquivo .h com mesmo nome do .c
- Abrir o arquivo .c e copiar o nome da estrutura que está final do .c. (exemplo: ```const lv_img_dsc_t imagem_nome;```)
- Colocar no topo do .h,  ```#include "lvgl.h"```  e depois a linha da estrutura ```const lv_img_dsc_t imagem_nome```;
- No main.c, incluir o .h da imagem. Usar exemplo do site do lvgl como usar
```c
  lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img1, &imagem_nome);
  lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, -20);
```