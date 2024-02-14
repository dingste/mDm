#include "mDm-Runtime.h"
#include <memory>

// Einfache Beispieldatei für die Verarbeitung dynamischer dSeqs
void processExampledSeq(std::vector<std::any> &inputs)
{
    // Beispielverarbeitungslogik
    for (auto &input : inputs)
    {
        try
        {
            std::cout << "Processing input: " << std::any_cast<int>(input) << std::endl;
        }
        catch (const std::bad_any_cast &)
        {
            std::cout << "Invalid input type. " << std::any_cast<std::string>(input) << std::endl;
        }
    }
}

int main()
{
    RuntimeEnvironment env;

    // Erstellen eines einfachen dSeqs mit Variablenzuweisung
    // auto dseq = std::make_shared<dSeqException>();
    // dseq->addState(std::make_shared<AssignmentNode>("x", 42));
    // dseq->addState(std::make_shared<VariableNode>("x"));

    // env.registerdSeq("exampledSeq", processExampledSeq);

    try
    {
        // Laden der dSeqs aus einer Datei
        std::vector<std::any> inputSequences = env.loaddSeqFromFile("../src/hello_world.mDm");
        //env.executedSeq("helloworld", inputSequences);
        for (std::any &inputs : inputSequences)
        {
            // jeder inputs ist eine zeile
            //   env.executedSeq("helloworld",inputs);
            if (inputs.has_value())
            {

                for (std::any token : std::any_cast<std::vector<std::any>>(inputs))
                {
                    std::cout << std::any_cast<std::string>(token) << std::endl;
                }
            }
        }

        /*   // Ausführung einer Beispiel-dSeq mit dynamischen Eingaben
   std::vector<std::any> inputs;// = {5, std::string("test")};
   env.executedSeq("exampledSeq", inputs);
   */
    }
    catch (const dSeqException &e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
}
