#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
class Flight {
public:
    std::string Flight_Number;
    std::string Start_Place;
    std::string Final_Place;
    std::string Date;
    std::string Go_Time;
    std::string End_Time;
    std::string Air_Type;
    double Price;

    Flight(const std::string& flightNumber,
           const std::string& startPlace,
           const std::string& finalPlace,
           const std::string& date,
           const std::string& goTime,
           const std::string& endTime,
           const std::string& airType,
           double price)
        : Flight_Number(flightNumber),
          Start_Place(startPlace),
          Final_Place(finalPlace),
          Date(date),
          Go_Time(goTime),
          End_Time(endTime),
          Air_Type(airType),
          Price(price) {
    }
};

bool readFlightsFromFile(const std::string& filename, std::vector<Flight>& flights) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string flightNumber, startPlace, finalPlace, date, goTime, endTime, airType, priceStr;

        if (ss >> flightNumber >> startPlace >> finalPlace >> date >> goTime >> endTime >> airType >> priceStr) {
            double price = std::stod(priceStr);
            flights.emplace_back(flightNumber, startPlace, finalPlace, date, goTime, endTime, airType, price);
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    file.close();
    return true;
}

void displayMenu() {
    std::cout << "Flight Information System" << std::endl;
    std::cout << "1. Display all flights" << std::endl;
    std::cout << "2. Search for a flight by Flight Number" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

void displayFlight(const Flight& flight) {
    std::cout << "Flight Number: " << flight.Flight_Number << std::endl;
    std::cout << "Start Place: " << flight.Start_Place << std::endl;
    std::cout << "Final Place: " << flight.Final_Place << std::endl;
    std::cout << "Date: " << flight.Date << std::endl;
    std::cout << "Go Time: " << flight.Go_Time << std::endl;
    std::cout << "End Time: " << flight.End_Time << std::endl;
    std::cout << "Air Type: " << flight.Air_Type << std::endl;
    std::cout << "Price: " << flight.Price << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

int main() {
    std::vector<Flight> flights;

    // 从文件中读取航班信息
    if (readFlightsFromFile("input.txt", flights)) {
        // 对航班进行排序
        std::sort(flights.begin(), flights.end(), [](const Flight& a, const Flight& b) {
            return a.Flight_Number < b.Flight_Number;
        });
        int choice;
        do {
            system("cls");
            displayMenu();
            std::cout << "Enter your choice: ";
            while (!(std::cin >> choice)) {
                std::cin.clear(); // clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            }
            switch (choice) {
                case 1:
                {
                    for (const auto& flight : flights) {
                        displayFlight(flight);
                    }
                    std::cout<<"found ok.type any key to return"<<std::endl;
                    int x;std::cin>>x;
                    std::cin.ignore();
                    break;
                }
                case 2:
                {
                    std::string targetFlightNumber;
                    std::cout << "Enter the Flight Number to search: ";
                    std::cin >> targetFlightNumber;
                    // 使用二分查找查找航班
                    auto it = std::lower_bound(flights.begin(), flights.end(), Flight(targetFlightNumber, "", "", "", "", "", "", 0),
                                               [](const Flight& a, const Flight& b) {
                                                   return a.Flight_Number < b.Flight_Number;
                                               });
                    if (it != flights.end() && it->Flight_Number == targetFlightNumber) {
                        std::cout << "Flight found:" << std::endl;
                        displayFlight(*it);
                    } else {
                        std::cout << "Flight not found." << std::endl;
                    }

                    std::cout<<"found ok.type any key to return"<<std::endl;
                    int x;std::cin>>x;
                    std::cin.ignore();
                    break;
                }
                case 3:
                    std::cout << "Exiting the program. Goodbye!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please enter a valid option." << std::endl;
            }
        } while (choice!=3);
    }

    return 0;
}
