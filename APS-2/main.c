/** 
 * Computação Embarcada
 * APS 2 
 * Rafael . Corsi @ insper . edu . br
 */ 
#include <stdio.h>
#include "maquina1.h"

/**
 * Inicializa ordem do menu
 * retorna o primeiro ciclo que
 * deve ser exibido.
 */
t_ciclo *initMenuOrder(){
  c_rapido.previous = &c_enxague;
  c_rapido.next = &c_diario;

  c_diario.previous = &c_rapido;
  c_diario.next = &c_pesado;

  c_pesado.previous = &c_diario;
  c_pesado.next = &c_enxague;

  c_enxague.previous = &c_pesado;
  c_enxague.next = &c_centrifuga;

  c_centrifuga.previous = &c_enxague;
  c_centrifuga.next = &c_rapido;

  return(&c_diario);
}

void main(void){
  t_ciclo *p_primeiro = initMenuOrder();
  printf("%s", p_primeiro->next->next->nome);
}
