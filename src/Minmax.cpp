#include "../include/Minmax.hpp"
#include <limits>

Minmax::Minmax(Player p, int weight, int depth):Player_Abs(p),weight(weight),depth(depth){	
}

Minmax::~Minmax(){
}

//Equivalent of main play function of minimax. Calls max first.
Move Minmax::play(Game G){
	std::pair<int,int> result = max(G,0,depth);
	Move m(result.second,G.get_turn(),G);
	return m;
}

//Comparison of 4 Board_states. Used in evaluation function.
inline int Minmax::compare_4(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4){
	Board_state p_c = player_to_board_state(p);
	Board_state p_c_o = player_to_board_state(opposite_player(p));
	//Encourages multiple pieces of the same color with empty spaces rather than with opposite pieces. If everything is empty, score is 0. 
	//This is an exponential growth and the weight can be changed to ensure higher score for bigger sets of pieces.
	return ((((p_c == val_1) * weight + (val_1 == EMPTY)) *
			 ((p_c == val_2) * weight + (val_2 == EMPTY)) * 
			 ((p_c == val_3) * weight + (val_3 == EMPTY)) * 
			 ((p_c == val_4) * weight + (val_4 == EMPTY)))
 			/* - ((((p_c_o == val_1) * weight + (val_1 == EMPTY)) *
 			 ((p_c_o == val_2) * weight + (val_2 == EMPTY)) * 
 			 ((p_c_o == val_3) * weight + (val_3 == EMPTY)) * 
 			 ((p_c_o == val_4) * weight + (val_4 == EMPTY)))))*/
			* !(val_1 == EMPTY && val_2 == EMPTY && val_3 == EMPTY && val_4 == EMPTY));
}

//Evaluation of the game board, used to get a score that will help the AI decide where to play.
int Minmax::evaluate(const Game &G){
	Player player = this->get_color();
	int total_score = 0;
	//Horizontal eval 
	for (int i = 0; i<6; i++){
		for(int j = 0; j<4; j++){
			total_score += compare_4(player, G.get(i,j), G.get(i,j+1), G.get(i,j+2), G.get(i,j+3));
			
		}
	}
	
	//Vertical eval
	for (int i = 0; i<3; i++){
		for(int j = 0; j<7; j++){
			total_score += compare_4(player, G.get(i,j), G.get(i+1,j), G.get(i+2,j), G.get(i+3,j));
		}
	}
	
	//Diagonal ascending eval
	for (int i = 0; i<3; i++){
		for(int j = 0; j<4; j++){
			total_score += compare_4(player, G.get(i,j), G.get(i+1,j+1), G.get(i+2,j+2), G.get(i+3,j+3));
		}
	}
	
	//Diagonal descending eval
	for (int i = 0; i<3; i++){
		for(int j = 3; j<7; j++){
			total_score += compare_4(player, G.get(i,j), G.get(i+1,j-1), G.get(i+2,j-2), G.get(i+3,j-3));
		}
	}

	return total_score;
}


std::pair<int,int> Minmax::min(Game &G, int current_depth, int max_depth){

	Player winner = G.who_win();
	if (winner == this->get_color()){
		return std::make_pair<int,int>(evaluate(G),-1);
	}
	else if (winner == opposite_player(this->get_color())){
		return std::make_pair<int,int>(-evaluate(G),-1);
	}
	else if (G.total_chips() == 42 || current_depth == max_depth){
		return std::make_pair<int,int>(evaluate(G),-1);
	}	
	int best_score = std::numeric_limits<int>::max();
	int best_column = 0;
	for (int i = 0; i<7;i++){
		//Game aux(G);
		Move maux(i,G.get_turn(),G);
		if (maux.is_valid() == OK){
			int empty_space = G.get_first_empty_space(i);
			G.apply(maux);
			std::pair<int,int> score_column = max(G,current_depth+1,max_depth);
			G.set_turn(opposite_player(G.get_turn()));
			G.set(empty_space,i,EMPTY);
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

std::pair<int,int> Minmax::max(Game &G, int current_depth, int max_depth){
	Player winner = G.who_win();
	if (winner == opposite_player(this->get_color())){
		return std::make_pair<int,int>(-evaluate(G),-1);
	}
	else if (winner == this->get_color()){
		return std::make_pair<int,int>(evaluate(G),-1);
	}
	else if (G.total_chips() == 42 || current_depth == max_depth){
		return std::make_pair<int,int>(evaluate(G),-1);
	}	
	int best_score = std::numeric_limits<int>::min();
	int best_column = 0;
	for (int i = 0; i<7;i++){
		//Game aux(G);
		Move maux(i,G.get_turn(),G);
		if (maux.is_valid() == OK){
			int empty_space = G.get_first_empty_space(i);
			G.apply(maux);
			std::pair<int,int> score_column = min(G,current_depth+1,max_depth);
			G.set_turn(opposite_player(G.get_turn()));
			G.set(empty_space,i,EMPTY);
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
