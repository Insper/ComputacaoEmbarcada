Diagrama
===========

Com o intuito de clarificar o entendimento da interrupção e dos periféricos recentemente vistos (TC e RTC), faça um diagrama de blocos que contenha toda a informação necessária para o entedimento da entrega `Tick Tack`. Esse diagrama deve conter ao menos os seguintes itens:

- Periféricos utilizados
- Interface dos periféricos com o CORE
- Pinos utilizados e como estão conectados nos periféricos
    - Numerar os pinos de cada LED (ex. PA8, PB12, ...).
- Deve ficar claro o que é :
    - uC
    - Kit de desenvolvimento
    - Módulo OLED1
- Deve-se ilustra as interfaces de interrupção entre os periféricos e o *Core*
    - Informar os valores (ID_TC0, ID_TC1) de cada interrupção 

Pesquisa
===========

(mínimo dois itens da lista)

1. Explique o funcionamento interno de um RTC. (como ele conta os dias/meses e anos ? gastando pouca energia).

2. Explique como o LINUX controla e acessa o RTC do computador (https://www.kernel.org/doc/Documentation/rtc.txt) (http://lxr.free-electrons.com/source/drivers/char/rtc.c)

3. Como o TimerCounter pode ser utilizado para medir a velocidade e posição de um motor usando um encoder ótico?

4. Qual o consumo de energia do RTC no SAME70 ? 

Avaliação
=========

Estaremos trabalhando nessa etapa os seguintes itens dos objetivos de aprendizagem :

- Entende a relação entre o uC e o mundo externo, mas não consegue transpor essa relação para um código.
- Lista os pontos de execução da aplicação relacionando HW e SW.
- Correlaciona os diferentes tipos de documentos e faz uso constante da documentação.
- Correlaciona a informação encontrada com outros materiais extraindo e sintetiza as informações para uso futuro.
- Sintetiza as informações em um documento externo ao código.
