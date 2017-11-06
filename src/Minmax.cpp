#include "../include/Minmax.hpp"

Minmax::Minmax(int depth):depth(depth){	
}

Minmax::~Minmax(){
}

  
Move Minmax::AI_play(Game G){
	//std::cout<< "eval pre-start :" <<evaluate(G)<<std::endl;
	int best_score=-(4*4*4*4);
	int column;
	for (int i = 0; i<7; i++){
		//std::cout<<"Iteration AIPLAY " << i <<std::endl;
		Game aux(G);
		Move maux(i,aux.get_turn(), aux);
		Move mret(i,G.get_turn(),G);
		if (maux.is_valid() == OK){
			aux.apply(maux);
			
			//std::cout<<aux<< "eval :" <<evaluate(aux)<<std::endl;
			//std::cout<<"Playing on row number " <<i<<std::endl;
			if (aux.who_win() == G.get_turn()) return mret;
			int score = min(aux,0,4);
			if (score >= best_score){
				column = i;
				best_score = score;
				std::cout<<"Best score: "<<best_score<<" Best col:" <<column<<std::endl;
			}
		}
	} 
std::cout<<column<<std::endl;
Move m(column,G.get_turn(),G);

return m;
	
}

int Minmax::compare_4(Player p, Board_state val_1, Board_state val_2, Board_state val_3, Board_state val_4, int weight){
Board_state p_c = Player_to_Board_state(p);

return (((p_c == val_1) * weight + (val_1 == EMPTY)) * ((p_c == val_2) * weight + (val_2 == EMPTY)) * ((p_c == val_3) * weight + (val_3 == EMPTY)) * ((p_c == val_4) * weight + (val_4 == EMPTY)))* !(val_1 == EMPTY && val_2 == EMPTY && val_3 == EMPTY && val_4 == EMPTY);   

}
int Minmax::evaluate(Game G){
	Player player = G.get_turn();
	if (player == RED) player = GREEN;
	else player = RED;
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





bool Minmax::move_is_win(Game G, int column){

	Player current_player = G.get_turn();
	Game aux(G);
	Move m(column, current_player, aux);
	aux.apply(m);
	if (aux.is_over()) return true;

	return false;
	
}
/*int Minmax::minimax(Game G, int depth, int max_depth){
   Player winner = G.who_win();
   int chip_count = G.total_chips();
   
   if (winner == G.get_turn()){
	return 100;
   }
   else if(chip_count == 42 || depth == max_depth){
   	return 0;
   }
   
	int best_score = -100;
	
	for (int i = 0; i<7;i++){
   	Game aux(G);
   	Move maux(i,aux.get_turn(),aux);
   	if (maux.is_valid() == OK){
   		aux.apply(maux);
   		int score = -minimax(aux,depth+1,max_depth);
   		if(score > best_score){
   	 		best_score = score;
   	 	}
   	 }
   		 }
   	 return best_score;
  }
*/
int Minmax::min(Game G, int depth, int max_depth){
	//std::cout<<"Iteration min " << depth << "   " << max_depth<<std::endl;
	Player winner = G.who_win();
	
	if (winner == G.get_nao()){
		return evaluate(G);
	}
	else if (winner == G.get_human()){
		return -evaluate(G);
	}
	else if (G.total_chips() == 42 || depth == max_depth){
	        //std::cout<<"MIN:MaxDepth"<<std::endl;
		return evaluate(G);
	}
	
	int best_score = (4*4*4*4);
	
	for (int i = 0; i<7;i++){
   	Game aux(G);
   	Move maux(i,aux.get_turn(),aux);
   	if (maux.is_valid() == OK){
   		aux.apply(maux);
   		//score = evaluate(aux);
   		int score = max(aux,depth+1,max_depth);
   		if(score <= best_score){
   	 		best_score = score;
   	 	}
   	 }
   		 }
   	 return best_score;
}

int Minmax::max(Game G, int depth, int max_depth){
	//std::cout<<"Iteration max " << depth << "   " << max_depth<<std::endl;
	Player winner = G.who_win();
	
	if (winner == G.get_human()){
		return -evaluate(G);
	}
	else if (winner == G.get_nao()){
		return evaluate(G);
	}
	else if (G.total_chips() == 42 || depth == max_depth){
		//std::cout<<"Max:MaxDepth"<<std::endl;
		return evaluate(G);
	}
	
	int best_score = -(4*4*4*4);
	
	for (int i = 0; i<7;i++){
		Game aux(G);
	  	Move maux(i,aux.get_turn(),aux);
		if (maux.is_valid() == OK){
	   		aux.apply(maux);
	   		//score = -evaluate(aux);
	   		int score = min(aux,depth+1,max_depth);
	   		if(score >= best_score){
	   	 		best_score = score;
	   	 	}
	   	}
	}
   	 return best_score;
}
