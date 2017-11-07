#pragma once
#include "AI.hpp"

class Basic : public Player_Abs 
{

public:
  Basic(Player p);
  virtual ~Basic();

  virtual Move play(Game G);

private:

int win_possibility(Game g);
};

