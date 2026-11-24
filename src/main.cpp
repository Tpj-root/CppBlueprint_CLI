#include "cppforge/app/App.h"
#include "cppforge/cli/Arguments.h"

int main(int argc, char* argv[])
{
    const cppforge::Arguments args(argc, argv);
    cppforge::App app(args);
    return app.run();
}
