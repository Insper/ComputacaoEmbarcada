## LAB

Agora vamos começar mexer com o LVGL e criar nossa interface. A ideia é recriar uma interface de um termostato inspirado no produto a seguir:

!!! info ""
     KKmoon LCD Touch Screen Termostato Sistema de Aquecimento de Piso Elétrico Aquecimento de Água Termorregulador AC85-240 V Controlador de Temperatura Preto 
    
     - https://www.amazon.com.br/KKmoon-Aquecimento-Termorregulador-Controlador-Temperatura/dp/B07X3CDM83

![](https://images-na.ssl-images-amazon.com/images/I/51iNUfjxJDL._AC_SL1000_.jpg){width=500}

### Etapas

Quando começamos projetar uma [interface homem máquina (IHM)](https://en.wikipedia.org/wiki/Human%E2%80%93computer_interaction) é necessário analisarmos várias frentes:

- Usabilidade
- Acessibilidade
- Branding
- Implementação

A usabilidade irá indicar como as funções do produto estarão disponíveis e serão exibidas aos usuários, isso deve estar atrelada aos conceitos da marca do produto. O público alvo deve ser analisado e o produto deve ser acessível, para isso, muitos testes de usabilidade devem ser feitos para validar o conceito.

Muitas vezes o protótipo da interface esbarra em problemas técnicos e de implementação, muitas imagens e fontes impactam no tamanho total do firmware que pode impossibilitar a implementação da interface proposta, ou necessitar a adição de formas alternativas de armazenamento de dados. Microcontroladores de forma geral não possuem GPU (alguns sim, exemplo: [STM32MP157](https://www.st.com/en/microcontrollers-microprocessors/stm32mp157.html) ) e isso impacta na performance da interface e muito provavelmente no gasto energético.

### Identificando widgets

Neste laboratório iremos trabalhar apenas com a parte de implementação de uma interface, como visto anteriormente o LVGL possui muitos widgets o primeiro passo é identificarmos no protótipo da interface com widgets iremos usar para recriar a funcionalidade especificada.


!!! question choice
    Text of the question. 

    - [ ] option 1
    - [ ] option 2
    - [X] correct option


    !!! details
        Text explaining correct answer. Only shown after option is selected.

