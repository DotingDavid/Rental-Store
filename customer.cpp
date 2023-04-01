#include <iostream>
#include <map>
#include <string>
#include <list>
#include "customer.h"
#include "movierental.cpp"
#include "movie.h"

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::list;
using std::map;
using std::pair;


    Customer::Customer(string Name) {
        id = idcounter++;
        name = Name;
    }

    int Customer::getid() {
        return id;
    }

    string Customer::getname() {
        return name;
    }

    void Customer::addRental(Movie m) {
        moviesRented.push_back(m);
    }

    void Customer::removeRental(Movie m) {
        moviesRented.remove(m);
    }

    void Customer::printRentals() {
        for(auto Movie: moviesRented) {
            cout << Movie.title << endl;
        }
    }

    bool Customer::operator==(const Customer &other) const{
        if(id == other.id && name == other.name);
            return true;
        return false;
    }

    void Customer::operator+=(Customer& customer2) {
        for(auto movie: customer2.moviesRented) {
            this->moviesRented.push_back(movie);
            customer2.moviesRented.remove(movie);
        }
    }
