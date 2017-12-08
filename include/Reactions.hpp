#pragma once
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/altrackerproxy.h>
#include <iostream>
#include <cstring>
#include <time.h>
#include <thread>


std::string isRed[] = {
  "OK! I'll be red and you'll be green.",
  "I'm red and you're green.",
  "You can be green and I will be red."
};

std::string isGreen[] = {
  "OK! I'll be green and you'll be red.",
  "I'm green and you're red.",
  "You can be red and I will be green."
};

std::string humanStart[] = {
  "I'll let you start this time...",
  "Go ahead and start the game!",
  "You can start us off."
};

std::string naoStart[] = {
  "I will start, so I can win faster.",
  "I'll make the first move.",
  "Alright, I'll go first."
};

std::string playOnRow[] = {
  "I will play on row number ",
  "I choose row number ",
  "My move is on row ",
  "Let me think... I guess I'll play on row number ",
  "Easy choice for me, row number "
};

std::string afterHumanTurn[] = {
  "Nice move! It's my turn now.",
  "Good choice. Now it's my turn.",
  "Now I'll go.",
  "It's my time to shine!",
  "What do I do now..."
};

std::string afterNaoTurn[] = {
  "What do you think about this move! You're up!",
  "It's your turn now.",
  "You're up next!",
  "Hurry up, your move!",
  "You didn't expect that did you? Keep going!"
};

std::string naoWin[] = {
  "I win! Better luck next time !",
  "I am victorious!",
  "I knew I would win"
};

std::string naoLose[] = {
  "Well played dude! I'll win next time for sure!",
  "Oh well, I lose!",
  "You win! Nicely done"
};

std::string naoDraw[] = {
  "It's a draw! I'm at least as good as you!",
  "We're tied!",
  "I suppose nobody wins!"
};

std::string cheating[] = {
  "Didn't anyone teach you that cheating is bad?",
  "Don't cheat, it's against the three laws of robotics!",
  "I see you're cheating, but I will win anyways!"
  };
  
std::string thinking[] = {
  "Let me think...",
  "Huuuuuuum",
  "Wait a second..."
};

void say_phrase(AL::ALTextToSpeechProxy voiceproxy, const std::string &phrase){

voiceproxy.say(phrase);
}

void do_lookAt(AL::ALTrackerProxy trackerproxy, const std::vector<float> &look, const float speed){

trackerproxy.lookAt(look, 0, speed, false);

}

void nao_is_red(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=isRed[rand() %3];
	voiceproxy.say(phrase);
}

void nao_is_green(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=isGreen[rand() %3];
	voiceproxy.say(phrase);
}

void human_start(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=humanStart[rand() %3];
	voiceproxy.say(phrase);
}


void nao_start(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=naoStart[rand() %3];
	voiceproxy.say(phrase);
}

void play_on_row(int row, AL::ALTextToSpeechProxy voiceproxy){
	std::ostringstream ss;
	ss << playOnRow[rand() %5] << (row+1);
	voiceproxy.say(ss.str());

}

void after_human_turn(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=afterHumanTurn[rand() %5];
	voiceproxy.say(phrase);

}

void after_nao_turn(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=afterNaoTurn[rand() %5];
	voiceproxy.say(phrase);

}

void nao_win(AL::ALTextToSpeechProxy voiceproxy, AL::ALTrackerProxy trackerproxy){
	
	std::vector<float> uparms(3), downarms(3), headdown(3), headup(3);
	uparms = {0.4,1,0.6};
	downarms ={0,0,-1};
	headdown = {1,0,-1};
	headup = {10,0,0};
	const std::string phrase=naoWin[rand() %3];
	std::thread vt(say_phrase,voiceproxy,phrase);
	std::thread vt2(do_lookAt,trackerproxy,headdown,0.4);
	trackerproxy.pointAt("Arms",uparms,0,0.4);
	vt.join();
	vt2.join();
	std::thread vt3(do_lookAt,trackerproxy,headup,0.4);
	trackerproxy.pointAt("Arms",downarms,0,0.4);
	vt3.join();

}

void nao_lose(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=naoLose[rand() %3];
	voiceproxy.say(phrase);

}

void nao_draw(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=naoDraw[rand() %3];
	voiceproxy.say(phrase);

}

void cheat(AL::ALTextToSpeechProxy voiceproxy, AL::ALTrackerProxy trackerproxy){

	std::vector<float> left(3), right(3), center(3);
	right = {1, 0.8, -0.2};
	left = {1, -0.8, -0.2};
	center = {10, 0, 0};
	const std::string phrase=cheating[rand() %3];
	//std::thread vt(lapin);
	std::thread vt(say_phrase,voiceproxy,phrase);
	trackerproxy.lookAt(left, 0, 0.4, false);
	trackerproxy.lookAt(right, 0, 0.4, false);
	trackerproxy.lookAt(left, 0, 0.4, false);
	trackerproxy.lookAt(right, 0, 0.4, false);
	trackerproxy.lookAt(center, 0, 0.4, false);
	vt.join();
		
	
}

void think(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=thinking[rand() %3];
	voiceproxy.say(phrase);

}
