#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <SDL2/SDL.h>

#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>


namespace fs = std::filesystem;



class MdmInterpreter
{
public:
    MdmInterpreter(const std::string &filename);
    void run();

private:
    std::string filename_;
    fs::file_time_type lastWriteTime_;
    bool running_ = true;
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    std::unordered_map<std::string, std::vector<std::string>> tokens;

    void parseMdmFile();
    void execute();
    void displayDStates();
    bool initSDL();
    void cleanupSDL();
};

class MdmParser
{
public:
    explicit MdmParser(const std::string &rootPath);
    void parse(const std::string &filepath);
    const std::unordered_map<std::string, std::vector<std::string>> &getTokens() const;
    void processToken(const std::string &name, std::istringstream &stream);

private:
    std::string rootPath_;
    std::unordered_set<std::string> importedFiles_;                    // Verhindert zyklische oder doppelte Imports
    std::unordered_map<std::string, std::vector<std::string>> tokens_; // Speichert Tokens nach Datei
    std::string trim(const std::string &str);
};

#endif