#include "classes.hpp"
#include "deserialize.hpp"
MdmParser::MdmParser(const std::string &rootPath) : rootPath_(rootPath) {}

void MdmParser::parse(const std::string &filepath)
{
    if (importedFiles_.find(filepath) != importedFiles_.end())
    {

        return;
    }
    importedFiles_.insert(filepath);

    // Überprüft, ob der Pfad bereits mit ".mdmD" endet
    std::string fullPath = filepath;
    if (fullPath.size() < 5 || fullPath.substr(fullPath.size() - 5) != ".mdmD")
    {
        fullPath = "../" + filepath;
        fullPath += ".mdmD"; // Fügt ".mdmD" hinzu, falls nicht vorhanden
    }

    std::ifstream file(rootPath_ + "/" + fullPath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << fullPath << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line))
    {
        // Überspringen von Kommentarzeilen
        if (line.size() >= 3 && line.substr(0, 3) == "///")
            continue;
        std::istringstream iss(line);

        std::string token;
        while (iss >> token)
        {
            if (token == "import")
            {
                std::string importPath;
                if (iss >> importPath)
                {
                    parse(importPath); // Rekursives Parsen des Imports
                }
            }
            else
            {
                // Setzen Sie die Zeile wieder zusammen, wenn es kein 'import' war
                std::string restOfLine;
                getline(iss, restOfLine, '\0');                  // Liest den Rest der Zeile
                std::string fullLine = token + " " + restOfLine; // Setzt die Zeile wieder zusammen
                std::istringstream newIss(fullLine);             // Erstellt einen neuen Stream für die weitere Verarbeitung
                processToken(filepath, newIss);
            }
        }
    }
}

const std::unordered_map<std::string, std::vector<std::string>> &MdmParser::getTokens() const
{
    return tokens_;
}

void MdmParser::processToken(const std::string &name, std::istringstream &stream)
{
    T_DSEQ dSeqPart;

    stream >> dSeqPart;
    dSeqPart.dState_PROCESSING = trim(dSeqPart.dState_PROCESSING);

    if (!dSeqPart.dState_PROCESSING.empty())
    {
        tokens_[name].push_back(dSeqPart.dState_PROCESSING);
        stream.clear();
    }
}

std::string MdmParser::trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
