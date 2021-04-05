# Rubrica

!!! info 
    - Em dupla
    - Não pode repetir dupla, mas pode fazer par com colega do outro lab.

    Cria repositório via classroom: https://classroom.github.com/g/0M_7xFQT
    
A rubrica a seguir será aplicada a nota da entrega:

- A+
    - Testa controle com pessoa externa ao projeto (filma interação)
  
- A (cada item = meio conceito)
    - Firmware e python suportam mais de um controle ao mesmo tempo
    - Possibilita usuário Ligar e Desligar controle (sleep mode)
        - Deve ajustar o python para reconhecer quando o controle ligar novamente
    - Programa em python envia informações ao controle e isso é exibido ao usuário.
botão e `task_bluetooth`.
  
- B 
    - Grupo cria um primeiro protótipo mecânico para o controle (pode usar papelão, massinha, ...), não precisa ligar a parte elétrica ao mecânico.
    
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
