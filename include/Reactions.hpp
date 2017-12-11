#pragma once
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/altrackerproxy.h>
#include <alproxies/almotionproxy.h>
#include <iostream>
#include <cstring>
#include <time.h>
#include <thread>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>


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
  "Let me think... I guess I'll play on ",
  "Easy choice for me, row ",
  "Can you please play for me on "
};

std::string afterHumanTurn[] = {
  "Nice move! It's my turn now.",
  "Good choice. Now it's my turn.",
  "Now I'll go.",
  "It's my time to shine!",
  "What do I do now...",
  "Exactly what I expected you to do! My turn!",
  "I didn't expect that move, interesting... let's see..."
};

std::string afterNaoTurn[] = {
  "What do you think about this move! You're up!",
  "It's your turn now.",
  "You're up next!",
  "Hurry up, your move!",
  "You didn't expect that did you? Keep going!",
  "Keep going!",
  "Come on human, play"
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
	ss << playOnRow[rand() %6] << (row+1);
	voiceproxy.say(ss.str());

}

void after_human_turn(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=afterHumanTurn[rand() %7];
	voiceproxy.say(phrase);

}

void after_nao_turn(AL::ALTextToSpeechProxy voiceproxy){

	const std::string phrase=afterNaoTurn[rand() %7];
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

void initial_phrase(AL::ALTextToSpeechProxy voiceproxy){
	const std::string phrase = "Hey human, do you want to play a game of connect four with me ?";
	voiceproxy.say(phrase);
}

void open_hand(AL:ALMotionProxy motionproxy, const std::string& hand_name){
	motionproxy.openHand(hand_name);
}

void close_hand(AL:ALMotionProxy motionproxy, const std::string& hand_name){
	motionproxy.closeHand(hand_name);
}

void pointAtColumn(cv::VideoCapture vcap, int column, AL::ALTrackerProxy trackerProxy) {

  const std::string effector = "RArm";
  const std::string calibFile = "nao.txt";
  int markerCount = 2;
  int dictionaryId = 0;
  float markerLength = 0.01; // [m]
  Mat camMatrix, distCoeffs;
  bool readOk = readCameraParameters(calibFile, camMatrix, distCoeffs);
  if(!readOk) {
      cerr << "Invalid camera file" << endl;
      return 0;
  }
  Ptr<aruco::Dictionary> dictionary =
      aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));
  Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
  detectorParams->cornerRefinementMethod = aruco::CORNER_REFINE_SUBPIX; // do corner refinement in markers

  double *p[markerCount];
  while(vcap.grab() && p[0] == NULL && p[1] == NULL) {
    Mat image, imageCopy;
    vcap.retrieve(image);
    vector< double > x(markerCount), y(markerCount), z(markerCount);
    double *p[markerCount];
    for (unsigned int j = 0; j < markerCount; j++) {
        p[j] = &x[j];
    }
    vector< vector< Point2f > > corners, rejected;
    vector< int > ids(markerCount);
    vector< Vec3d > rvecs, tvecs;

    aruco::detectMarkers(image, dictionary, corners, ids, detectorParams, rejected);
    aruco::estimatePoseSingleMarkers(corners, markerLength, camMatrix, distCoeffs, rvecs,
                                     tvecs);
    image.copyTo(imageCopy);
    aruco::drawDetectedMarkers(imageCopy, corners, ids);
    for(unsigned int i = 0; i < ids.size(); i++) {
        x[ids[i]] = tvecs[i][0];
        y[ids[i]] = tvecs[i][1];
        z[ids[i]] = tvecs[i][2];
        aruco::drawAxis(imageCopy, camMatrix, distCoeffs, rvecs[i], tvecs[i],
                        markerLength * 0.5f);
    }
    if(rejected.size() > 0)
        aruco::drawDetectedMarkers(imageCopy, rejected, noArray(), Scalar(100, 0, 255));
    imshow("out", imageCopy);
  }

  float x_total = (float)x[1] - (float)x[0];
  float dx = x_total/8;
  //float v[3] = {(float)z[0], -(float)x[0] - column*dx, -(float)y[0]};
  float v[3] = {(float)z[0], -(float)x[0], -(float)y[0]};
  std::vector<float> vv(&v[0],&v[0]+3);
  trackerProxy.pointAt(effector, vv, 0, 0.2);

  float v[3] = {(float)z[0], -(float)x[1], -(float)y[0]};
  std::vector<float> vv(&v[0],&v[0]+3);
  trackerProxy.pointAt(effector, vv, 0, 0.2);

}

