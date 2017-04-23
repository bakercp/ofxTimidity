#include "ofApp.h"


int main()
{
    ofSetupOpenGL(85 * 10 + 10, 85 * 10 + 10, OF_WINDOW);
    return ofRunApp(std::make_shared<ofApp>());
}
