#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <random>
#include <iomanip>
#include <chrono>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/shuffle.h>
#include <thrust/random.h>
#include <thrust/device_ptr.h>

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

__host__ __device__ double euclidean(city ct1, city ct2) { 
    return sqrt(pow(ct1.x - ct2.x, 2) + pow(ct1.y - ct2.y, 2));
}

void print_path(vector<city> cities) {
    for (int i = 0; i < (int) cities.size(); i++) {
        cout << cities[i].id << " ";
    }
    cout << endl;
}

__host__ __device__ double calc_tour(vector<city> cities) {
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

struct random_search {
    city swapped;
    double best_tour_inner;
    thrust::device_vector<city, thrust::device_allocator<city>> all_paths;
    int n_cities;
    random_search(vector<city> all_paths_, int n_cities_) : all_paths(all_paths_), n_cities(n_cities_) {};
    __host__ __device__
    float operator() (const int &index)
    {
    }
};

void sequential_random_search(vector<city> cities, int n_cities) {
    std::default_random_engine rng(10);
    vector<city> best_tour = cities;

    int last_index = (int) cities.size() - 1;

    for (int i = 0; i < 10*n_cities; i++) {
        vector<city> best_tour_inner = cities;
        
        // Shuffling vector
        // From https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
        std::shuffle(std::begin(best_tour_inner), std::end(best_tour_inner), rng);

        vector<city> swapped = best_tour_inner;

        // Swapping vector items one by one
        for (int i = 0; i < last_index; i++) {     
            swap(swapped[i], swapped[i+1]);
            if (isPathShorter(best_tour_inner, swapped)) best_tour_inner = swapped;
        }

        if (isPathShorter(best_tour, best_tour_inner)) best_tour = best_tour_inner;
        
        //print_output_new(best_tour, calc_tour(best_tour));

        // For some reason, tests work with different outputs (stderr with format > tour index1 index2 ...)
        //print_err_output(best_tour, calc_tour(best_tour));
        }
    }

int main(int argc, char *argv[]) {
    thrust::default_random_engine generator(10);

    int n_cities;
    cin >> n_cities;

    vector<city> cities[n_cities];
    vector<city> OutputIterator[10*n_cities];

    // Populating indexes
    int indexes[10*n_cities];
    thrust::sequence(indexes, indexes + 10 * n_cities);
    
    // Number of possibilities is 10*n_cities, just like usual
    long n_possibilities = 10 * n_cities;

    // Creating cities vector from input file
    thrust::host_vector<city> h_cities = createVector(n_cities);

    // Copying to GPU
    thrust::device_vector<city> d_cities = h_cities;

    // All paths
    thrust::device_vector<city> all_paths(n_cities * n_possibilities);

    for (int i = 0; i < n_possibilities; i++) {
        // Copying original vector
        thrust::device_vector<city> d_swapped = d_cities;

        // Shuffle happens inside the GPU
        thrust::shuffle(d_swapped.begin(), d_swapped.end(), generator);

        for (int j = 0; j < n_cities; j++) {
            all_paths[(n_cities * i) + j] = d_swapped[j];
        }
    }

    thrust::device_vector<int> outer_paths(10*n_cities);

    // Supposing the best path is the first one
    float min_dist = calc_tour(outer_paths[0]);

    float min_dist = thrust::reduce(outer_paths.begin(), outer_paths.end(), min_dist, thrust::minimum<float>());
    

    // auto begin_random = std::chrono::high_resolution_clock::now();
    // auto end_random = std::chrono::high_resolution_clock::now();
    // auto elapsed_random = std::chrono::duration_cast<std::chrono::nanoseconds>(end_random - begin_random);
    // cout << "Sequential time: " << elapsed_random.count() * 1e-9 << endl;   
}