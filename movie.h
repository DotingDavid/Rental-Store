#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <map>
#include <string>
#include <list>
#include "customer.h"


using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::list;
using std::map;
using std::pair;

class Customer;

class Movie {
public:
    list<Customer> customersRented;
    string title;
    string director;
    unsigned int copies;
    unsigned int totalCopies;
    Movie();
    Movie(string Title, string Director, int Copies);

    void printCustomersRented(Movie m);

    bool operator==(const Movie &other) const;
};



#endif