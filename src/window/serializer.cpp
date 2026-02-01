
#include "window/serializer.h"

#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <fstream>

void WindowSerializer::Serialize(const SerializedWindowData &data) {

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Title" << YAML::Value << data.Title;
    out << YAML::Key << "Width" << YAML::Value << data.Width;
    out << YAML::Key << "Height" << YAML::Value << data.Height;
    out << YAML::Key << "PosX" << YAML::Value << data.PosX;
    out << YAML::Key << "PosY" << YAML::Value << data.PosY;

    if (!std::filesystem::exists(".cache/win/"))
        std::filesystem::create_directories(".cache/win/");

    std::ofstream fout(".cache/win/config.yaml");
    fout << out.c_str();
    fout.close();
}


SerializedWindowData WindowSerializer::Deserialize() {
    YAML::Node data;
    try	{ data = YAML::LoadFile(".cache/win/config.yaml"); }
    catch (YAML::ParserException ex)
    {
        printf("ERROR: %s", ex.what());
        return {};
    }
    SerializedWindowData out;

    out.Title = data["Title"].as<std::string>();
    out.Width = data["Width"].as<uint32_t>();
    out.Height = data["Height"].as<uint32_t>();
    out.PosX = data["PosX"].as<int32_t>();
    out.PosY = data["PosY"].as<int32_t>();

    return out;
}
