# ISR - Variáveis

Devemos seguir algumas regras básicas quando desenvolvemos código que faz uso de interrupção, devemos tratar essa secção do programa como algo especial e que possui algumas regras básicas para operar corretamente. 

!!! info
    Para informações mais detalhadas consulte:
    
    - https://betterembsw.blogspot.com/search/label/interrupts 

!!! exercise
    Está atividade requer que você crie um repositório a partir do link a seguir:
    
    - {{rules_isr_classroom}}

!!! progress 
    Começar

## Variáveis volatile

!!! warning "Rule 1.1"
    Somente as variáveis globais e modificadas durante a ISR devem ser globais.
    
**Racional: Devemos deixar o compilador fazer o papel dele e otimizar as variáveis que devem ser otimizadas.**

!!! warning "Rule 1.2"
    Todas as variáveis globais acessadas de uma interrupção (ISR) devem possuir a keyword: `volatile`
    
**Racional: O `volatile` indica para o compilador não otimizar a variável em questão que está sendo modificada por um evento gerado pelo hardware e que o compilador não tem conhecimento.**

Essas regras pode ser flexibilizada quando desejamos acessar periféricos e memórias externas, os valores desses endereços de memória são alterados sem o conhecimento do compilador.

### Exemplo

O exemplo a seguir demonstra um ==uso errado== da keyword `volatile`:

- `f_btn`: É uma variável global modificada pelo um evento no pino do botão, deveria ser `volatile`
- `cnt`: É apenas um contador não devemos interferir no processo de compilação.

```c

int f_btn = 0; // deveria ser volatile

// ISR
void btn_callback(void) {
    f_btn = 1; // variável alterada de uma interrupcão
}

void main(void) {
    
    volatile int cnt = 0; // não precisa ser volatile
    
    while (1) {
        if (f_btn) {
            cnt++;
            f_btn = 0;
        }
    }
}
```

!!! exercise "Variáveis `volatile`"
    Agora você deve corrigir o código anterior usando variáveis `volatiles` :
    
    - https://github.com/insper-classroom/emb-rules-variables/blob/main/rules_basic_variable_isr.c
