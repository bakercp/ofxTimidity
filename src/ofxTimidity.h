#pragma once


#include "ofMain.h"
#include "Poco/Pipe.h"
#include "Poco/Process.h"
#include "Poco/NullStream.h"
#include "Poco/PipeStream.h"


namespace ofx {
namespace Timidity {


class Player
{
public:
    Player();
    Player(const std::string& path);
    ~Player();

    void load(const std::string& path);

    void play();
    void stop();

    bool isPlaying() const;

    static const std::string DEFAULT_TIMIDITY_PATH;

    static void setTimidityPath(const std::string& path);
    static std::string getTimidityPath();

private:
    /// \brief The global Timidity path.
    static std::string _TIMIDITY_PATH;

    std::string _file;

    /// \brief We use a shared pointer to avoid the hassle of a std::unique_ptr.
    std::shared_ptr<Poco::ProcessHandle> _handle;

    std::shared_ptr<Poco::PipeInputStream> _nos;
    std::shared_ptr<Poco::Pipe> _outPipe;

};


} } // namspace ofx::Timidity
