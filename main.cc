#include <drogon/drogon.h>

int main()
{
    drogon::app().addListener("0.0.0.0", 80).loadConfigFile("../config.json");
    drogon::app().run();
}
