#include <drogon/drogon.h>

/**
 * Server loop.
 */
int main()
{
    drogon::app().loadConfigFile("../config.json").run();
}
