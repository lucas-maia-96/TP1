#include "jogador.h"

class Lista {
 public:
  Lista() { tamanho = 0; };
  int get_tamanho() { return tamanho; };

  virtual Jogador Get_jogador(int pos) = 0;
  virtual Jogador Insere(Jogador a) = 0;
  virtual Jogador Remove(Jogador a) = 0;

 protected:
  int tamanho;
};

class ListaArranjo : public Lista {
 public:
  // ListaArranjo() : Lista();
  Jogador Get_jogador(int pos) = 0;
  Jogador Insere(Jogador a) = 0;
  Jogador Remove(Jogador a) = 0;

 private:
  static const int MAXTAM = 100;
  Jogador _players[MAXTAM];
};

Jogador ListaArranjo::Get_jogador(int pos) {
  if ((pos > tamanho) || (pos < 0)) throw "ERRO: Posicao Invalida";

  return _players[pos];
}
