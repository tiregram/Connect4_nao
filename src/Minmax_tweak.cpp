#include "../include/Minmax_tweak.hpp"


Minmax_tweak::Minmax_tweak(Player p, int weight, int depth):Minmax(p,weight,depth){	
}

int Minmax_tweak::compare_4(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4){
	Board_state p_c = player_to_board_state(p);
	Board_state p_c_o = player_to_board_state(opposite_player(p));
	//Encourages multiple pieces of the same color with empty spaces rather than with opposite pieces. If everything is empty, score is 0. 
	//This is an exponential growth and the weight can be changed to ensure higher score for bigger sets of pieces.
	return (((p_c == val_1) * weight + (val_1 == EMPTY)) *
			 ((p_c == val_2) * weight + (val_2 == EMPTY)) * 
			 ((p_c == val_3) * weight + (val_3 == EMPTY)) * 
			 ((p_c == val_4) * weight + (val_4 == EMPTY)))
			* !(val_1 == EMPTY && val_2 == EMPTY && val_3 == EMPTY && val_4 == EMPTY);
}

int Minmax_tweak::compare_4_trick(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4){
Board_state p_c = player_to_board_state(p);
	
	if((val_1 == EMPTY) && (p_c == val_2) && (p_c == val_3) && (val_4 == p_c)) return 0;
	if((p_c == val_1) && (val_2 == EMPTY) && (p_c == val_3) && (val_4 == p_c)) return 1;
	if((p_c == val_1) && (p_c == val_2) && (val_3 == EMPTY) && (val_4 == p_c)) return 2;
	if((p_c == val_1) && (p_c == val_2) && (p_c == val_3) && (val_4 == EMPTY)) return 3;
	return -1;
	 
}
int Minmax_tweak::evaluate(Game G){
	Player player = this->get_color();
	std::vector< std::pair<int,int> > v;
	int total_score = 0;
	//Horizontal eval 
	for (int i = 0; i<6; i++){
		for(int j = 0; j<4; j++){
			total_score += compare_4(player, G.get(i,j), G.get(i,j+1), G.get(i,j+2), G.get(i,j+3));
			int res = compare_4_trick(player,G.get(i,j), G.get(i,j+1), G.get(i,j+2), G.get(i,j+3));
			if (res > -1) v.push_back(std::make_pair(i,j+res));
			
		}
	}
	
	//Vertical eval
	for (int i = 0; i<3; i++){
		for(int j = 0; j<7; j++){
			total_score += compare_4(player, G.get(i,j), G.get(i+1,j), G.get(i+2,j), G.get(i+3,j));
			int res = compare_4_trick(player,G.get(i,j), G.get(i+1,j), G.get(i+2,j), G.get(i+3,j));
			if (res > -1) v.push_back(std::make_pair(i+res,j));
		}
	}
	
	//Diagonal ascending eval
	for (int i = 0; i<3; i++){
		for(int j = 0; j<4; j++){
			total_score += compare_4(player, G.get(i,j), G.get(i+1,j+1), G.get(i+2,j+2), G.get(i+3,j+3));
			int res = compare_4_trick(player,G.get(i,j), G.get(i+1,j+1), G.get(i+2,j+2), G.get(i+3,j+3));
			if (res > -1) v.push_back(std::make_pair(i+res,j+res));
		}
	}
	
	//Diagonal descending eval
	for (int i = 0; i<3; i++){
		for(int j = 3; j<7; j++){
			total_score += compare_4(player, G.get(i,j), G.get(i+1,j-1), G.get(i+2,j-2), G.get(i+3,j-3));
			int res = compare_4_trick(player,G.get(i,j), G.get(i+1,j-1), G.get(i+2,j-2), G.get(i+3,j-3));
			if (res > -1) v.push_back(std::make_pair(i+res,j-res));
		}
	}
	
	if(v.size() > 1){
	//std::cout<<v.size()<<std::endl;
	for (std::vector< std::pair<int,int> >::iterator x = v.begin(); x < v.end(); x++ ){
		for (std::vector< std::pair<int,int> >::iterator y = v.begin(); y < v.end(); y++ ){
			
			if(abs(x->first - y->first) == 1 && (x->second == y->second)){
				//std::cout<<"Trick detected"<<std::endl<<G<<std::endl;
				total_score += (weight * weight * weight * weight)/3;
			}
		}
	}
	}
		
	
	return total_score;
}
