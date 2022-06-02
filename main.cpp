#include <fstream>
#include <string>

#include "baralho.h"
#include "jogador.h"

int main() {
  int rodadas = 0, num_players = 0, din_init = 0, pingo = 0, pote = 0;
  std::string nome;

  /*

  Jogador *players = nullptr;

  Jogador a("Joao", 120);

  a.set_carta(0, 13, 'c');
  a.set_carta(1, 13, 'c');
  a.set_carta(2, 13, 'a');
  a.set_carta(3, 9, 'p');
  a.set_carta(4, 9, 'c');

  a.organiza_bolha();

  a.imprime_mao();

  std::cout << std::endl << a.analisa_mao() << std::endl; */

  std::fstream entrada;

  entrada.open("entrada.txt", std::fstream::in);

  entrada >> rodadas >> din_init >> num_players >> pingo;

  Jogador* lista[num_players];

  int aposta = 0;

  std::string cc;

  for (int i = 0; i < num_players; i++) {
    aposta = 0;
    entrada >> nome;
    lista[i] = new Jogador(nome, din_init);
    entrada >> aposta;
    lista[i]->set_aposta(aposta);

    for (int j = 0; j < 5; j++) {
      entrada >> cc;
      std::cout << "TAMANHO CC = " << cc.length() << "<< " << std::endl;
      if (cc.length() == 2) {
        lista[i]->set_carta(j, (int)cc[0], cc[-1]);
        std::cout << (int)cc[0] << " " << cc[-1] << " ";
      } else if (cc.length() == 3) {
        lista[i]->set_carta(j, stoi(cc.substr(0, 2)), cc[-1]);
        std::cout << stoi(cc.substr(0, 2)) << " " << cc[-1] << " ";
      }
    }
    // lista[i]->imprime_mao();
  }

  return 0;
}
