#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

void readAllStudents() {
    utility::string_t result;
    http_client client(U("http://127.0.0.1:5000"));

    //Creates an object to represent the request
    auto request = client.request(methods::GET, uri_builder(U("students")).to_string())
            //take the object and add .then to the object, we use this to describe what happens when the request is done.
            .then([](const http_response &response)
                  {
                      if (response.status_code() != 200)
                          throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));

                      return response.extract_json();
                  })
            .then([&result](json::value root)
                  {
                      auto DataArray = root.as_array();

                      for (int i = 0; i< DataArray.size(); i++)
                      {
                          auto data = DataArray[i];
                          auto dataObj = data.as_object();

                          ucout << "id: "
                                    << dataObj[U("id")].as_integer()
                                    << ", name: "
                                    << dataObj[U("name")].as_string()
                                    << ", email: "
                                    << dataObj[U("email")].as_string()
                                    << ", year: "
                                    << dataObj[U("year")].as_integer()
                                    << "\n";
                      }
                  });

    request.wait();
}

void getStudentById() {
    utility::string_t id;
    std::cout << "ID: ";
    ucin >> id;
    bool found = false;

    utility::string_t result;
    http_client client(U("http://127.0.0.1:5000"));

    auto request = client.request(methods::GET, uri_builder(U("students")).append_path(id).to_string())
            .then([](const http_response &response)
                  {

                      if (response.status_code() == 404) {
                          std::cout << "Student not found\n";
                      }

                      return response.extract_json();
                  })
            .then([&result](json::value root)
                  {
                        if (root.size() > 1) {
                          auto dataObj = root.as_object();
                          ucout << "id: "
                                << dataObj[U("id")].as_integer()
                                << ", name: "
                                << dataObj[U("name")].as_string()
                                << ", email: "
                                << dataObj[U("email")].as_string()
                                << ", year: "
                                << dataObj[U("year")].as_integer()
                                << "\n";
                        }



                  });

    request.wait();
}

void addStudent() {
    utility::string_t name;
    utility::string_t email;
    int year;

    std::cin.ignore();
    std::cout << "Name: ";
    std::getline(ucin, name);

    std::cout << "E-mail: ";
    std::getline(ucin, email);

    std::cout << "Year: ";
    ucin >> year;

    utility::string_t result;
    http_client client(U("http://127.0.0.1:5000/students/"));

    json::value postData;
    postData[U("name")] = json::value::string(name);
    postData[U("email")] = json::value::string(email);
    postData[U("year")] = json::value::number(year);

    http_request req(methods::POST);
    req.headers().set_content_type(U("application/json"));
    req.set_body(postData);

    auto request = client.request(req)
            .then([](const http_response &response)
                  {
                      if (response.status_code() != 201)
                          throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));

                      return response.extract_json();
                  })
            .then([&result](json::value root)
                  {
                      auto dataObj = root.as_object();

                      ucout << "Added student: id: "
                                 << dataObj[U("id")].as_integer()
                                 << ", name: "
                                 << dataObj[U("name")].as_string()
                                 << ", email: "
                                 << dataObj[U("email")].as_string()
                                 << ", year: "
                                 << dataObj[U("year")].as_integer()
                                 << "\n";
                  });

    request.wait();
}

void deleteStudent() {
    utility::string_t id;
    std::cout << "ID: ";
    ucin >> id;

    http_client client(U("http://127.0.0.1:5000/"));

    http_request req(methods::DEL);
    req.set_request_uri(uri_builder(U("students")).append_path(id).to_string());

    auto request = client.request(req)
            .then([](const http_response &response)
                  {

                      if (response.status_code() == 204)
                          std::cout << "Student was removed successfully\n";

                      if (response.status_code() == 404)
                          std::cout << "Student not found\n";

                      if (response.status_code() != 200 && response.status_code() != 404)
                          throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));

                      return response.extract_json();
                  });
}

void editStudent() {
    int id;
    utility::string_t name;
    utility::string_t email;
    utility::string_t id_str;
    utility::stringstream_t ss;
    int year;

    std::cout << "ID: ";
    ucin >> id;

    ss << id;

    std::cin.ignore();
    std::cout << "Name: ";
    std::getline(ucin, name);

    std::cout << "E-mail: ";
    std::getline(ucin, email);

    std::cout << "Year: ";
    ucin >> year;

    utility::string_t result;
    http_client client(U("http://127.0.0.1:5000/"));

    json::value postData;
    postData[U("id")] = json::value::number(id);
    postData[U("name")] = json::value::string(name);
    postData[U("email")] = json::value::string(email);
    postData[U("year")] = json::value::number(year);

    http_request req(methods::PUT);
    req.set_request_uri(uri_builder(U("students")).append_path(ss.str()).to_string());
    req.headers().set_content_type(U("application/json"));
    req.set_body(postData);

    auto request = client.request(req)
            .then([](const http_response &response)
                  {

                      if (response.status_code() == 200)
                          std::cout << "Student was edited successfully\n";

                      if (response.status_code() == 404)
                          std::cout << "Student not found\n";

                      if (response.status_code() != 200 && response.status_code() != 404)
                          throw std::runtime_error("Request failed: " + std::to_string(response.status_code()));

                      return response.extract_json();
                  })
            .then([&result](json::value root)
                  {
                  });
}

int main()
{
    int choice = 0;

    while (choice != 6) {
        std::cout << "1. Read all students\n"
                  << "2. Get student by id\n"
                  << "3. Add student\n"
                  << "4. Edit student\n"
                  << "5. Remove student\n"
                  << "6. Exit\n";

        std::cin >> choice;

        switch (choice) {
            case 1: readAllStudents(); break;
            case 2: getStudentById(); break;
            case 3: addStudent(); break;
            case 4: editStudent(); break;
            case 5: deleteStudent(); break;
            case 6: break;
            default: break;
        }
    }
}
