- Marco Mello

- 24/03/2020

- Computação Embarcada

# SAME70-XPLD - Erros de Utilização

Aqui estão listados os erros mais frequentes na utilização da placa SAME70-XPLD.

![ATSAME70XPLD_SPL](C:\Users\MarcoASMA.INSPER\Downloads\ATSAME70XPLD_SPL.jpg)

## 1) ATSAME70Q21 (Rev. A e Rev. B)

As placas SAME70-XPLD possuem o Microcontrolador ATSAME70Q21, contudo ele possui 2 versões, a ATSAME70Q21 (Rev. A) e a versão ATSAME70Q21**B** (Rev. B). Caso a versão não esteja correta na IDE Atmel Studio, o código a ser transferido para a placa pode não ser gravado corretamente e pode até nem ser reconhecida pela IDE.

### - Identificando a versão de sua placa SAME70-XPLD

Basta olhar o código impresso em cima do CI do Microcontrolador:

|                            REV. A                            |                            REV B                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| ![0 (Editada)](C:\Users\MarcoASMA.INSPER\Downloads\Fotos ATSAME70-XPLD\WhatsApp Unknown 2020-03-24 at 11.05.39\0 (Editada).jpg) | ![2 (Editada)](C:\Users\MarcoASMA.INSPER\Downloads\Fotos ATSAME70-XPLD\WhatsApp Unknown 2020-03-24 at 11.05.39\2 (Editada).jpg) |



### - Alterando a versão na IDE Atmel Studio



