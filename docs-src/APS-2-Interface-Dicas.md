# Interface dicas

Você está perdido e não sabe como começar a APS? Vou tentar dar algumas dicas e passos aqui para facilitar sua vida. 

1. Encontre um parceiro para a APS e crie um repositório git
1. Estude os cenários e a rubrica
1. Prototipe uma interface no papel 
    - Com tamanho dos botões, icones e tudo mais! Vai facilitar muitooo o desenvolvimento.
1. Estude os exemplos  do LCD fornecidos na ordem apresentanda a seguir (**estudar = entender e modificar o código**) 

!!! note
    Sugerimos cada um do grupo estudar um exemplo!!

`SAME70-examples/Screens/`:

- [`LCD-maXTouch-Images`](https://github.com/Insper/SAME70-examples/tree/master/Screens/LCD-maXTouch-Images): Exemplo de como colocar uma imagem no LCD
    - **FAÇA: baixe um ICONE da web, converta para o `.h` e exiba no LCD**
- [`LCD-maxTouch-Switch-Toggle`](https://github.com/Insper/SAME70-examples/tree/master/Screens/LCD-maxTouch-Switch-Toggle): Exemplo de como fazer a leitura do touch screen do LCD
    - **FAÇA: implemente um terceiro botão que faz o LED da placa piscar**
- [`LCD-maXTouch-New-Fonts`](https://github.com/Insper/SAME70-examples/tree/master/Screens/LCD-maXTouch-New-Fonts): Mostra como usar novas fontes no LCD (gerar e inserir no código)
    - **FAÇA: Escolha uma fonte nova e insira nesse exemplo**

## Começando a trabalhar na entrega (protótipo)

1. Copie a pasta do `LCD-maxTouch-Switch-Toggle` para o repositório da APS
    - Ele servirá como base do desenvolvimento
1. Converta um dos icones para `.h` (documentando em `LCD-maXTouch-Images`) 
    - Desenhe o icone na tela do LCD (Vai dar uma motivada!, use o exemplo
      `LCD-maXTouch-Images`)
1. Escolha uma das fontes da sua interface
    - Faça a conversão para ser usada no
   sistema embarcado (tutorial `LCD-maXTouch-New-Fonts`) e a utilize na tela.
1. Converta todos os outros icones para `.h`
    - Duas são as soluções: Um `.h` por icone (resultando em N `.h`) ou Um `.h` para todos os icones (resultando em 1 `.h`) .
1. Comece por desenhar a interface padrão 
    - Pegue um dos [ciclos de lavagem](https://github.com/Insper/ComputacaoEmbarcada/blob/master/APS-2/maquina1.h#L18) como referência.
    - Apenas desenhando Icones e Textos (sem botão/ touch)
1. Insira aos poucos os botões na interface
    - Se não estruturar o código direito vai dar muitoooo trabalho
1. Vá inserindo as funcionalidades, precisa lembra de usar a `struct t_ciclo` fornecida pela engenharia.



