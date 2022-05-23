#include "baralho.h"
#include "jogador.h"

int main() {
  Jogador a("Joao", 120);

  a.set_carta(0, 13, 'c');
  a.set_carta(1, 12, 'c');
  a.set_carta(2, 11, 'c');
  a.set_carta(3, 10, 'c');
  a.set_carta(4, 1, 'c');

  a.organiza_bolha();

  a.imprime_mao();

  if (check_straight(a)) {
    std::cout << "TEM UM STRAIGTH" << std::endl;
    if (check_royal_straight(a)) {
      std::cout << ">>>>>>ROYAL<<<<<<" << std::endl;
    }
  } else {
    std::cout << "NAO TEM JOGO" << std::endl;
  }

  return 0;
}
