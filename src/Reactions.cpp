#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>



void play_on_row(int row, AL::ALTextToSpeechProxy voiceproxy){

const std::string phrase="I will play on row number" + row;
voiceproxy.say(phrase);

}
