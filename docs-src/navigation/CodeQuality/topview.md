# ⚡ Visão geral

Regras de desenvolvimento de firmware para entregas de laboratórios, APS, projetos e avaliações. É importante ressaltar que estas são regras gerais e podem existir exceções, mas você deve pensar bem e talvez discutir com algum membro da equipe antes de querer quebrar alguma delas.

## Linguagem C

!!! warning ""
	```
    _"With great power comes great responsibility"_
										Ben, Uncle.
	```


- Usar variáveis globais apenas quando estritamente necessárias, como `"regra de ouro"`, só é necessário aquelas que são modificadas de dentro de uma interrupção. Pois as variáveis globais podem ser alteradas em qualquer lugar do código, tornando-o menos previsível.
- Se uma função for alterar uma variável global, você deve passar o ponteiro da variável como argumento da função.
- Sempre que possível deixe o código genérico e sem [`magic numbers`](https://en.wikipedia.org/wiki/Magic_number_(programming)), utilize `#define` ou `const`.
- Não implementar funções dentro do `.h`, faça isso no `.c`.

## Interrupção / Callback

!!! warning ""
    Você deve gastar no máximo algo entre 100-200 clocks dentro de uma interrupção.

- Apenas algumas linhas de código em C
- Evitar manipular strings (`sprintf`)
- Evitar usar `printf`
- Não atualizar displays (OLED / LCD)
- Evite loops (`while` / `for`)

!!! info ""
    A interrupção é um evento de hardware na qual o compilador não tem conhecimento.

- Lembre de dar o **ACK** da interrupção (exe: `tc_get_status`)
- Declare as variáveis compartilhadas ( entre interrupções e a main(); ) como [`volatile`](https://www.embedded.com/introduction-to-the-volatile-keyword/)
- No ARM para ativar interrupção é necessário configurar o periférico e o NVIC!

## freeRTOS

!!! warning ""
    Usar os recursos do sistema operacional sempre!

- De forma geral usar `vTaskDelay` no lugar de `delay_ms`.
- Não fazer uso de flags (variáveis globais) para indicar que um evento deve acontecer, usar um semáforo.
- Não compartilhar variáveis globais entre tasks para transmitir informações, usar uma fila para isso.
- Lembre de inicializar os recursos antes de usar (`xCreateSemaphore`, `xCreateQueue`). Indicamos fazer isso no início da função `main` e não dentro das tarefas 

## Fontes

- https://betterembsw.blogspot.com/2013/03/rules-for-using-interrupts.html
