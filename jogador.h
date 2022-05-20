#include "baralho.h"

class Jogador {
 public:
  Jogador(std::string nome, int saldo);
  void tira_saldo(int a) { _saldo -= a; };
  void soma_saldo(int a) { _saldo += a; };
  int get_saldo() { return _saldo; };
  std::string get_name() { return _nome; };

 private:
  std::string _nome;
  int _saldo;
  carta _mao[5];
};

Jogador::Jogador(std::string nome, int saldo) {
  _nome = nome;
  _saldo = saldo;
}