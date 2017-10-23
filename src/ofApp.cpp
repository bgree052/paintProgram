#include "ofApp.h"
#include <iostream>

int colourHolder[3] = { 0, 0, 0 };
ofRectangle squareDrawer(10, 10, 100, 40);
ofRectangle paintDrawer(10 + squareDrawer.x + squareDrawer.width, 10, 50, 40);
ofRectangle brushChanger(10 + paintDrawer.x + paintDrawer.width, 10, 110, 40);
ofRectangle eraserButton(10 + brushChanger.x + brushChanger.width, 10, 50, 40);

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);
	ofSetBackgroundColor(199);
	buttonNo = 0;
	state = 0;
	xHolder = 0;
	yHolder = 0;
	widthHolder = 0;
	heightHolder = 0;
	brushType = true;
	brushShape = true;
}

//--------------------------------------------------------------
void ofApp::update() {
	ofSetColor(colourHolder[0],colourHolder[1],colourHolder[2]);
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofNoFill();
	ofDrawRectangle(squareDrawer);
	ofDrawRectangle(paintDrawer);
	ofDrawRectangle(brushChanger);
	ofDrawRectangle(eraserButton);

	ofFill();
	drawSquare();
	drawPaint();

	ofSetColor(0);
	ofDrawBitmapString("Draw Square", squareDrawer.x + 5, squareDrawer.y + squareDrawer.height / 2);
	ofDrawBitmapString("Paint", paintDrawer.x + 5, paintDrawer.y + paintDrawer.height / 2);
	ofDrawBitmapString("Change Brush", brushChanger.x + 5, brushChanger.y + brushChanger.height / 2);
	ofDrawBitmapString("Eraser", eraserButton.x + 5, eraserButton.y + eraserButton.height / 2);

	ofDrawBitmapString("Press: Up Arrow to change brush shapes", 5, 550);
	ofDrawBitmapString("Press: r,g,y,b,w to change colours", 5, 570);
	ofDrawBitmapString("Press F to stop painting", 5, 590);
}


void ofApp::eraser(){

}

/*This function is for drawing the shapes at the mouse point to create a brush effect, there are also 2 
different brush types withing that are selectable via a button*/
void ofApp::drawPaint() {
	if (buttonNo == 2 && state == 2) {
		if (brushType==true) {
			if (brushShape == true) {
				ofDrawEllipse(mouseX, mouseY, 8, 8);
			}
			else if (brushShape == false) {
				ofDrawRectangle(mouseX, mouseY, 8, 8);
			}
		}
		else if (brushType==false) {
			if (brushShape == true) {
				ofDrawEllipse(mouseX + ofRandom(-10, 10), mouseY + ofRandom(-10, 10), 3, 3);
			}
			else if (brushShape == false) {
				ofDrawRectangle(mouseX + ofRandom(-10, 10), mouseY + ofRandom(-10, 10), 3, 3);
			}
		}
		//ofDrawEllipse(mouseX, mouseY, 20, 20);
	}
}

/*This function is for drawing the square once the perameters are met, which are that the square button has been clicked 
and the user has then clicked twice more on the screen*/
void ofApp::drawSquare() {
	//if (buttonNo == 1 && state == 2) {
	//	ofDrawRectangle(xHolder, yHolder, mouseX - xHolder, mouseY - yHolder); //outline the square before drawing it
	//	ofDrawBitmapString("Drawing Square", 5, 758);
	//}
	if (buttonNo == 1 && state == 3) {
		ofDrawRectangle(xHolder, yHolder, widthHolder, heightHolder);
		buttonNo = 0; state = 0;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	//SQUARE DRAWING
	//This Code then works out the size of the rectangle from where you previously clicked and where you clicked just now
	if (buttonNo == 1 && state == 2) {
		widthHolder = x - xHolder;
		heightHolder = y - yHolder;
		state = 3;
		cout << "Passed 3 ";
	}

	//This part checks you have then clicked elsewhere on the screen and stores that point in a variable
	if (buttonNo == 1 && state == 1) {
		xHolder = x;
		yHolder = y;
		state = 2;
		cout << "Passed 2 ";
	}

	//This part of the code checks the button has been clicked
	if (x >= squareDrawer.x &&
		x <= squareDrawer.x + squareDrawer.width &&
		y >= squareDrawer.y &&
		y <= squareDrawer.y + squareDrawer.height) {
		cout << "Passed Square ";
		buttonNo = 1;
		state = 1;
	}

	//PAINTING
	if (buttonNo == 2 && state == 2) {
		buttonNo = 0;
		state = 0;
	}
	if (buttonNo == 2 && state == 1) {
		state = 2;
	}

	if (x >= paintDrawer.x &&
		x <= paintDrawer.x + paintDrawer.width &&
		y >= paintDrawer.y &&
		y <= paintDrawer.y + paintDrawer.height) {
		cout << "Paint Passed ";
		buttonNo = 2;
		state = 1;
	}

	//Brush Type
	if (x >= brushChanger.x &&
		x <= brushChanger.x + brushChanger.width &&
		y >= brushChanger.y &&
		y <= brushChanger.y + brushChanger.height) {
		cout << "Passed Brush ";
		brushType = !brushType;
		cout << brushType ;
		state = 1;
	}

	if (x >= eraserButton.x &&
		x <= eraserButton.x + eraserButton.width &&
		y >= eraserButton.y &&
		y <= eraserButton.y + eraserButton.height) {

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//cout << key ;
	if (key == 'f' && buttonNo == 2) {
		buttonNo = 0;
		//state = 0;
	}
	if (key == 'r') {
		colourHolder[0] = 255;
		colourHolder[1] = 0;
		colourHolder[2] = 0;
	}
	if (key == 'g') {
		colourHolder[0] = 0;
		colourHolder[1] = 255;
		colourHolder[2] = 0;
	}
	if (key == 'b') {
		colourHolder[0] = 0;
		colourHolder[1] = 0;
		colourHolder[2] = 0;
	}
	if (key == 'y') {
		colourHolder[0] = 255;
		colourHolder[1] = 255;
		colourHolder[2] = 0;
	}
	if (key == 'w') {
		colourHolder[0] = 255;
		colourHolder[1] = 255;
		colourHolder[2] = 255;
	}
	if (key == 357) {
		brushShape = !brushShape;
		//cout << "PRESSED";
	}

	//bool reseter = true;
	//if (key == 'r' && reseter==true) {
	//	cout << "R LOGGED";
	//	ofSetBackgroundAuto(true);
	//	reseter = false;
	//}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}