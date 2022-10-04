#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>

using namespace std;
struct city {
    int id;
    double x;
    double y;
};

vector<city> createVector() {
    vector<city> cities;
    int n_cities;
    cin >> n_cities;
    for (int i = 0; i < n_cities; i++) {
        city new_city;
        new_city.id = i;
        cin >> new_city.x;
        cin >> new_city.y;
        cities.push_back(new_city);
    }    
    // Printing vector
    // for (int i = 0; i < (int) cities.size(); i++){
    //     cout << "id: " << cities.at(i).id << "; x: " << cities[i].x << "; y: " << cities[i].y << endl;
    // }  

    return cities;
}

double euclidean(city ct1, city ct2) { 
    return sqrt(pow(ct1.x - ct2.x, 2) + pow(ct1.y - ct2.y, 2));
}

void remove_city(std::vector<city> & cities, int id) {
    cities.erase(
        std::remove_if(cities.begin(), cities.end(), [&](city const & t_city) {
            return t_city.id == id;
        }),
        cities.end());
}

void print_output(vector<int> path, double tour) {
    cout << tour << " " << 0 << "\n";
    for (int i = 0; i < (int) path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;
}


void find_nearest(vector<city> cities) {
    vector<int> path;
    double tour = 0.0;
    double dist;
    double dist_to_nearest;

    // Setting starting point -> id = 0
    city current_city = cities[0];
    city first_city = cities[0];

    city nearest_city;

    // Adding first city to path and removing first city from list of available cities
    path.push_back(current_city.id);
    cities.erase(cities.begin());

    while (!cities.empty()) {

        // Sets the nearest city as the first one in the list of available cities
        nearest_city = cities[0];

        // Iterating over all available cities and getting the nearest one
        for (int next = 0; next < (int) cities.size(); next++) {            

            // Calculating distance between current and next city
            dist = euclidean(current_city, cities[next]);
            dist_to_nearest = euclidean(current_city, nearest_city);

            // If current city is nearer than nearest, substitutes nearest
            if (dist <= dist_to_nearest) {
                nearest_city = cities[next];
            } 
        }
        
        // Distance to reach the nearest city     
        tour += euclidean(current_city, nearest_city);

        // Updating current city
        current_city = nearest_city;

        // Adding to path
        path.push_back(current_city.id);

        // Removing from available cities
        remove_city(cities, current_city.id);
    }
    
    // Distance to go back to starting point (city 0)
    tour += euclidean(first_city, nearest_city);
    print_output(path, tour);
}

int main (int argc, char *argv[]) {

    find_nearest(createVector());
    return 1;
}