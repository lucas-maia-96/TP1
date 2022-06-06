#include "baralho.h"

#ifndef JOGADOR
#define JOGADOR

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

 private:
  std::string _nome;
  int _saldo;
  Carta _mao[5];
  int _valor_mao;
  int _aposta;
  int _maior_carta_all;
  int _maior_carta_mao;
};

int check_flush(Jogador *a);

int check_straight(Jogador *a);

int check_royal_straight(Jogador *a);

int check_par(Jogador *a);

#endif