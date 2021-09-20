# Rubrica

!!! info 
    - Em dupla
    - Não pode repetir dupla, mas pode fazer par com colega do outro lab.

    Cria repositório via classroom: https://classroom.github.com/g/WZuf4ADp

!!! tip
    Ao terminar preencha o forms a seguir:
    
    - https://forms.gle/GuA7ZGbrERPMdGdp7
    
    <iframe src="https://docs.google.com/forms/d/e/1FAIpQLSdNF5ocUMjA9tczfyP6tBnvBNIWEClous0JP_D4B3FMgmrjUQ/viewform?embedded=true" width="640" height="300" frameborder="0" marginheight="0" marginwidth="0">Loading…</iframe>
   
A rubrica a seguir será aplicada a nota da entrega:

- A+
    - Testa controle com pessoa externa ao projeto (filma interação)
  
- A (cada item = meio conceito)
    - ~~Firmware e python suportam mais de um controle ao mesmo tempo~~
        - Não da para fazer só com uma placa!
    - Possibilita usuário Ligar e Desligar controle (sleep mode)
        - Deve ajustar o python para reconhecer quando o controle ligar novamente
    - Programa em python envia informações ao controle e isso é exibido ao usuário.
botão e `task_bluetooth`.
  
- B 
    - Grupo cria um primeiro protótipo **conceitual** mecânico para o controle (pode usar papelão, massinha, modelo cad 3d, ...), não precisa ligar a parte elétrica ao mecânico, é só para termos uma ideia de como seria.
    
    - Cria uma task dedicada para receber e processar dados da comunicação (computador --> uC).
    
- C+
    - No lugar de vários semáforos usa uma única fila para comunicar IRQ com `task_bluetooth`.
  
- C
    - Controle desenvolvido para aplicação específica.
    - Utiliza interrupção nos botões.
    - Possuir quatro entradas digitais (botões).
    - Uma entrada analógica.
    - 2x Feedbacks ao usuário:
        - um de uso geral
        - outro deve indicar ao usuário o controle  está pronto para uso (software PC reconhece controle, precisa de hand shake aqui).
    - Comunicação com o computador (bluetooth/ USB-UART).
    - Faz uso de RTOS 
    - Grava vídeo de uso
