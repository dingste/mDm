#include "classes.hpp"

MdmInterpreter::MdmInterpreter(const std::string &filename) : filename_(filename), lastWriteTime_(fs::last_write_time(filename)) {}

void MdmInterpreter::run()
{
    if (!initSDL())
    {
        std::cerr << "SDL Initialization failed." << std::endl;
        return;
    }
    while (running_)
    {
        auto currentWriteTime = fs::last_write_time(filename_);
        if (lastWriteTime_ != currentWriteTime)
        {
            lastWriteTime_ = currentWriteTime;
            parseMdmFile();
            execute();
            displayDStates();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cleanupSDL();
}

void MdmInterpreter::parseMdmFile()
{
    MdmParser parser(".");
    parser.parse(filename_);
    tokens = parser.getTokens();
}

void MdmInterpreter::execute()
{
    // Ausführungslogik hier
}

void MdmInterpreter::displayDStates()
{
    // SDL Rendering-Logik hier
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);
    // Darstellen der dStates
    SDL_RenderPresent(renderer_);
}

bool MdmInterpreter::initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    window_ = SDL_CreateWindow("mDm Interpreter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window_)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void MdmInterpreter::cleanupSDL()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}
