#pragma once 
#include "Minmax.hpp"
#include <utility> 

class Minmax_tweak_arthur : public Minmax 

{
public:
	Minmax_tweak_arthur(Player p, int weight = 5,int depth = 4);
	
	virtual int compare_4(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4);
	
	virtual std::pair<int,int> min(Game &G, int current_depth, int max_depth);
	virtual std::pair<int,int> max(Game &G, int current_depth, int max_depth);
 	virtual std::string class_name() { return "Minmax_tweak_arthur";}
};
