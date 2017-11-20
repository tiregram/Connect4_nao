#pragma once
#include "AI.hpp"

class Human : public Player_Abs 
{

public:
  Human(Player p);
  virtual ~Human();

 virtual Move play(Game G);
 virtual std::string class_name() { return "Human";}
 virtual int get_depth() { return -1;}
 virtual int get_weight(){ return -1;}
  
 };
