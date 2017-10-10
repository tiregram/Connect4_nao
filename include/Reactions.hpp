#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
#include <iostream>
#include <cstring>
#include <time.h>

std::string isRed[] = {
  "OK! I'll be red and you'll be green",
  "I'm red and you're green",
  "You can be green and I will be red"
};

std::string isGreen[] = {
  "OK! I'll be green and you'll be red",
  "I'm green and you're red",
  "You can be red and I will be green"
};

std::string humanStart[] = {
  "I'll let you start this time...",
  "Go ahead and start the game!",
  "You can start us off"
};

std::string naoStart[] = {
  "I will start, so I can win faster",
  "I'll make the first move",
  "Alright, I'll go first"
};

std::string playOnRow[] = {
  "I will play on row number ",
  "I choose row number ",
  "My move is on row "
};

std::string afterHumanTurn[] = {
  "Nice move! It's my turn now",
  "Good choice. Now it's my turn",
  "OK, now I'll go"
};

std::string afterNaoTurn[] = {
  "What do you think about this move! You're up!",
  "OK, it's your turn now.",
  "You're up next!"
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
	ss << playOnRow[rand() %3] << (row+1);
	voiceproxy.say(ss.str());

}

void after_human_turn(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=afterHumanTurn[rand() %3];
	voiceproxy.say(phrase);

}

void after_nao_turn(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=afterNaoTurn[rand() %3];
	voiceproxy.say(phrase);

}

void nao_win(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=naoWin[rand() %3];
	voiceproxy.say(phrase);

}

void nao_lose(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=naoLose[rand() %3];
	voiceproxy.say(phrase);

}

void nao_draw(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=naoDraw[rand() %3];
	voiceproxy.say(phrase);

}
