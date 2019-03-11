#ifndef MAQUINA1
#define MAQUINA1

typedef struct ciclo t_ciclo;

struct ciclo{
  char nome[32];           // nome do ciclo, para ser exibido
  int  enxagueTempo;       // tempo que fica em cada enxague
  int  enxagueQnt;         // quantidade de enxagues
  int  centrifugacaoRPM;   // velocidade da centrifugacao
  int  centrifugacaoTempo; // tempo que centrifuga
  char heavy;              // modo pesado de lavagem
  char bubblesOn;          // smart bubbles on (???)
  t_ciclo *previous;
  t_ciclo *next;
};

t_ciclo c_rapido = {.nome = "Rapido",
                    .enxagueTempo = 5,
                    .enxagueQnt = 3,
                    .centrifugacaoRPM = 900,
                    .centrifugacaoTempo = 5,
                    .heavy = 0,
                    .bubblesOn = 1
                  };

t_ciclo c_diario = {.nome = "Diario",
                    .enxagueTempo = 15,
                    .enxagueQnt = 2,
                    .centrifugacaoRPM = 1200,
                    .centrifugacaoTempo = 8,
                    .heavy = 0,
                    .bubblesOn = 1,
                  };

t_ciclo c_pesado = {.nome = "Pesado",
                     .enxagueTempo = 10,
                     .enxagueQnt = 3,
                     .centrifugacaoRPM = 1200,
                     .centrifugacaoTempo = 10,
                     .heavy = 1,
                     .bubblesOn = 1,
                  };

t_ciclo c_enxague = {.nome = "Enxague",
                     .enxagueTempo = 10,
                     .enxagueQnt = 1,
                     .centrifugacaoRPM = 0,
                     .centrifugacaoTempo = 0,
                     .heavy = 0,
                     .bubblesOn = 0,
                  };

t_ciclo c_centrifuga = {.nome = "Centrifuga",
                     .enxagueTempo = 0,
                     .enxagueQnt = 0,
                     .centrifugacaoRPM = 1200,
                     .centrifugacaoTempo = 10,
                     .heavy = 0,
                     .bubblesOn = 0,
};


t_ciclo *initMenuOrder();

#endif
main.c~
