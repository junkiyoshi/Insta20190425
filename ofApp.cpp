#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
	ofSetLineWidth(2);

	auto ico_sphere = ofIcoSpherePrimitive(150, 2);
	this->triangles = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	for (auto& triangle : this->triangles) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.x * 0.0005, avg.y * 0.0005, avg.z + 0.0005, ofGetFrameNum() * 0.005);
		auto tmp_radius = 150.f;
		auto rotate = 0.f;
		if (noise_value >= 0.75) {
		
			tmp_radius += ofMap(noise_value, 0.75, 1, 0, 300);
			rotate = ofMap(noise_value, 0.75, 1, 0, 360 * 3);
		}
		auto tmp_avg = glm::normalize(avg) * tmp_radius;
		
		ofPushMatrix();
		ofTranslate(tmp_avg);
		ofRotateX(rotate);
		ofRotateY(rotate);

		vector<glm::vec3> vertices;
		vector<glm::vec3> fill_vertices;
		for (int j = 0; j < 3; j++) {

			glm::vec3 location = glm::vec3(triangle.getVertex(j).x, triangle.getVertex(j).y, triangle.getVertex(j).z) - avg;
			vertices.push_back(location);
			fill_vertices.push_back(location * 0.99);
		}

		ofFill();
		ofSetColor(239);

		ofBeginShape();
		ofVertices(fill_vertices);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}