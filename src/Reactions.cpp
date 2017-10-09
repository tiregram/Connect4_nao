#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>


void nao_is_red(AL::ALTextToSpeechProxy voiceproxy){

const std::string phrase="OK! I'll be red and you'll be green";
voiceproxy.say(phrase);
}

void nao_is_green(AL::ALTextToSpeechProxy voiceproxy){

const std::string phrase="OK! I'll be green and you'll be red";
voiceproxy.say(phrase);
}


/*void play_on_row(int row, AL::ALTextToSpeechProxy voiceproxy){

const std::string phrase="I will play on row number" + row;
voiceproxy.say(phrase);

}*/

void after_human_turn(AL::ALTextToSpeechProxy voiceproxy){

const std::string phrase="Nice move! It's my turn now";
voiceproxy.say(phrase);

}

void after_nao_turn((AL::ALTextToSpeechProxy voiceproxy){

const std::string phrase="What do you think about this move! You're up!";
voiceproxy.say(phrase);

}
