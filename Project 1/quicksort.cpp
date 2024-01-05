#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>
#include <chrono>

// Global variable to check if verbose output is required
bool verboseOutput = false;
std::vector<std::string> logEntries;

// Define a structure to represent each row of data
struct CityData
{
    std::string cityName;
    int number;
};

// Global variable to count comparisons
int quicksortComparisonCount = 0;

// Function prototypes
void swap(CityData &a, CityData &b);
void naiveQuickSort(std::vector<CityData> &A, int p, int r, char *type);
void hybridQuickSort(std::vector<CityData> &A, int p, int r, int k, char *type);
void insertionSort(std::vector<CityData> &A, int p, int r);
int partition(std::vector<CityData> &A, int p, int r);
int rPartition(std::vector<CityData> &A, int p, int r);
int mPartition(std::vector<CityData> &A, int p, int r);
void readCSVFile(const char *filename, std::vector<CityData> &cityDataVector);
void writeToFile(const std::string &filename, const std::vector<CityData> &cityDataVector);
void setVerboseOutput(char *arg);
void writePartitionLog(int pivot, const std::vector<CityData> &A, int p, int r);
void writeLogToFile(const std::string &filename);

int main(int argc, char *argv[])
{
    // Quick Sort strategy
    char *type = argv[2];
    // Threshold value k
    char *threshold = argv[3];
    int k = std::stoi(threshold);
    // Set verbose output based on command line argument
    setVerboseOutput(argv[5]);

    // Vector to hold CityData objects
    std::vector<CityData> cityDataVector;

    // Read CSV file and populate the vector
    readCSVFile(argv[1], cityDataVector);

    int p = 0;
    int r = cityDataVector.size() - 1;

    // Start measuring time
    auto startTime = std::chrono::high_resolution_clock::now();

    if (k == 1)
    {
        // Call this before running quicksort
        quicksortComparisonCount = 0;
        // Assuming naiveQuickSort is defined somewhere
        naiveQuickSort(cityDataVector, p, r, type);
    }
    else
    {
        // Assuming hybridQuickSort is defined somewhere
        hybridQuickSort(cityDataVector, p, r, k, type);
    }
    // Stop measuring time
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    std::cout << "Time taken by QuickSort with pivot strategy '" << type << "' and threshold " << k << ": " << duration.count() << " ns." << std::endl;

    // Write sorted data to the output file
    // writeToFile(argv[4], cityDataVector);

    if (verboseOutput)
    {
        writeLogToFile("log.txt");
    }
    std::cout << "quicksortComparisonCount:" << quicksortComparisonCount << std::endl;
    return 0;
}

// Swap function
void swap(CityData &a, CityData &b)
{
    CityData temp = a;
    a = b;
    b = temp;
}

// Naive quicksort function (if k = 1)
void naiveQuickSort(std::vector<CityData> &A, int p, int r, char *type)
{
    int q;
    if (p < r)
    {
        if (*type == 'l')
        {
            q = partition(A, p, r);
        }
        else if (*type == 'r')
        {
            q = rPartition(A, p, r);
        }
        else if (*type == 'm')
        {
            q = mPartition(A, p, r);
        }
        naiveQuickSort(A, p, q - 1, type);
        naiveQuickSort(A, q + 1, r, type);
    }
}

// Hybrid quicksort function (if k > 1)
void hybridQuickSort(std::vector<CityData> &A, int p, int r, int k, char *type)
{
    if ((r - p + 1) > k)
    {
        int q;
        if (p < r)
        {
            if (*type == 'l')
            {
                q = partition(A, p, r);
            }
            else if (*type == 'r')
            {
                q = rPartition(A, p, r);
            }
            else if (*type == 'm')
            {
                q = mPartition(A, p, r);
            }
            hybridQuickSort(A, p, q - 1, k, type);
            hybridQuickSort(A, q + 1, r, k, type);
        }
    }
    else if ((r - p + 1) <= k)
    {
        insertionSort(A, p, r);
    }
}

// Insertipn sort for hybrid implentation
void insertionSort(std::vector<CityData> &A, int p, int r)
{
    for (int j = p; j <= r; j++) // Corrected loop bounds
    {
        CityData key = A[j];
        int i = j - 1;

        // Move elements of A[0..j-1] that are greater than key to one position ahead of their current position
        while (i >= 0 && A[i].number > key.number)
        {
            A[i + 1] = A[i];
            i--;
        }

        A[i + 1] = key; // Place the key at its correct position in the sorted sequence
    }
}

// Partition function
int partition(std::vector<CityData> &A, int p, int r)
{
    int x = A[r].number;
    int i = p - 1;

    for (int j = p; j <= r - 1; ++j)
    {
        quicksortComparisonCount++; // Increment the comparison count
        if (A[j].number <= x)
        {
            i = i + 1;
            swap(A[i], A[j]);
        }
    }

    swap(A[i + 1], A[r]);
    if (verboseOutput)
    {
        writePartitionLog(x, A, p, r + 1);
    }
    return i + 1;
}

// Randomized partition
int rPartition(std::vector<CityData> &A, int p, int r)
{
    srand(time(NULL));
    int i = p + rand() % (r - p + 1);
    swap(A[i], A[r]);
    return partition(A, p, r);
}

// Median partition
int mPartition(std::vector<CityData> &A, int p, int r)
{
    srand(time(NULL));
    int i1 = p + rand() % (r - p + 1);
    int i2 = p + rand() % (r - p + 1);
    int i3 = p + rand() % (r - p + 1);

    int medianIndex;
    if ((A[i1].number <= A[i2].number && A[i2].number <= A[i3].number) || (A[i3].number <= A[i2].number && A[i2].number <= A[i1].number))
        medianIndex = i2;
    else if ((A[i2].number <= A[i1].number && A[i1].number <= A[i3].number) || (A[i3].number <= A[i1].number && A[i1].number <= A[i2].number))
        medianIndex = i1;
    else
        medianIndex = i3;

    swap(A[medianIndex], A[r]);
    return partition(A, p, r);
}

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

// Function to set verbose output based on command line argument
void setVerboseOutput(char *arg)
{
    if (arg && *arg == 'v')
    {
        verboseOutput = true;
    }
}

void writePartitionLog(int pivot, const std::vector<CityData> &A, int p, int r)
{
    std::string logEntry = "Pivot: " + std::to_string(pivot) + " Array: [";
    for (size_t i = p; i < r; ++i)
    {
        logEntry += std::to_string(A[i].number);

        // Check if the current element is the last one before appending the comma
        if (i < r - 1)
        {
            logEntry += ", ";
        }
    }
    logEntry += "]";

    logEntries.push_back(logEntry);
}

void writeLogToFile(const std::string &filename)
{
    std::ofstream logFile(filename);

    if (!logFile.is_open())
    {
        std::cerr << "Error opening the file: " << filename << std::endl;
        return;
    }

    for (const auto &logEntry : logEntries)
    {
        logFile << logEntry << std::endl;
    }

    logFile.close();
}