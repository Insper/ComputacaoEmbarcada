# IRS - Handler/ Callback 

Esses conjuntos de regra dizem respeito a que a execução de uma ISR deve ser a mais rápida possível e curta em tamanho de código. 

!!! info "RULE 2.0"
    Não pode usar / gerar `delay` de software dentro de uma ISR.

!!! info "RULE 2.1"
    Não pode acessar o OLED ou qualquer outro display de dentro de uma ISR.
   
!!! info "RULE 2.2"
    Não pode usar `printf` ou `sprintf` de dentro de uma ISR 
    
!!! info "RULE 2.3"
    Não pode executar laços de código (`while`, `for`) de dentro de uma ISR 

Pode ser flexibilizada se mitigado o impacto do uso desses recursos dentro de uma ISR, as vezes por exemplo queremos modificar um vetor pequeno para armazenar mais um valor nele, então poderíamos usar um laço, mas de forma geral iremos evitar isso.

!!! info
    Alguns microcontroladores possuem tamanho de memória de código limitado para interrupção, fique atento a isso quando for desenvolver um firmware para uC mais simples (os do tipo 8/16 bits)!
    
    Alguns desenvolvedores de software usam o principio de: *Keep it simple, stupid!* [**KISS**](https://en.wikipedia.org/wiki/KISS_principle) nos seus projetos, isso tem alguma semelhança com o que estamos propondo aqui.

### Example

A seguir um exemplo ==errado== de uso de interrupção.

```c
#include "asf.h"

int g_cnt = 0;
char g_str[10];

// This code creates a progress bar on an OLED screen that
// increases when the button is pressed.
void btn_callback(void) {
  printf("btn pressed \n"); // printf dentro de ISR

  if (g_cnt >= 8)
    g_cnt = 0;

  int i = 0;
  for (i = 0; i < g_cnt; i++) { // for dentro de ISR
    g_str[i] = '*';
    g_str[i + 1] = NULLL;
    delay_ms(50); // delay dentro de ISR
    gfx_mono_draw_string(g_str, 0, 0, &sysfont); // oled dentro de ISR
  }
}

void main(void) {
  // ...

  while (1) {
  }
}
```

!!! exercise "Simple and short"
    Agora você deve corrigir o código anterior usando corretamente ISR:
    
    - https://github.com/insper-classroom/emb-rules-variables/blob/main/rules_basic_isr.c 
    
    Dica: Crie uma `flag` para indicando que o btn foi pressionado e então reescreva o código na função `main`.
