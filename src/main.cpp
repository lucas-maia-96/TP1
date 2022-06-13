#include <string.h>

#include "poker.h"

int main() {
  int rodadas = 0, din_init = 0, num_players_total = 0;

  std::ifstream entrada;
  std::ofstream saida;
  int i = 0;

  entrada.open("entrada.txt", std::fstream::in);
  saida.open("saida.txt", std::fstream::out);
  // PRIMEIRA RODADA COM TODOS JOGADORES

  entrada >> rodadas >> din_init >> num_players_total;

  Jogador* lista[num_players_total];

  primeira_rodada(entrada, saida, lista, &num_players_total, &din_init);

  // Zerar o poder e fazer outras maos

  zera_poder_aposta_all(lista, num_players_total);

  for (i = 1; i < rodadas; i++) {
    rodada(entrada, saida, lista, num_players_total);
    zera_poder_aposta_all(lista, num_players_total);
  }

  saida << "####" << std::endl;

  imprime_ranking(saida, lista, num_players_total);

  return 0;
}
