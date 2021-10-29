# Design 

| Entrega          | Data |
|------------------|------|
| Design interface | 5/11 |

A equipe de novos produtos disponibilizou alguns requisitos funcionais do protótipo (requisitos mínimo). O hardware a ser utilizado será o LCD de `320`x`480`px colorido e touch, que vocês trabalharam no LAB 8.

Na etapa de design, você deve apresentar uma versão inicial da interface que deve satisfazer os requisitos listados a seguir.

Na interface, vocês devem indicar qual widget do LVGL pretendem utilizar. Lembrem de consultar sempre a página do LVGL para saber o que está disponível:

- https://docs.lvgl.io/latest/en/html/widgets/index.html

# Requisitos

Os requisitos mínimos estão listados a seguir:

!!! info "req. 0 - User"
    A interface a ser projetada deve ser tal que o usuário consigo operar com apenas uma mão (lembre que é algo para ser usado na bike) e que as informações devem ser exibidas de forma clara, considerando uma leitura e operação em movimento.

!!! info "req. 1 - Relógio"
    Indicação da hora atual, no formato: **HH:MM:SS**. Deve ser atualizado a cada segundo.

!!! info "req. 2 - Velocidade instantânea"
    Deve ser o componente principal da interface, medido em km/h

!!! info "req. 3 - Indicação da aceleração"
    Deve ser um componente gráfico que indica a aceleração atual da bicicleta (positiva/ negativa ou constante)

!!! info "req. 4 - Velocidade média"
    Indicação em km/h da velocidade média no percurso

!!! info "req. 5 - Distância do percurso"
    Indicação em km da distância percorrida no percurso

!!! info "req. 6 - Tempo no percurso"
    Indicação em **HH:MM** do tempo gasto em um percurso

!!! info "req. 7 - Botões: Start/ Stop/ Reset"
    Botões (**touch**) que permitem: Iniciar a contagem de um novo percurso, parar a contagem desse percurso e reiniciar o percurso.

    Quando o sistema estiver no modo **Stop**, o sistema deve exibir a velocidade instantânea, mas não pode atualizar outras informações referentes ao percurso (velocidade média/ distância no percurso/ tempo no percurso).

!!! info "req. 8 - Indicador status"
    A tela deve possuir um indicador se a contagem da parte referente ao percurso está ou não ativada (Start/Stop).

!!! info "req. 9 - Configuracão"
    Deve possibilitar o usuário configurar o diâmetro da roda.

### Extras 

A equipe identificou funcionalidades extras que seriam interessante ao projeto:

- Possibilitar criar vários 'Percursos'
- Exibir inclinação da bike (aclive/plano)
- Elevação total do percurso 
- Tema Light/Dark
- Cadência do pedal
- Batimento cardíaco/oximetria 
- Interface com GPS e velocidade.
