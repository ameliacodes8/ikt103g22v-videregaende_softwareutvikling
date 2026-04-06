#include <iostream>

#include "rapidcsv/rapidcsv.h"

int main()
{
    // Parser configuration
    rapidcsv::SeparatorParams sp;
    sp.mTrim = true; // Trim white space

    // Construct an object of type Document
    // Uses default label parameters and the separator parameters from above.
    rapidcsv::Document doc("data.csv", rapidcsv::LabelParams(), sp);

    // Read out each row
    for (int i = 0; i < doc.GetRowCount(); i++)
    {
        // Read individual values

        auto last_name = doc.GetCell<std::string>("Last name", i);
        std::cout << "Last name: " << last_name << std::endl;

        auto first_name = doc.GetCell<std::string>("First name", i);
        std::cout << "First name: " << first_name << std::endl;

        auto ssn = doc.GetCell<std::string>("SSN", i);
        std::cout << "SSN: " << ssn << std::endl;

        auto grade = doc.GetCell<std::string>("Grade", i);
        std::cout << "Grade: " << ssn << std::endl;

        // Read related values into a vector

        std::cout << "Scores: ";

        std::vector<float> tests;

        for (int j = 1; j <= 4; j++)
        {
            auto score = doc.GetCell<float>("Test" + std::to_string(j), i);
            tests.push_back(score);
            std::cout << score << ", ";
        }

        std::cout << std::endl << std::endl;
    }

    return 0;
}
