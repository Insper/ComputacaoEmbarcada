# APS 3 - IoT

![](https://live.staticflickr.com/4355/36802620122_fe3ca90fca_c.jpg)
- imagem: https://www.flickr.com/photos/thinkgizmo/36802620122

Um sistema embarcado de coleta e transmissão de dados via Wi-Fi (data logger)

### Hardware

Será utilizado um módulo [`WINC1500`](https://www.microchip.com/wwwproducts/en/ATWINC1500) como placa de rede Wi-Fi do nosso uC. 

## Descrição

Nessa APS vocês deverão desenvolver um sistema embarcado e uma aplicação web que coleta alguns
dados do mundo real e os envia para um servidor Web. Esse envio será feito via uma conexão Wi-Fi (módulo conectado no kit de desenvolvimento) e deverá ser armazenado por um servidor desenvolvido por vocês e hospedado na Web.

Os dados devem possuir [timestamp](https://en.wikipedia.org/wiki/Timestamp) (TS) e para que ele represente um valor condizente, o sistema embarcado deve sincronizar a hora com o servidor Web. Além do TS, deve ser possível identificar a origem dos dados (imaginando um sistema com N dispositivos).

O sistema embarcado deve satisfazer os seguintes requisitos:

### Rubrica
 

- **C**
  - Coletar e enviar para um servidor:
    - Um valor analógico externo a placa (1s)
    - Um valor digital externo a placa (1s)
  - Dados devem possuir Timestamp
  - Dados devem possuir identificador de dispositivo
  - ~Servidor hospedado em nuvem~
  - Faz uso de RTOS
- **B (3 itens)**
  - **Servidor hospedado em nuvem**
  - Envio dos dados a cada 5min
    - uC entra em sleepmode
    - dado analógico: continua coletando a cada 1s
    - dado digital: só envia quando seu estado mudar
  - Formatar dado para envio com json
  - Demonstrar com mais de um dispositivo funcionando ao mesmo tempo
  - Aviso visual que dado foi enviado com sucesso
  - Forma fácil de configurar dispositivo em rede Wi-Fi
    - SDCARD/ UART/ `_provision_mode`
  - RTOS
    - task para gerenciar leitura dos dados
    - Envia dados para task Wi-Fi via maillbox
  - Powersave (tem que medir!)
      - Wi-Fi entra em sleepmode
- **A  (1 item)**
  - Embarcado deve sincronizar hora com servidor Web
  - Não perder dado se servidor não estiver disponível
    - Caso não haja conexão com internet manter dado salvo até link ativo novamente
  - Segurança 
      - Usar HTTPS, certificado HW e certificado server

Deve gravar um vídeo demonstrando o funcionamento da APS (embarcado, servidor).
