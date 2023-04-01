#include <iostream>
#include <map>
#include <string>
#include <list>
#include <algorithm>
#include <limits>
#include <ios>
#include "movie.h"
#include "customer.h"


using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::list;
using std::map;
using std::pair;
using std::ws;


class RentalStore {
public:
    list<Customer> customers;

    map<string, Movie> inventory;

    void addCustomerAuto(string cust) {
        Customer obj(cust);
        customers.push_back(obj);
    }    

    void addCustomer(string cust) {
        Customer obj(cust);
        customers.push_back(obj);
        cout << endl << "Added New Customer " << cust << endl << endl;
    }    

    void removeCustomer(int ID) {
        bool customerFound = false;
        for (auto customer = customers.begin(); customer != customers.end(); ++customer) {
            if (customer->id == ID) {
                customerFound = true;
                if (customer->moviesRented.empty()) {
                    cout << endl << "Removed " << customer->name << endl << endl;
                    customers.erase(customer);
                    return;
                } else {
                    cout << endl << "Cannot remove a customer with active rentals" << endl << endl;
                    return;
                }
            }
        }
        if (customerFound == false) {
            cout << endl << "No customer found with ID " << ID << endl << endl;
        }
    }


    void addMovieAuto(string Title, string Director, int Copies) {
         Movie obj(Title, Director, Copies);
         inventory.insert(pair<string, Movie>(Title, obj));
    }

    void addMovie(string Title, string Director, int Copies) {
         Movie obj(Title, Director, Copies);
         inventory.insert(pair<string, Movie>(Title, obj));
         cout << endl << "Added New Movie " << obj.title << endl << endl;
    }

    void removeMovie(string Title) {
        bool movieFound = true;
        auto mapMovie = inventory.find(Title); 
        if(mapMovie == inventory.end()) {
            cout << endl << "The movie " << Title << " is not available in our catalog." << endl << endl;
            movieFound = false;
        }
        mapMovie->second.copies = 0;
        mapMovie->second.totalCopies = 0;
        if(movieFound == true)
            cout << endl << "Removed movie " << Title << " from inventory." << endl << endl;
    }

    void rentMovie(string Title, int ID) {
        auto mapMovie = inventory.find(Title);
        if(mapMovie == inventory.end())
            cout << endl << "The movie " << Title << " is not available in our catalog." << endl << endl;
        else if(mapMovie->second.copies == 0) 
            cout << endl << Title << " | No copies available" << endl << endl;
        else {
            bool customerFound = false;  //Initilization 
            auto customer = customers.begin();
            while(customer != customers.end() && !customerFound) {
                if(customer->id == ID) {
                    mapMovie->second.copies--;
                    mapMovie->second.customersRented.push_back(*customer);
                    customer->addRental(mapMovie->second);
                    customerFound = true;
                    cout << endl << customer->name << " has rented " << mapMovie->second.title << endl << endl;
                }
                else {
                    customer++;
                }
            }
            if (!customerFound) {
                cout << endl << "No customer found with ID " << ID << endl << endl;
            }
        }
}

void returnMovie(string Title, int ID) {
    auto mapMovie = inventory.find(Title);
    if(mapMovie == inventory.end()) {
        cout << endl << "The movie " << Title << " is not available in our catalog." << endl << endl;
        return;
    }
    
    bool customerFound = false;
    auto customer = customers.begin();

    while(customer != customers.end() && !customerFound) {
        if(customer->id == ID) {
            customerFound = true;
            auto rental = customer->moviesRented.begin();
            while (rental != customer->moviesRented.end()) {
                if (rental->title == Title) {
                    customer->moviesRented.erase(rental);
                    break;
                }
                rental++;
            }
            if (rental == customer->moviesRented.end()) {
                cout << "This customer did not rent the movie " << Title << endl;
            } else {
                mapMovie->second.copies++;
                if(mapMovie->second.totalCopies == 0)
                    mapMovie->second.copies = 0;
                mapMovie->second.customersRented.remove(*customer);
                cout << endl << "Successfully returned movie " << Title << endl << endl;
            }
        }
        else {
            customer++;
        }
    }
    if (!customerFound) {
        cout << "No customer found with ID " << ID << endl;
        }
    }

    void printInventoryMovies() {
        for(auto pair : inventory) {
            cout << pair.first << " | " << pair.second.director << " | " << pair.second.copies << endl;
        }
        cout << endl;
    }

    void printAvailableMovies() {
        for(auto pair : inventory) {
            if(pair.second.copies != 0) {
            cout << "Title: " << pair.first << endl << "Director: " << pair.second.director << endl << "Available Copies: " << pair.second.copies << "/" << pair.second.totalCopies << endl << endl;
            cout << "--------------------------------------" << endl << endl;
            }
        }
        cout << endl;
    }

    void printInventory() {
        for(auto pair : inventory) {
            cout << "Title: " << pair.second.title << endl << "Director: " << pair.second.director << endl << "Available Copies: " << pair.second.copies << "/" << pair.second.totalCopies << endl << endl;
            pair.second.printCustomersRented(pair.second);
            cout << endl << "--------------------------------------" << endl << endl; 
        }
    }

    void printCustomers() {
        for(auto &Customer : customers) {
            cout << Customer.getname() << " - " << Customer.getid() << endl;
        }
        cout << endl;
    }

    void printCustomerRentals() {
        for(auto &Customer : customers) {
            if(!Customer.moviesRented.empty()) {
            cout << Customer.getname() << " - " << Customer.getid() << endl;
            Customer.printRentals();
            cout << endl;
            }
        }
        cout << endl;
    }

    void customerAccount(int ID) {
        bool customerFound = false;
        auto customer = customers.begin();

        while(customer != customers.end() && !customerFound) {
        if(customer->id == ID) {
            system("cls");
            cout << "Customer Account:" << endl;
            customerFound = true;
            cout << customer->getname() << endl;
            cout << customer->getid() << endl <<endl;
            cout << "Customer Rentals: " << endl;
            customer->printRentals();
            }
        customer++;
        }
        if(customer == customers.end() && !customerFound)
            cout << "Customer not found" << endl;
        
    }

};

unsigned int Customer::idcounter = 1000;

int main() {
    RentalStore store;    
    
    store.addCustomerAuto("David Morris");
    store.addCustomerAuto("Austin Morris");
    store.addCustomerAuto("Annabelle Reeves");

    store.addMovieAuto("Memento", "Chrtopher Nolan", 2);
    store.addMovieAuto("Mavka", "Lisova Pisnya", 7);
    store.addMovieAuto("The Lion King", "Rob Minkoff", 4);
    store.addMovieAuto("Kubo and the Two Strings", "Travis Knight", 3);

int userChoice = 0;
while (userChoice != 12) {
    cout << "1.  Rent Movie" << endl;
    cout << "2.  Return Movie" << endl;
    cout << "3.  Print Avilable Movies" << endl;
    cout << "4.  Customer Account" << endl;
    cout << "5.  Add Customer" << endl;
    cout << "6.  Remove Customer" << endl;
    cout << "7.  Print All Customers" << endl;
    cout << "8.  Print Customer Rentals" << endl;
    cout << "9.  Add Movie" << endl;
    cout << "10. Remove Movie" << endl;
    cout << "11. Print Inventory" << endl;
    cout << "12. Exit" << endl << endl;
    cout << "Enter your choice: ";
    cin >> userChoice;
    if(cin.fail()) {
        while(cin.fail()) {
        cout << "Invalid Option" << endl << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Enter your choice: " << endl;
        cin >> userChoice;
        }
    }
    cout << endl;

    if(userChoice == 1) {
        system("cls"); //Rent Movie
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Enter Movie to be rented: " << endl;
        string movieTitle;
        getline(cin >> ws, movieTitle);
            if (movieTitle == "0" || movieTitle == "c" || movieTitle.empty()) {     // This allows the user to cancel
            system("cls");
            continue;
            }
        cout << "Enter Customer ID: " << endl;
        int customerID;
        cin >> customerID;
        if(cin.fail()) {
                while(cin.fail()) {
                    cout << "Invalid ID number" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << endl;
                    cout << "Enter Customer ID: " << endl;
                    cin >> customerID;
                }
        }
            if (customerID == 0) {     // This allows the user to cancel
            system("cls");
            continue;
            }
        store.rentMovie(movieTitle, customerID);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    else if(userChoice == 2) {
        system("cls"); //Return movie
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Enter Movie to be returned: " << endl;
        string movieTitle;
        getline(cin >> ws, movieTitle);
            if (movieTitle == "0" || movieTitle == "c" || movieTitle.empty()) {     // This allows the user to cancel
            system("cls");
            continue;
            }
        cout << "Enter Customer ID: " << endl;
        int customerID;
        cin >> customerID;
        if(cin.fail()) {
                while(cin.fail()) {
                    cout << "Invalid ID number" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << endl;
                    cout << "Enter Customer ID: " << endl;
                    cin >> customerID;
                }
        }
            if (customerID == 0) {     // This allows the user to cancel
            system("cls");
            continue;
            }
        store.returnMovie(movieTitle, customerID);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    else if(userChoice == 3) {
        system("cls"); //Available movies
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        store.printAvailableMovies();
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    else if(userChoice == 4) {
        system("cls"); //Customer Account
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int customerID;
        cout << "Customer ID: ";
        cin >> customerID;
        store.customerAccount(customerID);
        cout << endl << "Press enter to return to menu..." << endl;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getchar();
        system("cls");
    }
    else if(userChoice == 5) {
        system("cls");  //Add Customer
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "New Customer | Name: " << endl;
        string customerName;
        getline(cin >> ws, customerName);
            if (customerName == "0" || customerName == "c" || customerName.empty()) {     // This allows the user to cancel
            system("cls");
            continue;
            }
        store.addCustomer(customerName);
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    else if(userChoice == 6) {
        system("cls"); // Remove Customer
        cout << "Remove Customer" << endl;
        cout << "Customer ID: " << endl;
        int customerID;
        cin >> customerID;
          if(cin.fail()) {
                while(cin.fail()) {
                    cout << "Invalid ID number" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << endl;
                    cout << "Enter Customer ID: " << endl;
                    cin >> customerID;
                }
         }     
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (customerID == 0) {     // This allows the user to cancel
            system("cls");
            continue;
            }
        store.removeCustomer(customerID);
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    else if(userChoice == 7) {
        system("cls"); // Customers
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        store.printCustomers();
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    else if(userChoice == 8) {
        system("cls");  //CustomerRentals
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        store.printCustomerRentals();
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    if(userChoice == 9) {
        system("cls"); //Add Movie
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "New Movie | Name: " << endl;
        string movieName;
        getline(cin >> ws, movieName);
            if (movieName == "0" || movieName == "c" || movieName.empty()) {     // This allows the user to cancel
            system("cls");
            continue;
            }
        cout << "New Movie | Director: " << endl;
        string movieDirector;
        getline(cin >> ws, movieDirector);
            if (movieDirector == "0" || movieDirector == "c" || movieDirector.empty()) {     // This allows the user to cancel
            system("cls");
            continue;
            }
        cout << "New Movie | Copies: " << endl;
        int copies;
        cin >> copies;
            if(cin.fail()) {
                while(cin.fail()) {
                cout << "Invalid Number" << endl << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Enter Copies: " << endl;
                cin >> copies;
                }
            }
            if (copies == 0) {     // This allows the user to cancel
            system("cls");
            continue;
            }
            if (copies < 0) {   // Handles negative input error
                while(copies < 0) {
                cout << "Invalid Number" << endl << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Enter Copies: " << endl;
                cin >> copies;
                }
            }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        store.addMovie(movieName, movieDirector, copies);
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    if(userChoice == 10) {
        system("cls"); //Remove Movie
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Remove Movie: " << endl;
        string movieTitle;
        getline(cin >> ws, movieTitle);
            if (movieTitle == "0" || movieTitle == "c" || movieTitle.empty()) {     // This allows the user to cancel
            system("cls");
            continue;
            }
        store.removeMovie(movieTitle);
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    else if(userChoice == 11) {
        system("cls"); //Iventory
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        store.printInventory();
        cout << "Press enter to return to menu..." << endl;
        getchar();
        system("cls");
    }
    else if(userChoice == 12) {
        break;
    }
    else if(userChoice < 0 || userChoice > 11)
        cout << "Invalid Option" << endl << endl;
    }
}



/*  Project: Movie Rental Store

    You are tasked with creating a movie rental store program. The program should allow users to add movies to the store's inventory, 
    rent movies, and return movies. The movies in the inventory should be stored in a map with the movie title as the key and a list 
    of available copies as the value. The program should also keep track of the customers who have rented movies, and the movies that 
    they have rented.

    Here are the requirements for the program:

    1.The program should allow users to add movies to the inventory by specifying 
    the title, director, and number of copies. (check)

    2.The program should allow users to rent a movie by specifying the movie title
    and their name. If the movie is available, the program should mark the movie
    as rented and add the customer to the list of customers who have rented the movie. (check)

    3.The program should allow users to return a movie by specifying the movie title 
    and their name. If the customer has rented the movie, the program should mark
    the movie as available and remove the customer from the list of customers who
    have rented the movie. (check)

    4.The program should display the inventory of movies, including the title, director, 
    number of available copies, and the list of customers who have rented each movie. (check)

    5.The program should display the list of customers who have rented movies, along with 
    the list of movies that they have rented. (check)
    
    Class: Movie

    Variables:
        Title (a string that stores the title of the movie)
        Director (a string that stores the director of the movie)
        Copies (an integer that stores the number of available copies of the movie)
        Customers (a list of strings that stores the names of the customers who have rented the movie)

    Class: RentalStore

    Variables:
        Inventory (a map that maps the title of a movie to a Movie object)
    Functions:
        add_movie(title, director, copies) - adds a movie to the inventory with the specified title, director, and number of copies.
        rent_movie(title, customer) - rents a movie with the specified title to the customer if it is available.
        return_movie(title, customer) - returns a movie with the specified title if it was rented by the customer.
        display_inventory() - displays the inventory of movies, including the title, director, number of available copies, and the list of customers who have rented each movie.
        display_customers() - displays the list of customers who have rented movies, along with the list of movies that they have rented. */

//Ignore last space on input
//Cant rent multiple copies

//Future versions
//Multiple movie checkout, shopping cart
//Allow purchase of movie
//Loyalty rewards program
//Due date, late fees, cost at rental

//Map Data type
//Overloading operators
//Pointers, entire playlist
//Header files
//Exception Handling

//g++ movierental.cpp customer.cpp movie.cpp -o movierental
