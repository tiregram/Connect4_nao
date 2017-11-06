#pragma once 
#include "AI.hpp"

class Minmax : public AI_Abs 
{

public:

  int depth;
  Minmax(int depth = 4);
  
  virtual ~Minmax();

  virtual Move AI_play(Game G);
  
  bool move_is_win(Game G, int column);
 int minimax(Game G, int depth, int max_depth);
 
 int min(Game G, int depth, int max_depth);
 int max(Game G, int depth, int max_depth);
 
 int compare_4(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4, int weight = 4);
 int evaluate(Game G);
};
