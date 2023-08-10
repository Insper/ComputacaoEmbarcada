# Regras

!!! tip "Rule 1.0"
    O código não deve possuir erros detectados pelo `cppcheck`.
    
<<<<<<< HEAD
**Justificativa: Remover erros detectados pelo analisador estático facilita a depuração e faz com o que projeto funcione mais rapidamente.**
=======
    **Racional: Removendo erros detectado pelo analisador estático facilita a depuração e faz com o que projeto funcione mais rapidamente.**
>>>>>>> 726aca14f933d9946816f24bf1616220f5fa708a

!!! tip "Rule 1.1"
    Somente usar variáveis globais para passar informações de uma interrupção (ISR) para a função `main`. 

<<<<<<< HEAD
**Justificativa: Esta regra evita o uso de variáveis globais quando poderiam ser locais.**
=======
    **Racional: Está regra evita que você use variáveis globais onde elas poderiam ser locais.**
>>>>>>> 726aca14f933d9946816f24bf1616220f5fa708a

!!! tip "Rule 1.2"
    Todas as variáveis globais acessadas de uma interrupção (ISR) devem possuir a keyword: `volatile`

<<<<<<< HEAD
**Justificativa: A keyword `volatile` instrui o compilador a não otimizar a variável em questão, que está sendo modificada por um evento gerado pelo hardware e que o compilador não tem conhecimento.**
=======
    **Racional: O volatile indica para o compilador não otimizar a variável em questão que está sendo modificada por um evento gerado pelo hardware e que o compilador não tem conhecimento.**
>>>>>>> 726aca14f933d9946816f24bf1616220f5fa708a

!!! tip "Rule 1.3"
    Somente as variáveis globais e modificadas durante a ISR devem ser globais.
    
<<<<<<< HEAD
**Justificativa: Devemos deixar o compilador fazer o papel dele e otimizar as variáveis que devem ser otimizadas.**
=======
    **Racional: Devemos deixar o compilador fazer o papel dele e otimizar as variáveis que devem ser otimizadas.**
    
!!! note "Rule 2.0" 
    Todo *head file* (`.h`) deve ser criado com include guard.
    
!!! note "Rule 2.1"
    Não ter implementação de código em *head file* (`.h`).
>>>>>>> 726aca14f933d9946816f24bf1616220f5fa708a

!!! info "RULE 3.0"
    Não pode usar / gerar `delay` de software dentro de uma ISR.

!!! info "RULE 3.1"
    Não pode acessar o OLED ou qualquer outro display de dentro de uma ISR.
   
!!! info "RULE 3.2"
    Não pode usar `printf` ou `sprintf` de dentro de uma ISR.
    
!!! info "RULE 3.3"
    Não pode executar laços de código (`while`, `for`) de dentro de uma ISR.
    
<<<<<<< HEAD
**Justificativa: A ideia é que a ISR seja a mais simples e rápida possível, esse conjunto de regras evita o básico de tornar um código de ISR complexo e lento.**
=======
    **Racional: A ideia é que a ISR seja a mais simples e rápida possível, esse conjunto de regras evita o básico de tornar um código de ISR complexo e lento.**
>>>>>>> 726aca14f933d9946816f24bf1616220f5fa708a
