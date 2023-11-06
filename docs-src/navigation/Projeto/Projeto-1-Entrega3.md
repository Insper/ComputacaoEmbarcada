# Entrega 2 - Protótipo

| Projeto 1 - Entrega (Protótipo)                                                     |
|------------------------------------------------------------|
| **Data limite para entrega**: =={{proj_entrega2_prototipo_deadline}}==       |
| Usar o repositório do ==[Classroom]({{proj_entrega2_prototipo_classroom}})== |
| Preencher o ==[forms]({{https://docs.google.com/forms/d/e/1FAIpQLSftJoG-P8IRc8FXwSZSN7KLL_kq0ixdFjQGzYE6d30MZsdegA/viewform?usp=sf_link}})==                   |

!!! tip 
    Para começar siga as isseus do seu repositório!

!!! info
    Para atingir conceito maior que C sera necessário fechar as issues criadas após a entrega (qualidade de código)

A rubrica a seguir será aplicada para gerar a nota final:

- A+
    - Testa controle com pessoa externa ao projeto (filma interação)
  
- A (cada item = meio conceito)
    - Possibilita usuário Ligar e Desligar controle (sleep mode)
        - Deve ajustar o python para reconhecer quando o controle ligar novamente
    - Programa em python envia informações ao controle e isso é exibido ao usuário.
  
- B 
    - Grupo cria um primeiro protótipo **conceitual** mecânico para o controle (pode usar papelão, massinha, modelo cad 3d, ...), não precisa ligar a parte elétrica ao mecânico, é só para termos uma ideia de como seria.
    
    - Cria uma task dedicada para receber e processar dados da comunicação (computador --> uC).
    
!!! info
    A ideia aqui é que o PC se comunique com o uC, para isso vocês podem usar a função `self.ser.write()` que irá enviar um **char** para o bluetooth e por consequência para o uC. No uC você pode ler esse dado usando: `char status = usart_read(USART_COM, &readChar);` Se `status` for `1` isso indica que um dado válido foi salvo em `readChar`.
        
    Nessa comunicação vocês podem mandar qualquer coisa, já teve um grupo que enviou o nome da música do spotify que estava sendo tocada e exibiu a música no OELD. Não precisa ser algo tão complexo, podem enviar apenas um housekeeping da comunicação ou um ACK do recebimento do comando.
    
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
