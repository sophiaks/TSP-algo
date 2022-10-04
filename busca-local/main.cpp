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

double calc_tour(vector<city> cities) {
    double tour;
    for (int i = 0; i < (int) cities.size() - 1; i++) {
        tour += euclidean(cities[i], cities[i+1]);
    }
    tour +=  euclidean(cities[0], cities[-1]);
    return tour;
}

void print_output(vector<city> path, double tour) {
    cout << tour << " ";
    for (int i = 0; i < (int) path.size(); i++) {
        cout << path[i].id << " ";
    }
    cout << endl;
}

void print_err_output(vector<city> path, double tour) {
    cerr << tour << " ";
    for (int i = 0; i < (int) path.size(); i++) {
        cerr << path[i].id << " ";
    }
    cerr << "\n";
}


void print_output_new(vector<city> path, double tour) {
    cout << tour << " " << 0 << '\n';

    for (int i = 0; i < (int) path.size(); i++) {
        cout << path[i].id << " ";

    }
    cout << endl;
}

void print_err_output_new(vector<city> path, double tour) {
    cerr << tour << " " << 0 << '\n';

    for (int i = 0; i < (int) path.size(); i++) {
        cerr << path[i].id << " ";

    }
    cerr << endl;
}

void random_search(vector<city> cities, int n_cities) {
    // Setting seed as 10
    std::default_random_engine rng(10);
    vector<city> best_tour = cities;
    for (int i = 0; i < 10*n_cities; i++) {
        // Shuffling vector
        // From https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
        std::shuffle(std::begin(cities), std::end(cities), rng);

        for (int i = 0; i < (int) cities.size() - 1; i++) {
            vector<city> original = cities;
            vector<city> swapped = cities;

            swap(swapped[i], swapped[i+1]);

            if (calc_tour(swapped) < calc_tour(best_tour)) {
                //cout << "Dist swapped is " << calc_tour(swapped) << "; Last best dist is " << calc_tour(best_tour);
                best_tour = swapped;
            }
        }

        print_err_output(best_tour, calc_tour(best_tour));
        print_output_new(best_tour, calc_tour(best_tour));
        
        }
    }

void n2_random_search(vector<city> cities, int n_cities) {
    // Setting seed as 10
    std::default_random_engine rng(10);
    vector<city> best_tour = cities;
    vector<city> not_swapped_outer = cities;

    vector<city> untouched = cities; // Might be redundant
    vector<city> best_tour_inner = cities;
    vector<city> best_tour_outer = cities;
    // First iteration, fixes one number
    for (int j = 0; j < (int) cities.size(); j++) {
        vector<city> not_swapped_inner = cities;
        // Second iteration: swaps fixed number with next one
        for (int k = 0; k < (int) cities.size() - 1; k++) {
            // Swapping
            swap(cities[j], cities[j+1]);
            vector<city> swapped = cities;

            // If swapped is better, changes best tour

            if (calc_tour(swapped) < calc_tour(best_tour_inner)) {
                best_tour_inner = swapped;
            }

        if (calc_tour(best_tour_inner) < calc_tour(best_tour_outer)) {
            best_tour_outer = best_tour_inner;
        }
    }
    //Printing output
    print_err_output(best_tour_outer, calc_tour(best_tour_outer));
    print_output_new(best_tour_outer, calc_tour(best_tour_outer));
}
}


int main(int argc, char *argv[]) {
    int n_cities;
    cin >> n_cities;
    vector<city> cities_vec = createVector(n_cities);
    random_search(cities_vec, n_cities);
}