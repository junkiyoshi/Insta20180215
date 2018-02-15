#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->size = 2;

	this->cap.open("D:\\video\\image9.mp4");
	this->cap_size = cv::Size(1280, 720);
	ofSetFrameRate(this->cap.get(CV_CAP_PROP_FPS));

	this->blend_image.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_COLOR);
	this->blend_frame = cv::Mat(this->blend_image.getHeight(), this->blend_image.getWidth(), CV_MAKETYPE(CV_8UC3, this->blend_image.getPixels().getNumChannels()), this->blend_image.getPixels().getData(), 0);

	for (int i = 0; i < this->number_of_frames; i++) {

		cv::Mat src, mini_src;
		this->cap >> src;
		if (src.empty()) {

			break;
		}
		cv::resize(src, mini_src, this->cap_size);
		cv::cvtColor(mini_src, mini_src, CV_RGB2BGR);

		mini_src.copyTo(this->save_frames[(this->number_of_frames - 1) - i]);

		//if (ofGetFrameNum() < this->number_of_frames) {
		//	for (int i = ofGetFrameNum() - 1; i > 0; i--) {
		//		this->save_frames[i - 1].copyTo(this->save_frames[i]);
		//	}
		//	mini_src.copyTo(this->save_frames[0]);
		//}
		//else {
		//	for (int i = this->number_of_frames - 1; i > 0; i--) {
		//		this->save_frames[i - 1].copyTo(this->save_frames[i]);
		//	}
		//	mini_src.copyTo(this->save_frames[0]);
		//}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->values.clear();

	float x_count = ofGetWidth() / this->size;
	float y_count = ofGetHeight() / this->size;

	for (int y = 0; y < y_count; y++) {

		vector<float> tmp_values;

		for (int x = 0; x < x_count; x++) {

			if (y == 0) {

				float value = ofMap(ofNoise(x * 0.01, ofGetFrameNum() * 0.005), 0, 1, 0, this->number_of_frames);
				tmp_values.push_back(value);
			}
			else {

				float value = 0;
				int count = 0;

				for (int tmp_x = x - 1; tmp_x <= x + 1; tmp_x++) {

					if (tmp_x >= 0 && tmp_x < x_count) {

						value += this->values[y - 1][tmp_x];
						count++;
					}
				}

				if (y >= 2) {

					value += this->values[y - 2][x];
					count++;
				}

				float average = value / count + ofMap(ofNoise(x * 0.03, y * 0.01 - ofGetFrameNum() * 0.05), 0, 1, -0.5, 0.5);
				if (average > this->number_of_frames) {

					average = this->number_of_frames;
				}
				else if (average < 0) {

					average = 0;
				}

				tmp_values.push_back(average);
			}
		}

		this->values.push_back(tmp_values);
	}

	//if (ofGetFrameNum() > this->number_of_frames) {

		for (int y = 0; y < this->blend_frame.rows; y += 1) {

			for (int x = 0; x < this->blend_frame.cols; x += 1) {

				int tmp_x = x / this->size;
				int tmp_y = y / this->size;
				int index = this->values[tmp_y][tmp_x];
				this->blend_frame.at<cv::Vec3b>(y, x) = this->save_frames[index].at<cv::Vec3b>(y, x);
			}
		}

		this->blend_image.update();
	//}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->blend_image.draw(0, 0);
}

//========================================================================
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}