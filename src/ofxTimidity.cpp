#include "ofxTimidity.h"
#include "ofConstants.h"
#include "ofLog.h"
#include "ofUtils.h"


namespace ofx {
namespace Timidity {


#if defined(TARGET_OSX)
const std::string Player::DEFAULT_TIMIDITY_PATH = "/usr/local/bin/timidity";
#elif defined(TARGET_LINUX)
const std::string Player::DEFAULT_TIMIDITY_PATH = "/usr/bin/timidity";
#else
// Assume it's on the path.
const std::string Player::DEFAULT_TIMIDITY_PATH = "timidity";
#endif
std::string Player::_TIMIDITY_PATH = Player::DEFAULT_TIMIDITY_PATH;


void Player::setTimidityPath(const std::string& path)
{
    Player::_TIMIDITY_PATH = path;
}


std::string Player::getTimidityPath()
{
    return Player::_TIMIDITY_PATH;
}


Player::Player()
{
}


Player::Player(const std::string& file): _file(file)
{
}


Player::~Player()
{
    stop();
}

    
void Player::load(const std::string& file)
{
    stop();
    _file = file;
}


void Player::play()
{
    if (!isPlaying())
    {
        _outPipe = std::make_shared<Poco::Pipe>();
        _handle = std::make_shared<Poco::ProcessHandle>(Poco::Process::launch(_TIMIDITY_PATH,
                                                                              { ofToDataPath(_file, true) },
                                                                              nullptr,
                                                                              _outPipe.get(),
                                                                              _outPipe.get()
                                                                              ));
        _nos = std::make_shared<Poco::PipeInputStream>(*_outPipe.get());

    }
    else
    {
        ofLogNotice("Player::play") << "Already playing. Stop first.";
    }
}


void Player::stop()
{
    if (_handle)
    {
        Poco::Process::kill(*_handle);
        _handle.reset();
        _outPipe.reset();
        _nos.reset();
    }
}


bool Player::isPlaying() const
{
    return _handle && Poco::Process::isRunning(*_handle.get());
}


} } // namespace ofx::Timidity
