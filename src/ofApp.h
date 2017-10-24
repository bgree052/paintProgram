#pragma once

#include "ofMain.h"
#include <iostream>


class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void drawSquare();
	void drawPaint();
	void eraser();

	int colourHolder[3] = { 0, 0, 0 };

	int buttonNo = 0;
	int state = 0;
	int state2 = 0;
	int xHolder = 0;
	int yHolder = 0;
	int widthHolder = 0;
	int heightHolder = 0;
	int sizeInc = 0;
	bool brushType = true;
	bool brushShape = true;

	ofImage file;
};