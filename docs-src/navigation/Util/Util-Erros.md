# Erros comum

Aqui estão listados os erros mais frequentes que aparecem na hora de programar a placa SAME70-XPLD.

## USB errada

Muitas das vezes que o AtmelStudio não reconhece a placa é porque foi ligada na
porta USB errada. O Kit de desenvolvimento possui duas portas USB, uma para programar
o microcontrolador e outra para conectar dispositivos no microcontrolador (host/device).

==Este é o erro mais comum!==

!!! success "PORTA USB CERTA"
      ![](imgs/same70-xpld_erros/9_editada.jpg)

!!! error "PORTA USB ERRADA"
      ![](imgs/same70-xpld_erros/12_editada.jpg)

## Chip Errado

??? example "Configurando versão"
      Para alterar a versão do chip dentro do Atmel Studio basta realizar os seguintes passos:

      ![FAQ_ATSAME70xpld](imgs/same70-xpld_erros/FAQ_ATSAME70xpld.gif)

      1 - Clique no botão Device:

      ![device](imgs/same70-xpld_erros/device.PNG)

      2 - Clique no botão Change Device:

      ![ChangeDevice](imgs/same70-xpld_erros/ChangeDevice.PNG)

      3 - Selecione a versão correta do chip e clique em OK, agora seu gravador(EDBG) deverá ser reconhecido pela IDE:

      ![selection](imgs/same70-xpld_erros/selection.PNG)

      4 - Dentro da aba Tools, vá até o menu drop-down **Select debugger/programmer** e selecione o seu gravador, no caso desse gif:

      ![SelectDebugger](imgs/same70-xpld_erros/SelectDebugger.PNG)

As placas SAME70-XPLD possuem o Microcontrolador ATSAME70Q21, contudo ele possui 2 versões, a ATSAME70Q21 (Rev. A) e a versão ATSAME70Q21**B** (Rev. B). Caso a versão não esteja correta na IDE Atmel Studio, o código a ser transferido para a placa pode não ser gravado corretamente e pode até nem ser reconhecida pela IDE.

Os exemplos são todos configurados para a versão B da placa, se você possuir a A deve 
fazer a configuração a seguir.

Para saber a versão do seu chip, basta olhar o código impresso em cima do CI do Microcontrolador:

| REV. A                                                 | REV B                                       |
| :----------------------------------------------------: | :-----------------------------------------: |
| ![0 (Editada)](imgs/same70-xpld_erros/0 (Editada).jpg) | ![](imgs/same70-xpld_erros/2 (Editada).jpg) |

!!! info
    É bem difícil ver essas letras.

## Jumpers

??? example "Erase"

      Em algumas situações é necessário que a memória seja apagada (zerada), para isso siga os passos a seguir:

      1. Energize a placa
      1. Coloque o Jumper 
      1. Retire o cabo USB
      1. Coloque o cabo USB
      1. Retire o jumper
      1. Retire e coloque o cabo USB novamente

      ![jumper_erase](imgs/same70-xpld_erros/jumper_erase.gif)

O Kit possui dois jumpers: `Current Measurement` e `Erase`. O primeiro deve estar conectado e o segundo não.

- Current Measurement: Serve para medirmos a corrente que vai para o uC a fim de aferir a potência elétrica que está sendo consumida.

- Erase: Serve para apagar a memória de programa do uC.


## Limpando build

Dentro do AtmelStudio clique no menubar: `Build` :arrow_right: `Clean Solution`. Isso irá remover todos os arquivos da compilação anterior das pastas.

![image-20200330153918599](imgs/same70-xpld_erros/build_clean_solution.png)

## Instalando Terminal Window no Microchip Studio

??? example "Instalando"
      1. Clique em `Tools` :arrow_right: `Extensions and Update`

         ![Terminal_2](imgs/same70-xpld_erros/Terminal_2.png)

      2. Pesquise **Terminal** na caixa de busca a direita, depois clique em download.

         ![Terminal_3](imgs/same70-xpld_erros/Terminal_3.png)

      3. Após a instalação o Atmel Studio deverá reiniciar.

         ![Terminal_4](imgs/same70-xpld_erros/Terminal_4.png)

      4. Para verificar se o Terminal Windows foi instalado, clique em View > Terminal Window 

         ![Terminal_5](imgs/same70-xpld_erros/Terminal_5.png)

Caso não encontre o terminal em `View` :arrow_right: `Terminal Window` (Imagem abaixo), você deve seguir os passos para instalação do mesmo.

![](imgs/same70-xpld_erros/Terminal_5.png)


## Driver EDBG (USB) não está sendo reconhecido

??? example "Downgrade do driver EDBG"

      Faça o download do software [Zadig](https://zadig.akeo.ie/):

      - [Versão 2.5](https://github-production-release-asset-2e65be.s3.amazonaws.com/4975854/3043b700-726c-11ea-8a31-cd87633d48df?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20200828%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20200828T201855Z&X-Amz-Expires=300&X-Amz-Signature=30b0f6a83ad62a9b7fc19e9d9b5237bc90eeda5c915007b4e69c910a6fc9b4e5&X-Amz-SignedHeaders=host&actor_id=40698780&key_id=0&repo_id=4975854&response-content-disposition=attachment%3B%20filename%3Dzadig-2.5.exe&response-content-type=application%2Foctet-stream)

      1. Com a placa conectada, execute o software e selecione **Options > List All Devices**, feito isso selecione a opção **EDBG Data Gateway ** e em seguida clique em **Downgrade Driver**:

      ![7_3](imgs/same70-xpld_erros/7_3.png)

      2. O driver deverá ser reconhecido pelo Atmel Studio, conforme a imagem abaixo:

      ![7_4](imgs/same70-xpld_erros/7_4.png)


Abra qualquer um dos projetos da disciplina **Computação Embarcada** e conecte a placa, confira se o chip configurado na interface é o mesmo que você está utilizando, senão volte a sessão 2:

![7_1](imgs/same70-xpld_erros/7_1.png)

Caso o driver EDGB (gravador) não tenha sido reconhecido (imagem abaixo) será necessário fazer o **Downgrade** do driver EDBG:

![7_2](imgs/same70-xpld_erros/7_2.png)

