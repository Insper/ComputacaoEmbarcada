# APS 3 - IoT

![](https://live.staticflickr.com/4355/36802620122_fe3ca90fca_c.jpg)

> Fonte: https://www.flickr.com/photos/thinkgizmo/36802620122

Um sistema embarcado de coleta e transmissão de dados via Wi-Fi (data logger), será utilizado o módulo [`WINC1500`](https://www.microchip.com/wwwproducts/en/ATWINC1500) como placa de rede Wi-Fi do nosso uC. 


!!! info
    Criar repositório pelo classroom: https://classroom.github.com/g/XY1XxJiK

## Descrição

Nessa APS vocês deverão desenvolver um sistema embarcado e uma aplicação web que coleta alguns dados do mundo real e os envia para um servidor Web. Esse envio será feito via uma conexão Wi-Fi (módulo conectado no kit de desenvolvimento) e deverá ser armazenado por um servidor desenvolvido por vocês e hospedado na Web.

Os dados devem possuir [timestamp](https://en.wikipedia.org/wiki/Timestamp) (TS) e para que ele represente um valor condizente, o sistema embarcado deve sincronizar a hora com o servidor Web. Além do TS, deve ser possível identificar a origem dos dados (imaginando um sistema com N dispositivos).

!!! info 
    Posso usar o WIFI com o LCD? Eles compartilham alguns pinos da comunicacão SPI, mas estamos trabalhando em solução. 

## Rubrica

O protótipo deve possuir os recursos mínimos (C) e para cada item extra é adiconado meio conceito. Vocês Devem gravar um vídeo demonstrando o funcionamento da APS (embarcado, servidor) funcionando.

!!! info
    Ao finalizar preencher o forms a seguir:
    
    - https://docs.google.com/forms/d/e/1FAIpQLSf8Y3ZrmyTn0DkS5bNTRbRQCQ6lBXUE6E-o3fF7_GXiyv5tVg/viewform

### C

- Coletar e enviar para um servidor:
    - Um valor analógico externo a placa (1s)
    - Um valor digital externo a placa (1s)
- Dados devem possuir Timestamp - `TS` (identificaćão de quando foram coletos `DD:MM:YY/HH:MM:SS`)
- Dados devem possuir identificador de dispositivo - `ID`
- Embarcado deve sincronizar hora com Web
    - exemplo já pega calendário e hora da web, precisa atualizar RTC com esses valores.
- ~~Servidor hospedado em nuvem (aws, ...)~~
- ~~Demonstrar com mais de um dispositivo funcionando ao mesmo tempo~~
    - ~~os dois integrantes executam ao mesmo tempo.~~
    
### extras

Cada item a mais adiciona meio conceito na nota.

- ID da placa é coletado automaticamente.
    - Dica: que tal usar o mac address?
- **Envio dos dados a cada 5 min**
    - dado analógico: continua coletando a cada 1s, mas só envia de 5 em 5 minutos 
    - objetivo disso é poupar bateria.
- Não perder dado se servidor não estiver disponível
    - Caso não haja conexão com internet manter dado salvo até link ativo novamente
- Segurança 
    - Usar HTTPS, certificado HW e certificado server
    - Criptografar os dados com AES
- **Formatar dado para envio com [`json`](https://github.com/zserge/jsmn)**
- Forma fácil de configurar dispositivo em rede WIFI
    - SDCARD/ UART/ `_provision_mode`

- (+1.0) Servidor hospedado em nuvem (aws, ...)**
- (+0.5) Demonstrar com mais de um dispositivo funcionando ao mesmo tempo
    - os dois integrantes executam ao mesmo tempo.
