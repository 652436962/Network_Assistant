#include "global.h"

std::string getWorkModeString(WorkMode mode)
{
    std::string typeString = "";
    switch (mode)
    {
    case WorkMode::TCP_Server:
        typeString = "TCP Server";
        break;
    case WorkMode::TCP_Client:
        typeString = "TCP Client";
        break;
    case WorkMode::UDP:
        typeString = "UDP";
        break;
    default:
        break;
    }
    return typeString;
}

EncodingEnum encodingUsed = EncodingEnum::UTF8;