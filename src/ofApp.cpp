#include "ofApp.h"
#include <iostream>

ofRectangle squareDrawer(10, 10, 100, 40);
ofRectangle paintDrawer(10 + squareDrawer.x + squareDrawer.width, 10, 50, 40);
ofRectangle brushChanger(10 + paintDrawer.x + paintDrawer.width, 10, 110, 40);
ofRectangle eraserButton(10 + brushChanger.x + brushChanger.width, 10, 60, 40);

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);
	ofBackground(199);
}

//--------------------------------------------------------------
void ofApp::update() {
	ofSetColor(colourHolder[0],colourHolder[1],colourHolder[2]);
	//cout << state;
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
	eraser();

	ofSetColor(0);
	ofDrawBitmapString("Draw Square", squareDrawer.x + 5, squareDrawer.y + squareDrawer.height / 2);
	ofDrawBitmapString("Paint", paintDrawer.x + 5, paintDrawer.y + paintDrawer.height / 2);
	ofDrawBitmapString("Change Brush", brushChanger.x + 5, brushChanger.y + brushChanger.height / 2);
	ofDrawBitmapString("Eraser", eraserButton.x + 5, eraserButton.y + eraserButton.height / 2);

	ofDrawBitmapString("Press: 'S' to save your work", 5, 530);
	ofDrawBitmapString("Press: 'Up Arrow' to change brush shapes", 5, 550);
	ofDrawBitmapString("Press: 'R,G,Y,B,W' to change colours", 5, 570);
	ofDrawBitmapString("Press: 'F' to stop painting", 5, 590);
}

//Function to act as an eraser, draws with the same colour as the background
void ofApp::eraser(){
	if (buttonNo==3 && state==2) {
		ofSetColor(199);
		ofDrawEllipse(mouseX, mouseY, 10+sizeInc, 10+sizeInc);
	}
}

/*This function is for drawing the shapes at the mouse point to create a brush effect, there are also 2 
different brush types withing that are selectable via a button*/
void ofApp::drawPaint() {
	if (buttonNo == 2 && state == 2) {
		if (brushType==true) {
			if (brushShape == true) {
				ofDrawEllipse(mouseX, mouseY, 8+sizeInc, 8 + sizeInc);
			}
			else if (brushShape == false) {
				ofDrawRectangle(mouseX, mouseY, 8 + sizeInc, 8 + sizeInc);
			}
		}
		else if (brushType==false) {
			if (brushShape == true) {
				ofDrawEllipse(mouseX + ofRandom(-10, 10), mouseY + ofRandom(-10, 10), 3 + sizeInc, 3 + sizeInc);
			}
			else if (brushShape == false) {
				ofDrawRectangle(mouseX + ofRandom(-10, 10), mouseY + ofRandom(-10, 10), 3 + sizeInc, 3 + sizeInc);
			}
		}
	}
}

/*This function is for drawing the square once the perameters are met, which are that the square button has been clicked 
and the user has then clicked twice more on the screen*/
void ofApp::drawSquare() {
	if (buttonNo == 1 && state == 3) {
		ofDrawRectangle(xHolder, yHolder, widthHolder, heightHolder);
		state = 1;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	//SQUARE DRAWING
	//This Code then works out the size of the rectangle from where you previously clicked and where you clicked just now, and triggers the square to draw
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
	//Stops the painting
	if (buttonNo == 2 && state == 2) {
		//buttonNo = 2;
		state = 1;
		state2 = 1;
		cout << "STOPPED";
	}

	//Starts the painting
	if (buttonNo == 2 && state == 1 && state2 == 0) {
		state = 2;
	}

	state2 = 0; //Used to stop the paint function from continuing to draw even when the stop if is called

	//Checks the button has been pressed
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
		state = 0;
		cout << brushType ;
	}

	//Eraser
	//stops the erasers from being called
	if (buttonNo == 3 && state == 2) {
		state = 1;
		state2 = 1;
	}

	//triggers the eraser to draw
	if (buttonNo == 3 && state == 1 &&state2==0) {
		state = 2;
	}
	state2 = 0; //used to stop the eraser from continuing to draw even when the stop if is called

	//checks the button has been pressed
	if (x >= eraserButton.x &&
		x <= eraserButton.x + eraserButton.width &&
		y >= eraserButton.y &&
		y <= eraserButton.y + eraserButton.height) {
		buttonNo = 3;
		state = 1;
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//cout << key ;

	//Stop Painting
	if (key == 'f' && buttonNo == 2) {
		buttonNo = 0;
		//state = 0;
	}

	//Change Colours
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

	//Up Arrow key, for changing brush shape
	if (key == 357) {
		brushShape = !brushShape;
	}

	if (key == 358) {
		sizeInc++;
		cout << sizeInc;
	}

	if (key == 356 && sizeInc>0) {
		sizeInc--;
		cout << sizeInc;
	}

	//For saving your work
	if (key == 's') {
		file.grabScreen(0, 0, 1024, 600);
		file.save("myFile.png");
	}

	if (key == 'l') {
		file.load("myFile.png");
		cout << "LOADED";
		file.draw(0, 0);
	}
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