#include <iostream> // Standard input/output stream operations
#include <vector>   // Dynamic array implementation
#include <fstream>  // File stream operations
#include <sstream>  // String stream operations (e.g., converting strings to other types)
#include <limits>   // Include the <limits> header for negative infinity
#include <cmath>    // Using to calculate heigth of the d-ary heap
#include <chrono>

// Define a structure to represent each row of data
struct CityData
{
    std::string cityName;
    int number;

    CityData(const std::string &name, int num) : cityName(name), number(num) {}
};

// Global variable to count comparisons
// int heapComparisonCount = 0;

// Global variables
int d = 2;               // If no d argument in the command then initiale d as 2(binary). This will helps us to calculate parent and child indexes in helper functions
bool isMaxHeap = false;  // Initiale first isMaxHeap as false, after the build_max_heap it will be true. I will use this for checking whether the heap is max or not inside the other functions */
int key;                 // for increase functions
int index;               // for increase and insert functions
CityData keyCity("", 0); // for insert functions

//  Helper function to get the index of the parent
// I design helper functions parametric. If there is no d in argument then d=2 and helper functions acts like in binary tree.
int parent(int i)
{
    return (i - 1) / d;
}

// Function to calculate the index of the child at position j
int child(int i, int j)
{
    return d * i + j;
}

// Helper function to get the index of the left child. Since left and right child are exist only for binary tree this functions does not need d value.
int left(int i)
{
    return 2 * i + 1;
}

// Helper function to get the index of the right child
int right(int i)
{
    return 2 * i + 2; // Assuming right child is at position 2 in a 0-based index
}

// Swap function.
void swap(CityData &a, CityData &b)
{
    CityData temp = a;
    a = b;
    b = temp;
}

// I implement the most of the heap functions from the pseudo code in our textbook.
void max_heapify(std::vector<CityData> &A, int i, int heap_size)
{
    int l = left(i);  // left child
    int r = right(i); // right child
    int largest = i;  // initialize i as largest.

    // heapComparisonCount += 2; // Increment the comparison count for the two conditions below

    if (l < heap_size && A[l].number > A[i].number)
    {
        largest = l;
    }

    if (r < heap_size && A[r].number > A[largest].number)
    {
        largest = r;
    }

    if (largest != i)
    {
        swap(A[i], A[largest]);             // exchange with the largest element
        max_heapify(A, largest, heap_size); // recursively do max_heapify.
    }
}

// Function to build max heap from unordered input array
void build_max_heap(std::vector<CityData> &A)
{
    int heap_size = A.size();

    for (int i = heap_size / 2 - 1; i >= 0; --i)
    {
        max_heapify(A, i, heap_size); // build max heapify in the subtrees until to the root
    }
    isMaxHeap = true;
}

// heap sort for binary tree
void heapsort(std::vector<CityData> &A)
{
    if (!isMaxHeap)
    {
        build_max_heap(A); // if the tree is not in the max heap form, first convert to max heap.
    }

    int heap_size = A.size();

    for (int i = heap_size - 1; i >= 1; --i)
    {
        // Exchange A[0] (max element) with A[i]
        swap(A[0], A[i]);

        // Reduce heap size and maintain max heap property
        heap_size--;
        max_heapify(A, 0, heap_size);
    }
}

// heap sort for binary tree
void max_heap_insert(std::vector<CityData> &A, CityData &key, int heap_size)
{
    if (!isMaxHeap) // If the vector is not already a max heap, build one
    {
        build_max_heap(A);
    }
    // Push a new element to the back of the vector
    // A[heap-size] ← -∞
    A.push_back({"", std::numeric_limits<int>::min()});
    int i = heap_size;
    A[i] = key;
    // Since our vector is a object array, I can not simply call HEAP-INCREASE-KEY function. That's why I write a simple while loop to maintain the max heap property.
    while (i > 0 && A[parent(i)].number < A[i].number)
    {
        swap(A[i], A[parent(i)]);
        i = parent(i);
    }
}

// Extraxt max, remove from the heap and return the max value
CityData heap_extract_max(std::vector<CityData> &A, int heap_size)
{
    if (!isMaxHeap) // If the vector is not already a max heap, build one
    {
        build_max_heap(A);
    }

    if (heap_size < 1)
    {
        std::cerr << "Error: heap underflow" << std::endl;
        throw std::runtime_error("Heap underflow"); // Throw an exception indicating an error
    }

    CityData max = A[0];
    A[0] = A[heap_size - 1];
    heap_size--;

    max_heapify(A, 0, heap_size);
    A.erase(A.begin() + heap_size, A.end());
    return max;
}

// increase specific key in the specific index.
void heap_increase_key(std::vector<CityData> &A, int i, int key)
{
    if (!isMaxHeap) // If the vector is not already a max heap, build one
    {
        build_max_heap(A);
    }

    i--; // to indicates 1 as root.
    if (key < A[i].number)
    {
        std::cerr << "Error: new key is smaller than current key" << std::endl;
        return;
    }

    A[i].number = key;
    while (i > 0 && A[parent(i)].number < A[i].number)
    {
        swap(A[i], A[parent(i)]);
        i = parent(i);
    }
}

// return the max element in the mac heap. Dont remove from the heap.
CityData heap_maximum(std::vector<CityData> &A)
{
    if (!isMaxHeap) // If the vector is not already a max heap, build one
    {
        build_max_heap(A);
    }
    return A[0];
}

// Function to calculate the height of a d-ary heap
int dary_calculate_height(int n, int d)
{
    // Height of a d-ary heap is given by the formula:
    // Formula h = ⌈log_d(n*d - n + 1)⌉ - 1
    double result = log(((n * d - n + 1))) / log((d));
    int h = (ceil(result)) - 1;
    return h;
}

// Function to perform max heapify operation for d-ary heap
void dary_max_heapify(std::vector<CityData> &A, int i, int heap_size)
{
    int largest = i;

    for (int j = 1; j <= d; ++j)
    {
        int childIndex = child(i, j);
        if (childIndex < heap_size && A[childIndex].number > A[largest].number)
        {
            largest = childIndex;
        }
    }

    if (largest != i)
    {
        std::swap(A[i], A[largest]);
        dary_max_heapify(A, largest, heap_size);
    }
}

// Function to build a max heap for d-ary heap
void dary_build_max_heap(std::vector<CityData> &A)
{
    int heap_size = A.size();
    for (int i = heap_size / d; i >= 0; --i)
    {
        dary_max_heapify(A, i, heap_size);
    }
    isMaxHeap = true;
}

// Function to extract the maximum element from d-ary heap. Since out parent and chil funcitons are
CityData dary_extract_max(std::vector<CityData> &A, int &heap_size)
{
    if (!isMaxHeap) // If the vector is not already a max heap, build one
    {
        dary_build_max_heap(A);
    }
    if (heap_size < 1)
    {
        std::cerr << "Error: heap underflow" << std::endl;
        throw std::runtime_error("Heap underflow");
    }

    CityData max = A[0];
    A[0] = A[heap_size - 1];
    heap_size--;

    dary_max_heapify(A, 0, heap_size);
    A.erase(A.begin() + heap_size, A.end());
    return max;
}

/*  !!!
    dary_insert_element and dary_increase_key are special functions. Since my parent functions are parametric using d value,
    these two function have same code structure as max_heap_insert and heap_increase_key.
    !!!
*/

// Function to insert a new element into d-ary heap
void dary_insert_element(std::vector<CityData> &A, CityData key, int &heap_size)
{
    if (!isMaxHeap) // If the vector is not already a max heap, build one
    {
        dary_build_max_heap(A);
    }
    // Push a new element to the back of the vector
    // A[heap-size] ← -∞
    A.push_back({"", std::numeric_limits<int>::min()});
    int i = heap_size;
    A[i] = key;
    // Since our vector is a object array, I can not simply call HEAP-INCREASE-KEY function. That's why I write a simple while loop to maintain the max heap property.
    while (i > 0 && A[parent(i)].number < A[i].number)
    {
        swap(A[i], A[parent(i)]);
        i = parent(i);
    }
}

// Function to increase the key of a specific element in d-ary heap
void dary_increase_key(std::vector<CityData> &A, int i, int key)
{
    if (!isMaxHeap) // If the vector is not already a max heap, build one
    {
        dary_build_max_heap(A);
    }

    i--; // to indicates 1 as root.
    if (key < A[i].number)
    {
        std::cerr << "Error: new key is smaller than current key" << std::endl;
        return;
    }

    A[i].number = key;
    while (i > 0 && A[parent(i)].number < A[i].number)
    {
        swap(A[i], A[parent(i)]);
        i = parent(i);
    }
}

// heap sort for d array
void dary_heapsort(std::vector<CityData> &A)
{
    if (!isMaxHeap)
    {
        dary_build_max_heap(A); // First check is it whether max heap, if it is not convert to max heap.
    }

    int heap_size = A.size();

    for (int i = heap_size - 1; i >= 1; --i)
    {
        // Exchange A[0] (max element) with A[i]
        swap(A[0], A[i]);

        // Reduce heap size and maintain max heap property
        heap_size--;
        dary_max_heapify(A, 0, heap_size);
    }
}

// Read csv file and record to the vector array.
void readCSVFile(const char *filename, std::vector<CityData> &cityDataVector)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::stringstream ss(line);
        std::string cityName;
        int number;

        // Assuming the data is separated by semicolons
        std::getline(ss, cityName, ';');
        ss >> number;

        // Create a CityData object and add it to the vector
        cityDataVector.push_back({cityName, number});
    }

    inputFile.close();
}

// Write vector to the out.csv file
void writeToFile(const std::string &filename, const std::vector<CityData> &cityDataVector)
{
    std::ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        std::cerr << "Error opening the file: " << filename << std::endl;
        return;
    }

    for (const auto &cityData : cityDataVector)
    {
        outputFile << cityData.cityName << ";" << cityData.number << std::endl;
    }

    outputFile.close();
}

// Main function starts here
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> [options]" << std::endl;
        return 1; // Error
    }

    // Vector to hold CityData objects
    std::vector<CityData> cityDataVector;
    // Read CSV file and populate the vector
    readCSVFile(argv[1], cityDataVector);

    for (int i = 4; i < argc; ++i)
    {
        std::string option(argv[i]);

        if (option[0] == 'd')
        {
            // If d option given in the argument
            d = std::stoi(option.substr(1)); // get the number after 'd'
        }
        else if (option[0] == 'i')
        {
            // -i opsiyonu varsa
            index = std::stoi(option.substr(1)); // get the number after 'i'
        }
        else if (option[0] == 'k')
        {
            // -k option
            std::string keyInfo = option.substr(1);

            // Split by '_' character
            size_t firstUnderscore = keyInfo.find('_');
            size_t secondUnderscore = keyInfo.rfind('_');

            if (firstUnderscore != std::string::npos && secondUnderscore != std::string::npos &&
                firstUnderscore < secondUnderscore)
            {
                // k_cityname_population format
                std::string cityName = keyInfo.substr(firstUnderscore + 1, secondUnderscore - firstUnderscore - 1);
                int population = std::stoi(keyInfo.substr(secondUnderscore + 1));

                // Create the cityData struct object
                keyCity = CityData(cityName, population);
            }
            else
            {
                // k_number format
                key = std::stoi(keyInfo.substr(0));
            }
        }

        else
        {
            std::cerr << "Unknown option: " << option << std::endl;
            return 1; // Error
        }
    }

    std::string function(argv[2]);

    if (function == "max_heapify")
    {
        index--; // Adjust the index to start from 1 instead of 0
        max_heapify(cityDataVector, index, cityDataVector.size());
        writeToFile(argv[3], cityDataVector);
    }
    else if (function == "build_max_heap")
    {
        build_max_heap(cityDataVector);
        writeToFile(argv[3], cityDataVector);
    }
    else if (function == "heapsort")
    {
        // Call this before running heap sort
        // heapComparisonCount = 0;

        // Start measuring time
        // auto startTime = std::chrono::high_resolution_clock::now();
        heapsort(cityDataVector);
        // Stop measuring time
        // auto endTime = std::chrono::high_resolution_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        // std::cout << "Time taken by heapsort: " << duration.count() << " ns." << std::endl;

        writeToFile(argv[3], cityDataVector);
    }
    else if (function == "max_heap_insert")
    {
        max_heap_insert(cityDataVector, keyCity, cityDataVector.size());
        writeToFile(argv[3], cityDataVector);
    }
    else if (function == "heap_extract_max")
    {
        CityData max = heap_extract_max(cityDataVector, cityDataVector.size());
        // Append the maximum element to the output file without overwriting it
        writeToFile(argv[3], cityDataVector);
        std::ofstream outputFile(argv[3], std::ios::app);
        outputFile << "Max element is: " << max.cityName << ";" << max.number << std::endl;
    }
    else if (function == "heap_increase_key")
    {
        heap_increase_key(cityDataVector, index, key);
        writeToFile(argv[3], cityDataVector);
    }
    else if (function == "heap_maximum")
    {
        CityData max = heap_maximum(cityDataVector);
        std::ofstream outputFile(argv[3]);
        outputFile << "Max element is: " << max.cityName << ";" << max.number << std::endl;
        outputFile.close();
    }
    else if (function == "dary_calculate_height")
    {
        int height = dary_calculate_height(cityDataVector.size(), d);
        std::ofstream outputFile(argv[3]);
        outputFile << "Height of the " << d << "-ary is: " << height << std::endl;
        outputFile.close();
    }

    else if (function == "dary_extract_max")
    {
        int size = cityDataVector.size();
        CityData max = dary_extract_max(cityDataVector, size);
        // Append the maximum element to the output file without overwriting it
        writeToFile(argv[3], cityDataVector);
        std::ofstream outputFile(argv[3], std::ios::app);
        outputFile << "Max element is: " << max.cityName << ":" << max.number << std::endl;
    }
    else if (function == "dary_insert_element")
    {
        int size = cityDataVector.size();
        dary_insert_element(cityDataVector, keyCity, size);
        writeToFile(argv[3], cityDataVector);
    }
    else if (function == "dary_increase_key")
    {
        dary_increase_key(cityDataVector, index, key);
        writeToFile(argv[3], cityDataVector);
    }
    else if (function == "dary_build_max_heap")
    {
        dary_build_max_heap(cityDataVector);
        writeToFile(argv[3], cityDataVector);
    }
    else if (function == "dary_heapsort")
    {
        dary_heapsort(cityDataVector);
        writeToFile(argv[3], cityDataVector);
    }
    else
    {
        std::cerr << "Unknown function: " << function << std::endl;
        return 1;
    }

    // std::cout << "heapComparisonCount:" << heapComparisonCount << std::endl;

    return 0;
}
