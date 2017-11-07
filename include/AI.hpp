#pragma once 
#include "Game.hpp"
#include "cstdlib"



class Player_Abs
{

public:
  Player_Abs(Player p):color(p){}
  
  /*virtual ~AI_Abs();*/

  virtual Move play(Game G) = 0;
  Player get_color(){ return color;};
private:
 Player color;  
};


