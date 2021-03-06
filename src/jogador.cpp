#include "baralho.h"

#define ROYAL_STRAIGHT_FLUSH 14
#define STRAIGHT_FLUSH 11
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
  void analisa_mao();
  int get_valor_mao() { return _valor_mao; };
  void reseta_valor_mao() { _valor_mao = 0; };
  void reseta_aposta() { _aposta = 0; };
  void set_aposta(int a) { _aposta = a; };
  int get_aposta() { return _aposta; };
  void zera_poder() { _valor_mao = -1; }
  int get_maior_carta_mao() { return _maior_carta_mao; };
  int get_maior_carta_all() { return _maior_carta_all; };
  void check_saldo();

 private:
  std::string _nome;
  int _saldo;
  Carta _mao[5];
  int _valor_mao;
  int _aposta;
  int _maior_carta_all;
  int _maior_carta_mao;
};

// construtor
Jogador::Jogador(std::string nome, int saldo) {
  _nome = nome;
  _saldo = saldo;
}

// insere os valores de uma das 5 cartas da mao do jogador
void Jogador::set_carta(int pos, int num, char naipe) {
  this->_mao[pos].set_carta(num, naipe);
}

// organiza a mao do jogador de forma crescente (bubble sort)
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

// metodo util para verificacoes e testes
void Jogador::imprime_mao() {
  int i = 0;
  std::cout << "\n" << _nome << ":\n";
  for (i = 0; i < 5; i++) {
    std::cout << _mao[i].get_numero() << _mao[i].get_naipe() << " ";
  }
  std::cout << std::endl;
  std::cout << "Tem um: " << get_valor_mao() << std::endl;
}

int check_flush(Jogador *a) {
  int i = 0;
  char naipe = a->get_carta(0).get_naipe();
  for (i = 0; i < 5; i++) {
    if (a->get_carta(i).get_naipe() != naipe) {
      return 0;
    }
  }
  return FLUSH;
}

int check_straight(Jogador *a) {
  int i = 0;
  if ((a->get_carta(1).get_numero() == a->get_carta(0).get_numero() + 1) ||
      (a->get_carta(0).get_numero() == 1 &&
       a->get_carta(1).get_numero() == 10)) {
    for (i = 2; i < 5; i++) {
      if (a->get_carta(i).get_numero() !=
          a->get_carta(i - 1).get_numero() + 1) {
        return 0;
      }
    }
    return STRAIGHT;
  }
  return 0;
}

int check_royal_straight(Jogador *a) {
  int i = 0;
  for (i = 2; i < 5; i++) {
    if ((a->get_carta(0).get_numero() == 1 &&
         a->get_carta(1).get_numero() == 10))
      return 3;
  }
  return 0;
}

// verifica Um par, Dois pares, Trinca e FullHouse
int check_par(Jogador *a) {
  int i = 0, j = 0, count = 0, atual = 0, dupla = 0, trinca = 0, quadra = 0;
  for (i = 0; i < 5; i += count) {
    count = 0;
    atual = a->get_carta(i).get_numero();
    for (j = i; j < 5; j++) {
      if (a->get_carta(j).get_numero() == atual) {
        count++;
      } else {
        break;
      }
    }
    if (count == 2) {
      dupla++;
    } else if (count == 3) {
      trinca++;
    } else if (count == 4) {
      quadra++;
    }
  }
  if (dupla == 1 && trinca == 0) return UM_PAR;
  if (dupla == 2) return DOIS_PARES;
  if (trinca == 1 && dupla == 0) return TRINCA;
  if (trinca == 1 && dupla == 1) return FULL_HOUSE;
  if (quadra == 1) return FOUR;
  return 0;
}

// Desempate de Um par, Dois Pares, Trinca e FullHouse
int check_maior_carta_par(Jogador *a) {
  int i = 0, j = 0, count = 0, atual = 0, carta_repete = 0;
  if (a->get_valor_mao() != FULL_HOUSE) {
    for (i = 0; i < 5; i += count) {
      count = 0;
      atual = a->get_carta(i).get_numero();
      for (j = i; j < 5; j++) {
        if (a->get_carta(j).get_numero() == atual) {
          count++;
        } else {
          break;
        }
      }
      if (count >= 2) carta_repete = atual;
    }
  }
  if (a->get_valor_mao() == FULL_HOUSE) {
    for (i = 0; i < 5; i += count) {
      count = 0;
      atual = a->get_carta(i).get_numero();
      for (j = i; j < 5; j++) {
        if (a->get_carta(j).get_numero() == atual) {
          count++;
        } else {
          break;
        }
      }
      if (count == 3) carta_repete = atual;
    }
  }
  return carta_repete;
}

void Jogador::analisa_mao() {
  this->organiza_bolha();
  int poder = 0;
  _maior_carta_all = _mao[4].get_numero();
  if (check_flush(this) && check_straight(this)) {
    if (check_royal_straight(this))
      poder += check_royal_straight(this);
    else {
      poder += check_flush(this) + check_straight(this);
      _maior_carta_mao = this->_mao[4].get_numero();
    }
  } else if (check_par(this) == FOUR) {
    poder += check_par(this);
    _maior_carta_mao = check_maior_carta_par(this);
    _maior_carta_all = this->_mao[4].get_numero();
  } else if (check_par(this) == FULL_HOUSE) {
    poder += check_par(this);
    _maior_carta_mao = check_maior_carta_par(this);
  } else if (check_flush(this)) {
    poder += check_flush(this);
    _maior_carta_mao = this->_mao[4].get_numero();
  } else if (check_straight(this)) {
    poder += check_straight(this);
    _maior_carta_mao = this->_mao[4].get_numero();
  } else if (check_par(this)) {
    poder += check_par(this);
    _maior_carta_mao = check_maior_carta_par(this);
  }
  this->_valor_mao = poder;
}

// teste de insanidade
bool insano(Jogador *a) {
  if (a->get_saldo() < 0)
    return true;
  else
    return false;
}

void Jogador::check_saldo() {
  if (_saldo < 0) _saldo = 0;
}
