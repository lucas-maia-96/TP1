#include <iostream>

class carta {
 public:
  int get_numero() { return numero; };
  std::string get_naipe() { return naipe; };

 private:
  int numero;
  std::string naipe;
};