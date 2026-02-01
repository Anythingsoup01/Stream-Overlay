#pragma once


#include <string>

struct SerializedWindowData {
    std::string Title;
    uint32_t Width, Height;
    int32_t PosX, PosY;
};

class WindowSerializer {
public:
    static void Serialize(const SerializedWindowData& data);
    static SerializedWindowData Deserialize();
};
