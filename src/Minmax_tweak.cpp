#include "../include/Minmax_tweak.hpp"


Minmax_tweak::Minmax_tweak(Player p, int weight, int depth):Minmax(p,weight,depth){	
}

int Minmax_tweak::compare_4(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4){
	Board_state p_c = player_to_board_state(p);
	Board_state p_c_o = player_to_board_state(opposite_player(p));
	//Encourages multiple pieces of the same color with empty spaces rather than with opposite pieces. If everything is empty, score is 0. 
	//This is an exponential growth and the weight can be changed to ensure higher score for bigger sets of pieces.
	return ((((p_c == val_1) * weight + (val_1 == EMPTY)) *
			 ((p_c == val_2) * weight + (val_2 == EMPTY)) * 
			 ((p_c == val_3) * weight + (val_3 == EMPTY)) * 
			 ((p_c == val_4) * weight + (val_4 == EMPTY)))
 			- (((p_c_o == val_1) * weight + (val_1 == EMPTY)) *
 			 ((p_c_o == val_2) * weight + (val_2 == EMPTY)) * 
 			 ((p_c_o == val_3) * weight + (val_3 == EMPTY)) * 
 			 ((p_c_o == val_4) * weight + (val_4 == EMPTY)))/4)
			* !(val_1 == EMPTY && val_2 == EMPTY && val_3 == EMPTY && val_4 == EMPTY);
}
