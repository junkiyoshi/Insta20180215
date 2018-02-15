#pragma once
#include "ofMain.h"
#include "ofFbo.h"

#include "opencv2/opencv.hpp"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	cv::VideoCapture cap;
	cv::Size cap_size;

	static const int number_of_frames = 350;
	cv::Mat save_frames[number_of_frames];

	cv::Mat blend_frame;
	ofImage blend_image;

	int size;
	vector<vector<float>> values;
};