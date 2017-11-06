#pragma once
#include "AI.hpp"

class Basic : public AI_Abs 
{

public:
  Basic();
  virtual ~Basic();

  virtual Move AI_play(Game G);

private:

int win_possibility(Game g);
};

