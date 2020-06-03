# APS 3 - IoT

![](https://live.staticflickr.com/4355/36802620122_fe3ca90fca_c.jpg)

> Fonte: https://www.flickr.com/photos/thinkgizmo/36802620122

Um sistema embarcado de coleta e transmissão de dados via Wi-Fi (data logger)

### Hardware

Será utilizado um módulo [`WINC1500`](https://www.microchip.com/wwwproducts/en/ATWINC1500) como placa de rede Wi-Fi do nosso uC. 

## Descrição

Nessa APS vocês deverão desenvolver um sistema embarcado e uma aplicação web que coleta alguns dados do mundo real e os envia para um servidor Web. Esse envio será feito via uma conexão Wi-Fi (módulo conectado no kit de desenvolvimento) e deverá ser armazenado por um servidor desenvolvido por vocês e hospedado na Web.

Os dados devem possuir [timestamp](https://en.wikipedia.org/wiki/Timestamp) (TS) e para que ele represente um valor condizente, o sistema embarcado deve sincronizar a hora com o servidor Web. Além do TS, deve ser possível identificar a origem dos dados (imaginando um sistema com N dispositivos).

O sistema embarcado deve satisfazer os seguintes requisitos:

### Rubrica

Deve gravar um vídeo demonstrando o funcionamento da APS (embarcado, servidor).
 
- **C**
   - Coletar e enviar para um servidor:
      - Um valor analógico externo a placa (1s)
      - Um valor digital externo a placa (1s)
   - Dados devem possuir Timestamp - `TS`
   - Dados devem possuir identificador de dispositivo - `ID`
   - Embarcado deve sincronizar hora com servidor Web

- Cada item a mais adiciona meio conceito na nota.
    - **Servidor hospedado em nuvem**
    - **Envio dos dados a cada 5 min**
      - dado analógico: continua coletando a cada 1s, mas só envia de 5 em 5 minutos.
    - **dado digital: só envia quando seu estado muda**
    - **Formatar dado para envio com [`json`](https://github.com/zserge/jsmn)**
    - **Aviso visual que dado foi enviado com sucesso**
    - Forma fácil de configurar dispositivo em rede Wi-Fi
      - SDCARD/ UART/ `_provision_mode`
    - Não perder dado se servidor não estiver disponível
    - Caso não haja conexão com internet manter dado salvo até link ativo novamente
    - Segurança 
      - Usar HTTPS, certificado HW e certificado server
      - Criptografar os dados com AES
    - **Demonstrar com mais de um dispositivo funcionando ao mesmo tempo**
