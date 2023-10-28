#ifndef DICT_H
#define DICT_H

#include "BST.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

struct data {
    double longitude;
    double latitude;
    std::string country;
};

class dict {
public:
    dict();
    ~dict();
    BST<struct data, std::string>* get_tree();
    double dmsToRadians(int degrees, int minutes, double seconds);
    double latitudeToRadians(const std::string& latitude);
    double longitudeToRadians(const std::string& longitude);
    void fill_data(std::string file_name);
    void print_city_info(std::string city);
    double distance();
    void add_city(const std::string& file_name);
    void printAllCities(Node<struct data, std::string>* root);

private:
    BST<struct data, std::string>* tree;
};

#endif // DICT_H
