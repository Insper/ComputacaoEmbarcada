# SAME70-XPLD - Erros

Aqui estão listados os erros mais frequentes na utilização da placa SAME70-XPLD.

1. USB errada
1. Chip errado (rev A/ rev B)
1. Jump Erase
1. Como resetar o uC

![](imgs/same70-xpld_erros/ATSAME70XPLD_SPL.jpg)


## 1) USB ERRADA

### - Debug USB

Interface USB utilizada para transferir o programa, e também para realizar o Debug via EDBG.

![](imgs/same70-xpld_erros/9_editada.jpg)

### - Target USB

Interface USB de alta velocidade (USB high speed interface).

**OBS:** Essa interface USB não realizar a gravação do chip, serve para o uC se comportar como um dispositivo USB.

![](imgs/same70-xpld_erros/12_editada.jpg)

## 2) CHIP ERRADO

As placas SAME70-XPLD possuem o Microcontrolador ATSAME70Q21, contudo ele possui 2 versões, a ATSAME70Q21 (Rev. A) e a versão ATSAME70Q21**B** (Rev. B). Caso a versão não esteja correta na IDE Atmel Studio, o código a ser transferido para a placa pode não ser gravado corretamente e pode até nem ser reconhecida pela IDE.

### - Identificando a versão de sua placa SAME70-XPLD

Basta olhar o código impresso em cima do CI do Microcontrolador:

| REV. A                                                 | REV B                                       |
| :----------------------------------------------------: | :-----------------------------------------: |
| ![0 (Editada)](imgs/same70-xpld_erros/0 (Editada).jpg) | ![](imgs/same70-xpld_erros/2 (Editada).jpg) |

!!! tip
    É bem difícil ver essas letras...

### - Alterando a versão na IDE Atmel Studio

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

## 3) JUMPER ERASE

### - Jumper se conectado não grava o programa

![14 (Editada)_2](imgs/same70-xpld_erros/14 (Editada)_2.jpg)

Esse jumper (J200 - Chip Erase Header) quando conectado apaga o conteúdo da memória flash do chip (programa). Ele deve ficar conectado somente para essa finalidade, caso o jumper esteja conectado e tente-se transferir o programa para a placa, o mesmo não será gravado:

> ![chipErase](imgs/same70-xpld_erros/chipErase.PNG)



### - Apagando a memória de programa (FLASH)

Em algumas situações é necessário que a memória seja apagada(zerada) fisicamente, para isso, 4 passos simples são executados:

![jumper_erase](imgs/same70-xpld_erros/jumper_erase.gif)

1. Coloque o Jumper
1. Retire o cabo USB
1. Coloque o cabo USB
1. Retire o jumper
1. Retire e coloque o cabo USB novamente



## 4) Build > Clean Solution 

Remove todos os arquivos da compilação anterior das pastas **bin** e **obj**.

![image-20200330153918599](imgs/same70-xpld_erros/build_clean_solution.png)



------

Marco Mello

30/03/2020

Computação Embarcada - 5s

