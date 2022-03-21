# Projeto 1 

 
| Entregas  | Data |
|-----------|------|
| Ideia     |      |
| Interface |      |
| Final     |      |


!!! warning "Plágio"
    - Você não pode copiar código (parcial ou total) de outro grupo (do mesmo ou de outro semestre).
    - Você pode usar qualquer código fornecido pela equipe.
    - Código da internet? Você não pode copiar grandes trechos.
    - Código da internet? Se usou alguma coisa, referencie no README.
    
    A regra completa pode ser acessada em: https://www.insper.edu.br/portaldoaluno/wp-content/uploads/2018/08/orientacoes_integridade_intelectual-Engenharias.pdf

!!! info "Atraso"
    - Cada entrega possui uma penalização para o atraso, detalhes nas seccões referentes as entregas.

!!! tip "Dupla"
    - A APS pode ser realizada em dupla.
    - **Você não pode repetir a mesma dupla da APS1.**
    - O desenvolvimento do projeto deve ser feito no repositório criado
    pelo classroom:
        - https://classroom.github.com/a/5rSQSk3z
    - Leia atentamente como trabalhar no repositório:
         - [APS HowTo](https://insper.github.io/ComputacaoEmbarcada/navigation/APS/APS-howto/)


O projeto de computação Embarcada é de escopo fechado e tem como principal objetivo fazer com que vocês passem por todo o ciclo de desenvolvimento de um protótipo de um dispositivo embarcado:

- especificação :arrow_right: implementação :arrow_right: problemas :arrow_right: teste :arrow_right: problemas :arrow_right: finalização.

Neste projeto vocês terão que criar um controle remoto bluetooth, controlado pelo kit de desenvolvimento usado na disciplina (SAME70-XPLD), com a adição de um módulo externo bluetooth HC-05.

A entrega do projeto deve ser um protótipo funcional, e deve possuir todas as funcionalidades esperadas (e especificadas), descritas no folder:

![](folder-controle.pdf)

## Descrição

O controle deve ser um dispositivo que permita controlar remotamente um programa (pode ser um jogo) que estará sendo executado em um PC e deve ser feito específico para a aplicação em questão. A interface do controle com o computador será via `bluetooth`, um programa em python fará a leitura e processamento dos dados.

Características principais:

- Ao menos 4 entradas digitais e uma analógica
- Deve fornecer feedback (saídas digitais) ao usuário no próprio controle
- Customizado para a aplicação 
- Interface via bluetooh 

A seguir algumas ideias de controle:

- Vídeo (youtube/ netflix/ VLC)
- Música (spotify)
- ROS (robô robótica/ drone)
- Jogos (emulador)
    - Mario
    - Minecraft 
- ...

### Entregas

O projeto vai ter três entregas:

1. Idealização e descrição do projeto (README)
1. Estudo de usabilidade / design (README)
1. Protótipo funcional (código/ protótipo mecânico)

## Começando

Vamos começar pensando um pouco no controle! Para isso, faça em dupla a atividade no mural, essa etapa já vai ajudar na entrega (1) e (2):

https://app.mural.co/t/elementos9119/m/elementos9119/1647805316386/ea440968de8c0b032b081bfa8996879bb6318abd?sender=ub569a9273c6e285461187641
