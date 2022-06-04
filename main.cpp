#include <fstream>
#include <sstream>
#include <string>

#include "baralho.h"
#include "jogador.h"

int rodadas = 0, din_init = 0, num_players_total = 0;

void ganhadores(Jogador** lista, int num_players) {
  int maior = 0, ganhador = 0, i = 0;
  for (i = 0; i < num_players; i++) {
    if (lista[i]->get_valor_mao() > maior) maior = lista[i]->get_valor_mao();
  }
  std::cout << "Ganhou: ";
  for (i = 0; i < num_players; i++) {
    if (lista[i]->get_valor_mao() == maior)
      std::cout << lista[i]->get_name() << " ";
  }
  std::cout << std::endl;
}

void primeira_rodada(std::ifstream& entrada, Jogador** lista) {
  int num_players = 0, pingo = 0, pote = 0, i = 0, j = 0, aposta = 0;

  std::string nome, cc;

  entrada >> pingo;

  for (i = 0; i < num_players_total; i++) {
    aposta = 0;
    entrada >> nome;
    lista[i] = new Jogador(nome, din_init);
    entrada >> aposta;
    lista[i]->set_aposta(aposta);

    for (j = 0; j < 5; j++) {
      entrada >> cc;
      if (cc.length() == 2) {
        lista[i]->set_carta(j, std::stoi(cc), cc[1]);
      } else if (cc.length() == 3) {
        lista[i]->set_carta(j, std::stoi(cc), cc[2]);
      }
    }
    lista[i]->analisa_mao();
    lista[i]->imprime_mao();
  }

  ganhadores(lista, num_players_total);
}

void zera_poder_all(Jogador** lista) {
  int i = 0;
  for (i = 0; i < num_players_total; i++) {
    lista[i]->reseta_valor_mao();
  }
}

void rodada(std::ifstream& entrada, Jogador** lista) {
  int num_players_parc = 0, pingo = 0, i = 0, aposta = 0, j = 0, k = 0;
  std::string nome_parc, cc;
  entrada >> num_players_parc >> pingo;
  for (k = 0; k < num_players_parc; k++) {
    entrada >> nome_parc;
    for (i = 0; i < num_players_total; i++) {
      if (nome_parc == lista[i]->get_name()) {
        entrada >> aposta;
        lista[i]->set_aposta(aposta);

        for (j = 0; j < 5; j++) {
          entrada >> cc;
          if (cc.length() == 2) {
            lista[i]->set_carta(j, std::stoi(cc), cc[1]);
          } else if (cc.length() == 3) {
            lista[i]->set_carta(j, std::stoi(cc), cc[2]);
          }
        }
        lista[i]->analisa_mao();
        lista[i]->imprime_mao();
      }
    }
  }
  ganhadores(lista, num_players_total);
}

int main() {
  std::ifstream entrada;
  int i = 0;

  entrada.open("entrada.txt", std::fstream::in);
  // PRIMEIRA RODADA COM TODOS JOGADORES

  entrada >> rodadas >> din_init >> num_players_total;

  Jogador* lista[num_players_total];

  primeira_rodada(entrada, lista);

  // Zerar o poder e fazer outras maos

  zera_poder_all(lista);

  for (i = 1; i < rodadas; i++) {
    rodada(entrada, lista);
    zera_poder_all(lista);
  }

  return 0;
}
