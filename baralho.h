#include <iostream>

#ifndef CARTA
#define CARTA

class Carta {
 public:
  int get_numero() { return _numero; };
  char get_naipe() { return _naipe; };
  void set_carta(int numero, char naipe) {
    _numero = numero;
    _naipe = naipe;
  }
  Carta();

 private:
  int _numero;
  char _naipe;
};

Carta::Carta() {
  _numero = 0;
  _naipe = 'X';
}

#endif