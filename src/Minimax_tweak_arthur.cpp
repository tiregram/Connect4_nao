#include "../include/Minmax_tweak_arthur.hpp"
#include <limits>


Minmax_tweak_arthur::Minmax_tweak_arthur(Player p, int weight, int depth):Minmax(p,weight,depth){	
}

int Minmax_tweak_arthur::compare_4(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4){
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
 			 ((p_c_o == val_4) * weight + (val_4 == EMPTY)))*3)
			* !(val_1 == EMPTY && val_2 == EMPTY && val_3 == EMPTY && val_4 == EMPTY);
}

std::pair<int,int> Minmax_tweak_arthur::min(Game& G, int current_depth, int max_depth){
	
	if (G.is_over() || current_depth == max_depth){
		//return std::make_pair<int,int>(evaluate(G)/(current_depth+1),-1);
		return std::make_pair<int,int>(evaluate(G),-1);
	}
	
	int best_score = std::numeric_limits<int>::max();
	int best_column = 0;
	for (int i = 0; i<7;i++){
		Game aux(G);
	 	Move maux(i,aux.get_turn(),aux);
		if (maux.is_valid() == OK){
			aux.apply(maux);
			std::pair<int,int> score_column = max(aux,current_depth+1,max_depth);
			int score = score_column.first;
			if(score == best_score){
				int random_number = rand() % 2;
				if (random_number == 1) best_column = i;	
			}
			if(score < best_score){
				best_score = score;
				best_column= i;
			}
		}
	}
	return std::make_pair<int,int>(best_score, best_column);
}

std::pair<int,int> Minmax_tweak_arthur::max(Game& G, int current_depth, int max_depth){



	if (G.is_over() || current_depth == max_depth){
		//return std::make_pair<int,int>(evaluate(G)/(current_depth+1),-1);
		return std::make_pair<int,int>(evaluate(G),-1);
	}

	int best_score = std::numeric_limits<int>::min();
	int best_column = 0;
	for (int i = 0; i<7;i++){
		Game aux(G);
		Move maux(i,aux.get_turn(),aux);
		if (maux.is_valid() == OK){
			aux.apply(maux);
			std::pair<int,int> score_column = min(aux,current_depth+1,max_depth);
			int score = score_column.first;			
			if(score == best_score){
				int random_number = rand() % 2;
				if (random_number == 1) best_column = i;
			}
			if(score > best_score){
				best_score = score;
				best_column = i;
			}
		}
	}
	return std::make_pair<int,int>(best_score, best_column);
	
}
