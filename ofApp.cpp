#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	ofColor color;
	vector<int> hex_list = { 0xf44336, 0x9C27B0, 0x3F51B5, 0x03A9F4, 0x009688, 0x8BC34A, 0xFFEB3B, 0xFF9800 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->base_color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int radius = 30; radius < 320; radius += 1) {

		ofMesh face, line;
		line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

		int color_index = ofRandom(this->base_color_list.size());

		int start_deg = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0025), 0, 1, -360, 360);
		int deg_len = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.05), 0, 1, -30, 30);

		face.addVertex(glm::vec3());
		face.addColor(ofColor(this->base_color_list[color_index], 64));
		for (int deg = start_deg; deg < start_deg + deg_len; deg++) {

			face.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
			face.addColor(ofColor(this->base_color_list[color_index], 64));

			line.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
			line.addColor(this->base_color_list[color_index]);

			if (deg != start_deg) {

				face.addIndex(0);
				face.addIndex(face.getNumVertices() - 1);
				face.addIndex(face.getNumVertices() - 2);

				line.addIndex(line.getNumVertices() - 1);
				line.addIndex(line.getNumVertices() - 2);
			}
		}

		face.draw();
		line.draw();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}