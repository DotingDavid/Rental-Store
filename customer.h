#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <map>
#include <string>
#include <list>
#include "movie.h"

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::list;
using std::map;
using std::pair;

class Movie;

class Customer {
    public:
    unsigned static int idcounter;
    int id;
    string name;
    list<Movie> moviesRented;

    Customer(string Name);

    int getid();

    string getname();

    void addRental(Movie m);

    void removeRental(Movie m);

    void printRentals();

    bool operator==(const Customer &other) const;

    void operator+=(Customer& customer2);
};



#endif