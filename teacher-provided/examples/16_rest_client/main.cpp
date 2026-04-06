/*
 * Program that reads a cat fact from a REST API and prints it to the console.
 *
 * Note on std::string, std::cin and std::cout :
 * These can't be used with C++ REST SDK because strings are different between platforms.
 * Use utility::string_t, ucin and ucout instead.
 */

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>

#include <iostream>
#include <string>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main()
{
    // String variable to hold the extracted data from the response.
    // utility::string_t is a type alias that automatically uses the right string type for the platform we are on.
    utility::string_t result;

    // Create client object. U() is a macro that converts literal strings to the type used by the library.
    http_client client(U("https://catfact.ninja"));

    // Create a request using the client.
    // We chain on calls to .then() to specify what happens when the response arrives.
    auto request = client.request(methods::GET, uri_builder(U("fact")).to_string())
            // The first lambda is called when the response arrives
            .then([](const http_response &response)
            {
                // Check the HTTP status code. 200 = OK
                if (response.status_code() != 200)
                    throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));

                // Read the response contents and convert it to JSON
                return response.extract_json();
            })
            // The second lambda is called when the JSON is ready
            .then([&result](json::value root)
            {
                // Extract JSON value with key "fact" as string
                result = root[U("fact")].as_string();
            });

    std::cout << "Waiting for the response..." << std::endl;

    // Requests are now running in the background.
    // Wait for them to finish before ending the program.
    request.wait();

    // Request has completed, check if we got a result
    if (!result.empty())
        // Print extracted value. ucout automatically uses the right string type.
        ucout << "Got cat fact: " << result << std::endl;
    else
        ucout << "Failed to get cat fact." << std::endl;

    return 0;
}
