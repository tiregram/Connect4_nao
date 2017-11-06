#pragma once 
#include "Game.hpp"
#include "cstdlib"



class AI_Abs
{

public:
 /* AI_Abs();
  virtual ~AI_Abs();*/

  virtual Move AI_play(Game G) = 0;

};

