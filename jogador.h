#include "baralho.h"

#define ROYAL_STRAIGHT_FLUSH 10
#define STRAIGHT_FLUSH 9
#define FOUR 8
#define FULL_HOUSE 7
#define FLUSH 6
#define STRAIGHT 5
#define TRINCA 4
#define DOIS_PARES 3
#define UM_PAR 2

#define Troca(A, B) \
  {                 \
    Carta C = A;    \
    A = B;          \
    B = C;          \
  }

class Jogador {
 public:
  Jogador(std::string nome, int saldo);
  void tira_saldo(int a) { _saldo -= a; };
  void soma_saldo(int a) { _saldo += a; };
  int get_saldo() { return _saldo; };
  std::string get_name() { return _nome; };
  void set_carta(int pos, int num, char naipe);
  Carta get_carta(int pos) { return _mao[pos]; };
  void organiza_bolha();
  void imprime_mao();

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

void Jogador::organiza_bolha() {
  int i, j, trocou;
  for (i = 0; i < 5; i++) {
    trocou = 0;
    for (j = 1; j < 5 - i; ++j) {
      if (_mao[j].get_numero() < _mao[j - 1].get_numero()) {
        Troca(this->_mao[j - 1], this->_mao[j]);
        trocou = 1;
      }
    }
    if (!trocou) break;
  }
}

void Jogador::imprime_mao() {
  int i = 0;
  std::cout << "\n" << _nome << ":\n";
  for (i = 0; i < 5; i++) {
    std::cout << _mao[i].get_numero() << _mao[i].get_naipe() << " ";
  }
  std::cout << std::endl;
}

int check_flush(Jogador a) {
  int i = 0;
  char naipe = a.get_carta(0).get_naipe();
  for (i = 0; i < 5; i++) {
    if (a.get_carta(i).get_naipe() != naipe) {
      return 0;
    }
  }
  return FLUSH;
}

void Bolha(Jogador* a) {
  int i = 0;
  for (i = 0; i < 5; i++) {
  }
}

int check_straight(Jogador a) {
  int i = 0;
  // tratando royal straight e straight na mesma funcao
  if ((a.get_carta(1).get_numero() == a.get_carta(0).get_numero() + 1) ||
      (a.get_carta(0).get_numero() == 1 && a.get_carta(1).get_numero() == 10)) {
    for (i = 2; i < 5; i++) {
      if (a.get_carta(i).get_numero() != a.get_carta(i - 1).get_numero() + 1) {
        return 0;
      }
    }
    return STRAIGHT;
  }
  return 0;
}

bool check_royal_straight(Jogador a) {
  int i = 0;
  for (i = 2; i < 5; i++) {
    if ((a.get_carta(0).get_numero() == 1 && a.get_carta(1).get_numero() == 10))
      return true;
  }
  return false;
}