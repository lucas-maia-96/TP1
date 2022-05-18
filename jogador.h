#include "baralho.h"

class Jogador {
 public:
  void tira_saldo(int a);
  void soma_saldo(int a);
  int get_saldo(int a);
  void get_name();
  void set_name(std::string name);

 private:
  std::string nome;
  int saldo;
  carta mao[5];
};
