#include <fstream>
#include <sstream>
#include <string>

#include "jogador.h"

#ifndef POKER
#define POKER

std::string STR_MAO(int maior);

void ganhadores(Jogador** lista, int num_players, std::ofstream& saida,
                int pote);

void primeira_rodada(std::ifstream& entrada, std::ofstream& saida,
                     Jogador** lista, int* num_players_total, int* din_init);

void zera_poder_aposta_all(Jogador** lista, int num_players_total);

void rodada(std::ifstream& entrada, std::ofstream& saida, Jogador** lista, int num_players_total);

void ranking_bolha(Jogador** lista);

void imprime_ranking(std::ofstream& saida, Jogador** lista,
                     int num_players_total);

#endif
