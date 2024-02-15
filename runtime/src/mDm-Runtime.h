#ifndef MDM_H
#define MDM_H

// #include <vector>
#include <functional>
#include <any>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include "mDm-AST.h"

struct DataBlock {
    unsigned char dNib; // 4 Bit genutzt, Rest ungenutzt oder für andere Flags
// dNib werden aus data maskiert!
    uint32_t data; // 28 Bit für Daten, restliche Bits für Erweiterungen oder Flags

    DataBlock(unsigned char d, uint32_t dt) : dNib(d), data(dt) {}
};


class dSeqException : public std::exception
{
public:
    dSeqException(const std::string &message) : msg_(message) {}
    const char *what() const noexcept override
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class VirtualMemoryManager {
private:
    std::vector<unsigned char> memory;

public:
    VirtualMemoryManager(size_t initialSize) : memory(initialSize) {}

    // Methoden zum Lesen/Schreiben von Daten
    void writeData(size_t address, uint32_t data);
    uint32_t readData(size_t address);

    // Weitere Verwaltungsmethoden...
};


/*
```mDm
/// example Imports
(A; B),import,ABCname

/// example Variables
_, int, counter
10, int, literal10
"some string", string, shortstring

_,(
/// something here
),inputFunction

inputFunction,(
/// something here
),processingFunction

processingFunction,(
/// something here
),outputFunction

/// a standalone function with unknown input
_,(
/// something here
),standaloneFunction

/// Main Function Block - Initializes and Starts Threads
_,(

/// concated function in an endless loop
outputFunction, while _, _

/// Standalone Function running once, with unknown input and output
standaloneFunction, while 1, _

/// Standalone Function running once, with unknown input and output
_, standaloneFunction, _

/// Standalone Function running unknown cause of unknown processing function, with unknown input
_, _, standaloneFunction

),main
```
*/

class RuntimeEnvironment
{
private:
    std::unordered_map<std::string, std::function<void(std::vector<std::any> &)>> dSeqRegistry;

    std::vector<std::any> parseLine(const std::string &line)
    {
        std::istringstream iss(line);
        std::string token;
        std::string currentToken;
        std::vector<std::any> parsedTokens;

        while (iss >> token)
        {
            // Ignoriere Kommentare
            if (token.find("///") == 0)
            {
                break; // Kommentar gefunden, ignoriere den Rest der Zeile
            }

            for (char ch : line)
            {
                switch (ch)
                {
                case ',':
                case ';':
                case '(':
                case ')':
                case '_':
                case '?':
                case '~':
                case '*':
                    // Füge das aktuelle Token hinzu, wenn es nicht leer ist
                    if (!currentToken.empty())
                    {
                        parsedTokens.push_back(currentToken);
                        currentToken.clear();
                    }
                    // Füge das spezielle Zeichen als eigenes Token hinzu
                    parsedTokens.push_back(std::string(1, ch));
                    break;
                case ' ':
                case '\t':
                    // Ignoriere Leerzeichen, füge das aktuelle Token hinzu, wenn es nicht leer ist
                    /*if (!currentToken.empty())
                    {
                        parsedTokens.push_back(currentToken);
                        currentToken.clear();
                    } */
                    break;
                default:
                    // Akkumuliere das aktuelle Zeichen zum Token
                    currentToken += ch;
                    break;
                }
            }
            // Füge das letzte Token hinzu, wenn es nicht leer ist
            if (!currentToken.empty())
            {
                parsedTokens.push_back(currentToken);
            }
        }
        return parsedTokens;
    }

public:
    void registerdSeq(const std::string &name, std::function<void(std::vector<std::any> &)> process)
    {
        dSeqRegistry[name] = process;
    }

    void executedSeq(const std::string &name, std::vector<std::any> &inputs)
    {
        if (dSeqRegistry.find(name) == dSeqRegistry.end())
        {
            throw dSeqException("Unknown dSeq: " + name);
        }
        dSeqRegistry[name](inputs);
    }

    std::vector<std::any> loaddSeqFromFile(const std::string &filename)
    {
        std::vector<std::any> inputs;
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw dSeqException("Cannot open file: " + filename);
        }

        std::string line;
        std::vector<std::any> notempty;
        while (getline(file, line))
        {
            notempty = parseLine(line);
            if (notempty.capacity() > 0)
            {
                inputs.push_back(notempty);
            }
        }
        return inputs;
    }
};

#endif // MDM_H
