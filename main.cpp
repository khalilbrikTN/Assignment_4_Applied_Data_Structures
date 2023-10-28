#include <iostream>
using namespace std;
#include "BST.h"
#include "dict.h"

float distance (string city_1, string city_2);

int main() {
    dict* myDict = new dict();
    myDict->fill_data("data.csv");

    cout<<"Welcome to our Data Base!" <<endl;
    cout<<"Could you please enter the number of the operation you want to perform: "<<endl;
    cout<<"1. Search a city"<<endl;
    cout<<"2. Distance between 2 cities"<<endl;
    cout<<"3. Add a city"<<endl;
    cout<<"4. List all cities"<<endl;


    int choice;
    cout<<"Choice(enter '0' to quit) : ";
    cin>>choice;

    while (choice!=0)
    {
        switch (choice) {
            case 1: {
                cout << "Could you please enter the city name: ";
                string city_name;
                cin >> city_name;
                myDict->print_city_info(city_name);
                break;
            }
            case 2: {
                myDict->distance();
                break;
            }
            case 3: {
                myDict->add_city();
                break;
            }
            case 4: {
                myDict->printAllCities(myDict->get_tree()->get_root());
                break;
            }
            default:
            {
                cout << "No valid choice was specified!" << endl;
                break;
            }
        }
        cout<<"Choice(enter '/' to quit) : ";
        cin>>choice;
    }




    return 0;
};







