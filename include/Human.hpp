#pragma once
#include "AI.hpp"

class Human : public Player_Abs 
{

public:
  Human(Player p);
  virtual ~Human();

  virtual Move play(Game G);
  
 };
