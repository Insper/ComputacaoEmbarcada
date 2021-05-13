# APS 1 - Musical - Entregáveis

Entregáveis da APS 1 musical. Leia as regras:

!!! info "Regras"
    - Cada issue deve ser fechado com um `commit` e referenciado no issue. 
    - Todos do grupo devem participar (realizar commit, fechar issues) 
        - Iremos dar nota com base nessas evidências.
    - Somente Professores podem fechar os issues

## Entrega 1

Entregas referentes a configuração do hardware.

### Pino Buzzer

Definir e configurar pino que será usado para conectar o buzzer.

- [ ] Atualizar `README.md` com definição.
- [ ] Inserir `#defines` no  `main.c` com valores certos
```c
   #define BUZZER_PIO          
   #define BUZZER_PIO_ID       
   #define BUZZER_PIO_IDX      
   #define BUZZER_PIO_IDX_MASK 
```
- [ ] Atualizar função  `init()` configurando o pino do buzzer como output

### Pino botão start/pause

Definir e configurar pino que será usado para conectar o botão de start/pause.

- [ ] Atualizar `README.md` com definição.
- [ ] Inserir `#defines` no  `main.c` com valores certos
```c
   #define START_PIO          
   #define START_PIO_ID       
   #define START_PIO_IDX      
   #define START_PIO_IDX_MASK 
```
- [ ] Atualizar função  `init()` configurando o pino do botão como input


### Pino botão seleção musical

Definir e configurar pino que será usado para conectar o botão de seleção musical.

- [ ] Atualizar `README.md` com definição.
- [ ] Inserir `#defines` no  `main.c` com valores certos
```c
   #define SELECAO_PIO          
   #define SELECAO_PIO_ID       
   #define SELECAO_PIO_IDX      
   #define SELECAO_PIO_IDX_MASK 
```
- [ ] Atualizar função  `init()` configurando o pino do botão como input

### buzzer_test(int freq)

Crie uma função (`buzzer_test(int freq)`) que gera no pino do buzzer
uma onda quadrada de frequência definida, para isso você deve usar:

- `pio_set()`
- `pio_clear()`
- `delay_ns()`

> freq é definido em Hz.

## Entrega 2
