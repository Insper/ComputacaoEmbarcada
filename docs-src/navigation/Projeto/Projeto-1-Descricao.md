# Projeto 1 

| Entregas               | Data |
|------------------------|------|
| Entrega 1: Idealização | {{proj_idealizacao_deadline}} |
| Entrega 2: Protótipo   | {{proj_deadline}}  |

!!! video
    ![](https://www.youtube.com/watch?v=Y8Mk-5F9A5M)

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
    pelo [classroom]({{proj_classroom}})
    - Leia atentamente como trabalhar no repositório:
         - [APS HowTo](https://insper.github.io/ComputacaoEmbarcada/navigation/APS/APS-howto/)

O projeto de computação Embarcada é de escopo fechado e tem como principal objetivo fazer com que vocês passem por todo o ciclo de desenvolvimento de um protótipo de um dispositivo embarcado:

- especificação :arrow_right: implementação :arrow_right: problemas :arrow_right: teste :arrow_right: problemas :arrow_right: finalização.

Neste projeto vocês terão que criar um controle remoto bluetooth, controlado pelo kit de desenvolvimento usado na disciplina (SAME70-XPLD), com a adição de um módulo externo bluetooth HC-05.

A entrega do projeto deve ser um protótipo funcional, e deve possuir todas as funcionalidades esperadas de um controle remoto bluetooth (listado a seguir).

## Descrição

O controle deve ser um dispositivo que permita controlar remotamente um programa (pode ser um jogo) que estará sendo executado em um PC e deve ser feito específico para a aplicação em questão. A interface do controle com o computador será via `bluetooth`, um programa em python fará a leitura e processamento dos dados.

Características principais:

- Ao menos 4 entradas digitais e uma analógica
- Deve fornecer feedback (ao menos duas saídas digitais) ao usuário no próprio controle
- Interface via bluetooh 
- Informação de controle pareado 

Para ter ideias do que você pode fazer, consulte a pagina da disciplina com os projetos que já foram feitos nos outos semestres:

- https://insper.github.io/ComputacaoEmbarcada/navigation/Projeto/Projeto-1-Lista/

Além das ideas que já foram executadas, de uma olhada  nos possíveis dispositivos que você pode usar no controle:

- https://insper.github.io/ComputacaoEmbarcada/navigation/Projeto/Projeto-1-Dispositivos/

### RTOS

O projeto deve ser realizando usando o sistema operacional freeRTOS.

## Entregas

O projeto vai ter três entregas:

1. Idealização e descrição do projeto (README)
1. Estudo de usabilidade / design (README)
1. Protótipo funcional (código/ protótipo mecânico)

Cada entrega terá um peso diferente na composição final da nota:

| Etapa       | Entrega | Peso |
|-------------|---------|------|
| Idealização | 1       | 10%  |
| Protótipo   | 2       | 90%  |

## Começando

Vamos começar pensando um pouco no controle! Para isso, faça em dupla a atividade no mural, essa etapa já vai ajudar na entrega (1):

- [MURAL Idealização]({{proj_mural}})
