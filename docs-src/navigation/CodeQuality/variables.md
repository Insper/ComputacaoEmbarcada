# Variáveis

Programas para sistemas embarcados devem seguir algumas diretrizes fundamentais de qualidade de código, as quais refletem as melhores práticas no uso de microcontroladores e da linguagem de programação C. É importante lembrar que um sistema embarcado interage diretamente com o mundo real, onde falhas podem impactar significativamente nossa realidade.

Diversas normas foram criadas a fim de ajudar os desenvolvedores a criar firmwares com menos falhas, incluindo os problemas conhecidos com a especificação da linguagem C. 

!!! info "underfined behaviors - linguagem C"
    Os comportamentos indefinidos (undefined behaviors) na linguagem de programação C ocorrem quando o padrão da linguagem não especifica como o programa deve se comportar em determinadas situações. Isso pode ser resultado de ações como divisão por zero, acesso a ponteiros nulos, estouro de buffer, entre outros. Esses comportamentos podem levar a resultados imprevisíveis e causar problemas de segurança ou falhas no programa. Para minimizar tais riscos, é importante seguir as melhores práticas de programação e estar atento a possíveis comportamentos indefinidos ao escrever e revisar seu código.
    
Neste roteiro não vamos nos atentar a formatacão do código (nomenclatura, estilo). 

## Praticando

Vamos aprender e praticar as regras básicas de qualidade de código e boas práticas em sistemas embarcados, para isso crie um repositório pelo *github classroom* e então modifique os arquivos conforme indicado.

!!! exercise
    Acesse e crie um repositório a partir do link a seguir:
    
    - {{rules_variables_classroom}}

!!! progress 
    Comecar

## Variáveis Globais

!!! warning "Rule 1.1"
    Somente usar variáveis globais para passar informacoes de uma interrupcão (ISR) para a funcão `main`. 

Em projetos reais, essa regra pode ser flexibilizada, mas isso deve ser abordada com cautela e planejamento. Devido ao tempo limitado disponível para desenvolvermos boas práticas com vocês, estamos  o uso de variáveis globais apenas nessas situações. 

### Exemplo

O exemplo a seguir demonstra um ==uso errado== de variáveis globais:

- `void foo(void)`: A funcão `foo` acessa a variável global `a`
- `int b`: Poderia pertencer ao escopo da funcão `main`

```c
int a = 0; // var global
int b = 0; // var global

void foo(void) {
    a = a + 1; // acessa variavel global
}

void main(void) {
    while (1) {
        foo();
        
        if (a > 5) {
            b = 1;
        }
    }
}
```

!!! exercise "Variáveis globais"
    Agora você deve corrigir o código anterior para não usar variáveis globais:
  
    - https://github.com/insper-classroom/emb-rules-variables/blob/main/rules_basic_variable.c

    Dica: reescreva a funcão `foo` para um dos casos a seguir:
    
    1. `int foo(int a)`
    1. `void foo(int *a)`
