#include <iostream>
#include <map>
#include <string>
#include <list>
#include "movie.h"
#include "customer.h"

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::list;
using std::map;
using std::pair;


    Movie::Movie(string Title, string Director, int Copies) {
        title = Title;
        director = Director;
        copies = Copies;
        totalCopies = Copies;
    }

    void Movie::printCustomersRented(Movie m) {
        cout << "Customers who have a copy of " << m.title << endl;
        for(auto Customer : customersRented) {
            cout << " - " << Customer.name << " | " << Customer.id << endl;
        }
    }

    bool Movie::operator==(const Movie &other) const{
        if(title == other.title && director == other.director);
            return true;
        return false;
    }

