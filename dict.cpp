#include "dict.h"
#include <iostream>

dict::dict() {
    tree = new BST<struct data, string>();
}
dict::~dict() {
    delete tree;
}
BST<struct data, string>* dict::get_tree(){
    return tree;
}
double dict::dmsToRadians(int degrees, int minutes, double seconds) {
    // Convert degrees, minutes, and seconds to a single decimal degree value
    double decimalDegrees = degrees + (minutes / 60.0) + (seconds / 3600.0);

    // Convert decimal degrees to radians
    double radians = decimalDegrees * (M_PI / 180.0);

    return radians;
}

double dict::latitudeToRadians(const std::string& latitude) {
    int lat_degrees, lat_minutes;
    double lat_seconds;

    sscanf(latitude.c_str(), "%d°%d′%lf″", &lat_degrees, &lat_minutes, &lat_seconds);

    // Determine if the latitude is in the northern or southern hemisphere
    double lat_decimalDegrees = lat_degrees + (lat_minutes / 60.0) + (lat_seconds / 3600.0);
    if (latitude.find("S") != std::string::npos) {
        lat_decimalDegrees = -lat_decimalDegrees;
    }

    return dmsToRadians(lat_degrees, lat_minutes, lat_seconds);
}

double dict::longitudeToRadians(const std::string& longitude) {
    int lon_degrees, lon_minutes;
    double lon_seconds;

    sscanf(longitude.c_str(), "%d°%d′%lf″", &lon_degrees, &lon_minutes, &lon_seconds);

    // Determine if the longitude is in the eastern or western hemisphere
    double lon_decimalDegrees = lon_degrees + (lon_minutes / 60.0) + (lon_seconds / 3600.0);
    if (longitude.find("W") != std::string::npos) {
        lon_decimalDegrees = -lon_decimalDegrees;
    }

    return dmsToRadians(lon_degrees, lon_minutes, lon_seconds);
}


void dict::fill_data(string file_name){
    ifstream file;
    file.open(file_name);

    string line;
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            string no, city, lat, lon, country;
            stringstream ss(line);
            getline(ss, no, ',');
            getline(ss, city, ',');
            getline(ss, lat, ',');
            getline(ss, lon, ',');
            getline(ss, country, ',');



            float radian_lat = latitudeToRadians(lat);
            float radian_long = longitudeToRadians(lon);

            struct data city_data = {radian_long, radian_lat, country};

            tree->Insert(city, city_data);
        }
        file.close();
    } else {
        cout << "Unable to open the file" << endl;
    }
};


void dict::print_city_info(string city){
    Node<struct data, string>* searchResult = tree->search(get_tree()->get_root(), city);

    if(searchResult != nullptr) {
        cout << "Data for " <<city<<": "
             << "Latitude: " << searchResult->data.latitude
             << ", Longitude: " << searchResult->data.longitude
             << ", Country: " << searchResult->data.country
             << endl;
    } else {
        cout << city + " not found!" << std::endl;
    }
}

double dict::distance() {
    string city1, city2;
    cout << "Enter the 2 cities to calculate distance!" << endl;
    cout << "City 1: ";
    cin >> city1;
    cout << "City 2: ";
    cin >> city2;

    // Radius of the Earth in kilometers
    const double R = 6371.0;

    // Get data for city1 and city2
    struct data city1_data = tree->search(tree->get_root(), city1)->data;
    struct data city2_data = tree->search(tree->get_root(), city2)->data;

    // Convert latitude and longitude from degrees to radians
    double lat1 = city1_data.latitude;
    double lon1 = city1_data.longitude;
    double lat2 = city2_data.latitude;
    double lon2 = city2_data.longitude;

    // Haversine formula
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2) * std::sin(dlon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    double distance = R * c;

    cout << "The distance between " << city1 << " and " << city2 << " is: " << distance << " kilometers" << endl;

    return distance;
}

void dict::add_city(){
    string city_name, country_name;
    double lon, lat;

    cout<<"Enter the data of the city you want to add: ";
    cout<<"City Name: ";
    cin>>city_name;
    cout<<"Country Name: ";
    cin>>country_name;
    cout<<"Longitude: ";
    cin>>lon;
    cout<<"Latitude: ";
    cin>>lat;

    struct data city_data = {lon, lat, country_name};
    tree->Insert(city_name, city_data);

    cout<<"City added!"<<endl;

}

void dict::printAllCities(Node<struct data, string>* root) {
    if (root == nullptr) {
        return;
    }

    // Recursively print the left subtree
    printAllCities(root->left);

    // Print city name and data
    cout << "City: " << root->key << endl;
    cout << "Latitude (radians): " << root->data.latitude << endl;
    cout << "Longitude (radians): " << root->data.longitude << endl;
    cout << "Country: " << root->data.country << endl;
    cout << "-----------------------" << endl;

    // Recursively print the right subtree
    printAllCities(root->right);
}