#include "Game.hpp"

class IA_Abs
{

public:
  IA_Abs();
  virtual ~IA_Abs();

  Move play(Game G);

};

