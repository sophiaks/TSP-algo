#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <random>

using namespace std;
struct city {
    int id;
    double x;
    double y;
};

vector<city> createVector(int n_cities) {
    vector<city> cities;
    for (int i = 0; i < n_cities; i++) {
        city new_city;
        new_city.id = i;
        cin >> new_city.x;
        cin >> new_city.y;
        cities.push_back(new_city);
    }
    return cities;
}

double euclidean(city ct1, city ct2) { 
    return sqrt(pow(ct1.x - ct2.x, 2) + pow(ct1.y - ct2.y, 2));
}

void print_path(vector<city> cities) {
    for (int i = 0; i < (int) cities.size(); i++) {
        cout << cities[i].id << " ";
    }
    cout << endl;
}

void remove_city(std::vector<city> & cities, int id) {
    cities.erase(
        std::remove_if(cities.begin(), cities.end(), [&](city const & t_city) {
            return t_city.id == id;
        }),
        cities.end());
}

double calc_tour(vector<city> cities) {
    double tour;
    for (int i = 0; i < (int) cities.size() - 1; i++) {
        tour += euclidean(cities[i], cities[i+1]);
    }
    tour +=  euclidean(cities[0], cities[-1]);
    return tour;
}

void print_output_new(vector<city> path, double tour) {
    cout << tour << " " << 0 << '\n';

    for (int i = 0; i < (int) path.size(); i++) {
        cout << path[i].id << " ";

    }
    cout << endl;
}

vector<city> exaustive_search(vector<city> cities_not_visited, vector<city> path, int &n_leaf)
{
    cout << "Called exaustive search" << endl;
    // EXIT CONDITION FOR RECURSION
    if (!cities_not_visited.size()) {
        return path;
    }

    // --- CREATING ALL POSSIBLE PATHS ---- //

    // Vector of all possible paths (vector of vectors)
    vector<vector<city>> possibilities(cities_not_visited.size());

    // While we still have cities to visit
    for (int i = 0; i < (int) cities_not_visited.size(); i++) {
        // Adding city to path (path begins as an empty vector)
        vector<city> permutation = path;
        // Since i starts from 0, we are starting from cities[0] -> id = 0
        permutation.push_back(cities_not_visited[i]);

        // Making a copy of cities and removing the one we already visited
        vector<city> updated_not_visited = cities_not_visited;
        remove_city(updated_not_visited, i);

        // Calling function again with new path and new list of not visited cities
        for (int i = 0; i < (int) cities_not_visited.size(); i++) {
            exaustive_search(updated_not_visited, permutation, n_leaf);
        }
        possibilities.push_back(exaustive_search(updated_not_visited, permutation, n_leaf));
        print_path(possibilities[i]);
    }


    // ---- ITERATING OVER ALL PATHS ---- //


    // Guessing the first path is the best one
    vector<city> best_path = possibilities[0];
    // Calculating the tour
    double best_tour = calc_tour(best_path);

    // Iterating over all the paths
    for (int i = 1; i < (int) possibilities.size(); i++) {
        float tour = calc_tour(possibilities[i]);
        
        if (tour < best_tour) {
            // Updating bests (path and tour)
            best_path = possibilities[i];
            best_tour = tour;
            n_leaf++;
        }
    }

    return best_path;
}


int main(int argc, char *argv[]) {
    int n_cities;
    cin >> n_cities;
    vector<city> cities_vec = createVector(n_cities);
    int n_leaf = 0;
    // Creating empty vector to create paths with recursion
    vector<city> empty_vec;
    #ifdef _OPENMP
        // código específico para multi-core aqui
    #else
        // código específico para sequencia aqui
    #endif 

    vector<city>  best_path = exaustive_search(cities_vec, empty_vec, n_leaf);
    cerr << "num_leaf " << n_leaf << endl;
    print_output_new(best_path, calc_tour(best_path));
}