#include <fstream>
#include <sstream>
#include <string>

#include "jogador.h"

#define Troca_JOG(A, B) \
  {                     \
    Jogador* C = A;     \
    A = B;              \
    B = C;              \
  }

std::string STR_MAO(int maior) {
  if (maior == 14) return "RST";
  if (maior == 11) return "SF";
  if (maior == 8) return "FK";
  if (maior == 7) return "FH";
  if (maior == 6) return "F";
  if (maior == 5) return "S";
  if (maior == 4) return "TK";
  if (maior == 3) return "TP";
  if (maior == 2) return "OP";
  return "HC";
}

/* Principal funcao do trabalho: Realiza a comparacao das maos dos jogadores,
realiza dsempate, computa o pote, imprime o resultado */

void ganhadores(Jogador** lista, int num_players, std::ofstream& saida,
                int pote) {
  int maior = 0, ganhador = 0, i = 0, desempate = 0, des_2 = 0;

  // verfica a maior mao da rodada
  for (i = 0; i < num_players; i++) {
    if (lista[i]->get_valor_mao() > maior) maior = lista[i]->get_valor_mao();
  }

  // realiza desempate
  for (i = 0; i < num_players; i++) {
    if (lista[i]->get_valor_mao() == maior) {
      if (maior == 14 || maior == 11 || maior == 7 || maior == 6 ||
          maior == 5) {
        if (lista[i]->get_maior_carta_mao() > desempate) {
          desempate = lista[i]->get_maior_carta_mao();
        }
      } else {
        if (lista[i]->get_maior_carta_mao() > desempate) {
          desempate = lista[i]->get_maior_carta_mao();
          des_2 = lista[i]->get_maior_carta_all();
        }
      }
    }
  }

  for (i = 0; i < num_players; i++) {
    if (lista[i]->get_valor_mao() == maior) {
      if (maior == 14 || maior == 11 || maior == 6 || maior == 5) {
        if (lista[i]->get_maior_carta_mao() == desempate) ganhador++;
      } else {
        if (lista[i]->get_maior_carta_mao() == desempate &&
            des_2 == lista[i]->get_maior_carta_all())
          ganhador++;
      }
    }
  }

  // Imprime resultado da rodada
  saida << ganhador << " " << pote / ganhador << " " << STR_MAO(maior)
        << std::endl;

  // divite o pote entra os ganhadores
  for (i = 0; i < num_players; i++) {
    if (lista[i]->get_valor_mao() == maior) {
      if (maior == 11 || maior == 7 || maior == 6 || maior == 5) {
        if (lista[i]->get_maior_carta_mao() == desempate) {
          saida << lista[i]->get_name() << std::endl;
          lista[i]->soma_saldo(pote / ganhador);
        }
      } else {
        if (lista[i]->get_maior_carta_mao() == desempate &&
            des_2 == lista[i]->get_maior_carta_all()) {
          saida << lista[i]->get_name() << std::endl;
          lista[i]->soma_saldo(pote / ganhador);
        }
      }
    }
  }
}

void primeira_rodada(std::ifstream& entrada, std::ofstream& saida,
                     Jogador** lista, int* num_players_total, int* din_init) {
  int pingo = 0, pote = 0, i = 0, j = 0, aposta = 0;

  std::string nome, cc;

  entrada >> pingo;

  for (i = 0; i < *num_players_total; i++) {
    aposta = 0;
    entrada >> nome;
    lista[i] = new Jogador(nome, *din_init);
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
  }

  for (i = 0; i < *num_players_total; i++) {
    pote += lista[i]->get_aposta() + pingo;
    lista[i]->tira_saldo(pingo + lista[i]->get_aposta());
  }

  ganhadores(lista, *num_players_total, saida, pote);
}

void zera_poder_aposta_all(Jogador** lista, int num_players_total) {
  int i = 0;
  for (i = 0; i < num_players_total; i++) {
    lista[i]->reseta_valor_mao();
    lista[i]->reseta_aposta();
  }
}

void rodada(std::ifstream& entrada, std::ofstream& saida, Jogador** lista,
            int num_players_total) {
  int num_players_parc = 0, pingo = 0, pote = 0, i = 0, aposta = 0, j = 0,
      k = 0;
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
      }
    }
  }

  // teste de insanidade
  for (i = 0; i < num_players_total; i++) {
    if ((lista[i]->get_aposta() + pingo) > lista[i]->get_saldo() ||
        (lista[i]->get_aposta() % 50 != 0)) {
      saida << "0 0 I" << std::endl;
      return;
    }
  }

  // formacao do pote
  for (i = 0; i < num_players_total; i++) {
    pote += lista[i]->get_aposta() + pingo;
    lista[i]->tira_saldo(pingo + lista[i]->get_aposta());
  }

  ganhadores(lista, num_players_total, saida, pote);
}

// ranking dos jogadores, baseado no saldo (bubble sort)
void ranking_bolha(Jogador** lista, int num_players_total) {
  int i, j, trocou;
  for (i = 0; i < num_players_total; i++) {
    trocou = 0;
    for (j = 1; j < num_players_total - i; ++j) {
      if (lista[j]->get_saldo() > lista[j - 1]->get_saldo()) {
        Troca_JOG(lista[j - 1], lista[j]);
        trocou = 1;
      }
    }
    if (!trocou) break;
  }
}

void imprime_ranking(std::ofstream& saida, Jogador** lista,
                     int num_players_total) {
  ranking_bolha(lista, num_players_total);
  int i = 0;
  for (i = 0; i < num_players_total; i++) {
    lista[i]->check_saldo();
    saida << lista[i]->get_name() << " " << lista[i]->get_saldo() << std::endl;
  }
}
