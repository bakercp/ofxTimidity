    #include "ofApp.h"


void ofApp::setup()
{
    int size = 75;
    int margin = 10;
    int x = 10;
    int y = 10;
    
    ofDirectory dir("");

    // We use the gz extension, because we can play .mid.gz files.
    // Not required, it just saves space if you didn't really want MIDI files on
    // your hard drive in the first place, but you have to for a project.
    dir.allowExt("gz");
    for (auto& file: dir.getFiles())
    {
        players.push_back(ofx::Timidity::Player(file.getAbsolutePath()));
        rectangles.push_back(ofRectangle(x, y, size, size));

        if (x + size + margin >=  ofGetWidth())
        {
            x = margin;
            y += (size + margin);
        }
        else
        {
            x += (size + margin);
        }
    }

    ofBackground(0);
}


void ofApp::draw()
{
    for (std::size_t i = 0; i < players.size(); ++i)
    {
        if (players[i].isPlaying())
        {
            ofSetColor(ofColor::green);
        }
        else
        {
            ofSetColor(ofColor::red);
        }

        ofDrawRectangle(rectangles[i]);
    }
}


void ofApp::mousePressed(int x, int y, int button)
{
    for (std::size_t i = 0; i < players.size(); ++i)
    {
        if (rectangles[i].inside(x, y))
        {
            if (players[i].isPlaying())
            {
                players[i].stop();
            }
            else
            {
                players[i].play();
            }
        }
    }
}
