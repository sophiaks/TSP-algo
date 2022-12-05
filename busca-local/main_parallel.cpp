#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <random>
#include <iomanip>
#include <chrono>
#include <omp.h>

using namespace std;
struct city {
    int id;
    double x;
    double y;
};

// Creates a vector from stdin and number of cities
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

// Given a vector of cities, calculates the whole tour, from the first to the last item of the vector - returning to the initial point
double calc_tour(vector<city> cities) {
    double tour;
    int last_index = ((int) cities.size()) - 1; 
    for (int i = 0; i < last_index; i++) {
        tour += euclidean(cities[i], cities[i+1]);
    }
    // We have to return to the initial city
    tour +=  euclidean(cities[last_index], cities[0]);
    return tour;
}

int isPathShorter(vector<city> path_prev, vector<city> path_current) {
    if (calc_tour(path_current) < calc_tour(path_prev)) return 1;
    else return 0;
}

void print_err_output(vector<city> path, double tour) {
    cerr << tour << " ";
    for (int i = 0; i < (int) path.size(); i++) cerr << path[i].id << " ";
    cerr << "\n";
}

void print_test_err(vector<city> path, double tour) {
    cerr << tour << " " << 0 << endl;
    for (int i = 0; i < (int) path.size(); i++)  cout << path[i].id << " ";
    cout << endl;
}

void print_output_new(vector<city> path, double tour) {
    cout << tour << " " << 0 << '\n';
    for (int i = 0; i < (int) path.size(); i++)  cout << path[i].id << " ";
    cout << endl;
}

void parallel_random_search(vector<city> cities, int n_cities) {
    std::default_random_engine rng(123);
    // Copying setting the best_tour initially as the original vector of cities
    vector<city> best_tour = cities;

    // Last index is size - 1 because we access index + 1 
    int last_index = (int) cities.size() - 1;

    #pragma omp parallel num_threads(20)
    {   
        cout << "We are " << omp_get_num_threads();
        #pragma omp for
        for (int i = 0; i < 10*n_cities; i++) {
        vector<city> best_tour_inner = cities;
        
        // Shuffling vector
        // From https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
        std::shuffle(std::begin(best_tour_inner), std::end(best_tour_inner), rng);

        vector<city> swapped = best_tour_inner;

        for (int i = 0; i < last_index; i++) {     
            swap(swapped[i], swapped[i+1]);
            if (isPathShorter(best_tour_inner, swapped)) best_tour_inner = swapped;
        }

        if (isPathShorter(best_tour, best_tour_inner)) best_tour = best_tour_inner;
        
        //print_output_new(best_tour, calc_tour(best_tour));

        // For some reason, tests work with different outputs (stderr with format > tour index1 index2 ...)
        //rint_err_output(best_tour, calc_tour(best_tour));
        }
    }
    }

int main(int argc, char *argv[]) {
    //std::cout << std::setprecision(2);
    int n_cities;
    cin >> n_cities;
    vector<city> cities_vec = createVector(n_cities);
    auto begin_random = std::chrono::high_resolution_clock::now();
    parallel_random_search(cities_vec, n_cities);
    auto end_random = std::chrono::high_resolution_clock::now();
    auto elapsed_random = std::chrono::duration_cast<std::chrono::nanoseconds>(end_random - begin_random);
    cout << "Parallel time: " << elapsed_random.count() * 1e-9 << endl;
}