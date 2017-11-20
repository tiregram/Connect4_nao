#pragma once 
#include "AI.hpp"
#include <utility> 

class Minmax : public Player_Abs 
{

public:
  int weight;
  int depth;
  
  Minmax(Player p, int weight = 5, int depth = 4);
  
  virtual ~Minmax();

  virtual Move play(Game G);
 
 virtual std::pair<int,int> min(Game &G, int current_depth, int max_depth);
 virtual std::pair<int,int> max(Game &G, int current_depth, int max_depth);
 
 virtual int compare_4(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4);
 virtual int evaluate(const Game &G);
 virtual std::string class_name() { return "Minmax";}
 virtual int get_depth() { return depth;}
 virtual int get_weight(){ return weight;}
};
