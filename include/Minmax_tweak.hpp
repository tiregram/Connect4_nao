#pragma once 
#include "Minmax.hpp"
#include <utility> 

class Minmax_tweak : public Minmax 

{
public:
	Minmax_tweak(Player p, int weight = 5,int depth = 4);
	virtual int compare_4(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4);
	virtual int evaluate(Game G);
 	int compare_4_trick(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4);
 	 virtual std::string class_name() { return "Minmax_tweak";}
};
