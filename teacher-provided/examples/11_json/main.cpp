#include <iostream>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

int main()
{
    // Open the file as a stream
    std::ifstream ifs("data.json");

    if (!ifs.is_open())
    {
        std::cout << "Error: Failed to open file. Exiting." << std::endl;
        return 1;
    }

    // Convert the stream to the rapidjson stream type
    rapidjson::IStreamWrapper isw(ifs);

    // Create JSON document object
    rapidjson::Document doc;

    // Read the JSON document into memory
    doc.ParseStream(isw);

    // Get the object at the top level of the document
    const auto &object = doc.GetObject();

    // Get object fields
    std::string id = object["id"].GetString();
    std::string type = object["type"].GetString();
    std::string name = object["name"].GetString();
    float price = object["price"].GetFloat();

    // Get array from the top level object
    const auto &batters = object["batters"].GetArray();

    // Iterate each object in the array
    for (const auto &batter: batters)
    {
        // Get fields from each object in the array
        std::string batter_id = batter["id"].GetString();
        std::string batter_type = batter["type"].GetString();
    }

    return 0;
}
