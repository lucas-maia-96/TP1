#include "baralho.h"
#include "jogador.h"

int main() {
  int rodadas, pingo, pote;
  Jogador a("Joao", 120);

  a.set_carta(0, 13, 'c');
  a.set_carta(1, 13, 'c');
  a.set_carta(2, 13, 'a');
  a.set_carta(3, 9, 'p');
  a.set_carta(4, 9, 'c');

  a.organiza_bolha();

  a.imprime_mao();

  std::cout << std::endl << a.analisa_mao() << std::endl;

  return 0;
}
