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
  virtual std::string class_name() = 0;
  virtual int get_depth() = 0;
  virtual int get_weight() = 0;
  //virtual std::ostream& operator<<(std::ostream& os);
private:
 Player color; 
  
};


