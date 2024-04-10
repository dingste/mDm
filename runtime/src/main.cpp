#include "classes.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <mDm File Path>" << std::endl;
        return 1;
    }
    MdmInterpreter interpreter(argv[1]);
    interpreter.run();
    return 0;
}