#include "baralho.h"

class Jogador {
 public:
  Jogador(std::string nome, int saldo);
  void tira_saldo(int a) { _saldo -= a; };
  void soma_saldo(int a) { _saldo += a; };
  int get_saldo() { return _saldo; };
  std::string get_name() { return _nome; };
  void set_carta(int pos, int num, char naipe);
  Carta get_carta(int pos) { return _mao[pos]; }

 private:
  std::string _nome;
  int _saldo;
  Carta _mao[5];
};

Jogador::Jogador(std::string nome, int saldo) {
  _nome = nome;
  _saldo = saldo;
}

void Jogador::set_carta(int pos, int num, char naipe) {
  this->_mao[pos].set_carta(num, naipe);
}

bool check_flush(Jogador a) {
  int i = 0;
  char naipe = a.get_carta(0).get_naipe();
  for (i = 0; i < 5; i++) {
    if (a.get_carta(i).get_naipe() != naipe) {
      return false;
    }
  }
  return true;
}