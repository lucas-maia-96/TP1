#include "baralho.h"
#include "jogador.h"

int main() {
  std::cout << "Helo World" << std::endl;
  std::cout << "git works" << std::endl;
  Jogador a("Joao", 120);

  a.set_carta(0, 2, 'c');
  a.set_carta(1, 3, 'c');
  a.set_carta(2, 4, 'c');
  a.set_carta(3, 5, 'c');
  a.set_carta(4, 6, 'c');

  if (check_flush(a)) {
    std::cout << "\nDEU FLUSH !!!!" << std::endl;
  } else {
    std::cout << "\nNADA NA MAO" << std::endl;
  }

  return 0;
}
