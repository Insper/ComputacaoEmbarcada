
# Sobre

## Objetivos de aprendizagem 

Ao final da disciplina o estudante será capaz de:

1.	Criar softwares para microcontroladores utilizando suas especificidades (periféricos/ lowpower);
2.	Avaliar e melhorar soluções embarcadas integrando hardware/software levando em conta adequação a uma aplicação;
3.	Integrar em um protótipo hardware, software básico, sistema operacional de tempo real e módulos de interfaceamento com usuários, de comunicação e de alimentação.
4.	Compreender as limitações de microcontroladores e seus periféricos;
5.	Buscar e analisar documentação (datasheet) e extrair informações relevantes.

## Conteúdo Programático

1.	Sistemas embarcados microcontrolados e suas tecnologias
2.	Linguagem C para sistemas embarcados (firmware)
3.	Interface com o mundo externo (digital/analógica)
4.	Periféricos de microcontoladores
5.	Interrupção, superloop, Multitask
6.	Alimentação para sistemas embarcados
7.	Otimização energética
8.	Protocolos de comunicação
9.	Conectividade em sistemas embarcados - IoT, computação vestível, computação ubíqua.
10.	Sistema operacional de tempo real (RTOS)

## Softwares

!!! warning "Alerta para usuários de Linux e Windows"
    Não funciona no VirtualBox! Deve utilizar o VMWARE como máquina virtual

# Requisito de software para a disciplina

O AtmelStudio, IDE utilizado para programação dos microcontroladores da Atmel (usado no curso) é nativo Windows. Se for virtualizar, utilizar o [VMware Player](https://my.vmware.com/en/web/vmware/free#desktop_end_user_computing/vmware_workstation_player/12_0) pois o VirtualBox possui problemas com o driver USB do gravador.

A seguir informações a seguir do que fazer para cada sistema operacional:

## Windows 10


!!! note "Nota"
    reservar **2h** para instalação

Instalar os seguintes softwares no Windows:

- Sistema Operacional 
    - Windows 10
- Softwares :
    - [Atmel Studio 7](https://www.microchip.com/mplab/avr-support/atmel-studio-7) - Instalar a *versão WEB*
         - **Download:** http://studio.download.atmel.com/7.0.1931/as-installer-7.0.1931-web.exe
    - Serial Port for AtmelStudio
         - **Download:** https://gallery.microchip.com/api/v2/package/EFC4C002-63A3-4BB9-981F-0C1ACAF81E03/2.8.4
    - [git/github](https://desktop.github.com/)

        
## Usuários LINUX

!!! note "Nota"
    reservar **4h** para instalação

Opções : 

1. DualBoot com Windows
1. Instalar o VMWare player e instalar o windows 10 na máquina virtual.
    - **NÃO USAR VIRTUALBOX, [USAR VMWARE PLAYER](https://www.vmware.com/products/workstation-player.html)**
1. Efetuar o boot no pendrive.

!!! note ""
    Instalar os softwares listados na secção Windows.

## Usuário MAC

!!! note "Nota"
    reservar **4h** para instalação

Opções:

1. DualBoot com Windows
1. Efetuar o boot no pendrive
1. Virtualizar com `VMware` ou `Parallels` 


!!! note ""
    Instalar os softwares listados na secção Windows.

!!! warning "Alerta para usuários de Linux e Windows"
    Não funciona no VirtualBox! Deve utilizar o VMWARE como máquina virtual

## Kit de Desenvolvimento 

### Arquitetura

1.  **Processador ARM :** Possui ampla dominação do mercado de
    microprocessadores/controladores [^1]; não é exclusivo de um único
    fabricante [^2]; arquitetura de 32 bits.

2.  **Cortex M :** família M é classificada como a de
    microcontroladores, possuindo uma arquitetura interna menos
    sofisticadas das demais (A,R), possibilitando um melhor entendimento
    de seu funcionamento.

### Kit de desenvolvimento - ATSAME70-XPLD

- https://www.microchip.com/developmenttools/ProductDetails/atsame70-xpld

O kit de desenvolvimento escolhido para o curso é o *SAM E70 Xplained*
[^3] desenvolvido pela Atmel-Microchip possui as principais
características:

-   SAM E70 - high-performance ARM Cortex-M7 core-based MCU

-   Ethernet, HS USB, SD card

-   Embedded debugger

![SAM E70 Xplained](imgs/kit/kit.png)

### Periféricos extras

Periféricos extras podem ser adicionados ao kit para incluir
funcionalidades tais como : bluetooth 4.0; wifi; LCD.

### Bluetooth - BTLC1000 Xplained Pro Evaluation Kit

<http://www.atmel.com/pt/br/tools/ATBTLC1000-XPRO.aspx>\
Periférico para adicionar a comunicação bluetooth 4.0 ao kit de
desenvolvimento.

Especificação :

-   The Atmel® ATBTLC1000-MR110CA BLE module with 2.4GHz BLE4.1
    compliant ATBTLC1000A SoC (System on Chip)

-   On Board Temperature Sensor

![Módulo bluetooth](imgs/kit/bluetooth.png)

### Wifi - ATWINC1500-XPRO

- https://www.microchip.com/developmenttools/ProductDetails/ATWINC1500-XPRO

Módulo necessário para acrescentar comunicação wifi ao kit.

Especificação:

-   IEEE 802.11 b/g/n 20MHz (1x1) solution

-   Supports IEEE 802.11 WEP, WPA, and WPA2 Security

-   SPI, UART, and I2C host interface

![Módulo wifi](imgs/kit/wifi.jpg)

### LCD maXTouch Xplained Pro

https://www.microchip.com/developmenttools/ProductDetails/ATMXT-XPRO

Módulo para adicionar LCD colorido com touch screen ao kit de
desenvolvimento.

Especificação :

-   ILI9488 LCD Driver

-   480x320 Resolution

-   Parallel interface (up to 18-bits)

-   3 & 4 wire SPI interface

-   maXTouch capacitive touch screen controller

![LCD touch](imgs/kit/lcd.jpg)

### OLED1 Xplained Pro

- https://www.microchip.com/developmenttools/ProductDetails/atoled1-xpro

Módulo com OLED de 32 linhas.

-   OLED display 128x32 (SPI)

-   3 LEDs

-   3 push buttons

![LCD touch](imgs/kit/oled.jpg)

[^1]: <http://www.investopedia.com/stock-analysis/061115/3-key-numbers-arm-holdings-investors-need-know-armh.aspx>

[^2]: ARM não produz CIs mas fornece a arquitetura para fabricantes de
    chips (Atmel, Texas, Nvidia,...)

[^3]: <http://www.atmel.com/pt/br/tools/ATSAME70-XPLD.aspx?tab=applications>
