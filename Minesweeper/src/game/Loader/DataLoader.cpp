#include "DataLoader.h"

#include <iostream>
#include <vector>

namespace fs = std::filesystem;

DataLoader::DataLoader(std::string_view path)
{
    std::vector<fs::path> pathFiles;
    for (auto& p : fs::recursive_directory_iterator(path)) {
        std::cout << p.path() << '\n';
        pathFiles.emplace_back(p.path());
    }
    std::map<std::string, std::map<std::string, bool>> formats = 
    { 
        {"image",{ {".png",1},{".jpg",1},{".bmp",1} }},
        {"fonts",{ {".ttf",1} }},
    };
    for (const auto& it : pathFiles) {
        for (auto& [type, extensions] : formats) {
            auto currentExtension = it.extension().string();
            if (extensions[currentExtension]){
                auto nameFile = it.stem().string();
                if (type == "image") {
                    textureStorage[nameFile].loadFromFile(it.string());
                }
                else if (type == "fonts") {
                    fontStorage[nameFile].loadFromFile(it.string());
                }
            }
        }
    }
}

std::unique_ptr<sf::Texture> DataLoader::getTexture(std::string_view name) const
{
    if (auto it = textureStorage.find(name.data()); it != textureStorage.end()) {
        
        return std::make_unique<sf::Texture>(it->second);
    }
    return std::make_unique<sf::Texture>();
}

std::unique_ptr<sf::Font> DataLoader::getFont(std::string_view name) const
{
    if (auto it = fontStorage.find(name.data()); it != fontStorage.end()) {
        return std::make_unique<sf::Font>(it->second);
    }
    return std::make_unique<sf::Font>();
}
