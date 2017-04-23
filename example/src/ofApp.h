#pragma once


#include "ofMain.h"
#include "ofxTimidity.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void draw() override;

    void mousePressed(int x, int y, int button) override;

    std::vector<ofx::Timidity::Player> players;
    std::vector<ofRectangle> rectangles;

};
