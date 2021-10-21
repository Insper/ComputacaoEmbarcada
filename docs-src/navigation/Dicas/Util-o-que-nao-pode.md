# ⚡ Regras de firmware

Regras de desenvolvimento de firmware para entregas de laboratórios, aps, projetos e avaliações. 

Notem que são regras gerais e podem existir exceções, mas você deve pensar bem e talvez discutir com algum membro da equipe antes de querer quebrar alguma delas.

## Linguagem C

!!! warning ""
    Com grandes poderes vem grandes responsabilidades

- Usar variáveis globais apenas quando estritamente necessárias, como regra de ouro só é necessário aquelas que são modificadas de dentro de uma interrupção. 
- Se uma função for alterar uma variável global, você deve passar o ponteiro da variável como argumento da função.
- Sempre que possível deixe o código genérico e sem [`magic numbers`](https://en.wikipedia.org/wiki/Magic_number_(programming)), utilize `#define` ou `const`.
- Usar `inline` no lugar de `macros`
- Não implementar funções dentro do `.h`, fazer no `.c`.

## Interrupção / Callback

!!! warning ""
    Você deve gastar no máximo algo entre 100-200 clocks dentro de uma interrupção.

- Apenas algumas linhas de código em C
- Evitar manipular strings (`sprintf`)
- Evitar usar `printf`
- Não atualizar displays (OLED/ LCD)
- Evite loops (`while` / `for`)

!!! info ""
    A interrupção é um evento de hardware na qual o compilador não tem conhecimento.

- Lembre de dar o **ACK** da interrupção (exe: `tc_get_status`)
- Declare as variáveis compartilhadas (globais) como `volatile`
- No ARM para ativar interrupção é necessário configurar o periférico e o NVIC!

## freeRTOS

!!! warning ""
    Usar os recursos do sistema operacional sempre!

- De forma geral usar `vTaskDelay` no lugar de `delay_ms`.
- Não fazer uso de flags (variáveis globais) para indicar que um evento deve acontecer, usar um semáforo
- Não compartilhar variáveis globais entre tasks para transmitir informações, usar uma fila para isso
- Lembre de inicializar os recursos antes de usar (`xCreateSemaphore`, `xCreateQueue`). Indicamos fazer isso na função `main` e não dentro das tarefas 

## Fontes

- https://betterembsw.blogspot.com/2013/03/rules-for-using-interrupts.html
