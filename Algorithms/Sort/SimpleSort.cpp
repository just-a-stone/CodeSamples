#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;



/**
 * Dumps a vector of strings to an output stream.
 */
ostream& operator<<(ostream& stream, const vector<string>& data) {
    stream << "[";

    vector<string>::const_iterator iter = data.begin();
    if (iter != data.end()) {
        stream << '"' << *iter << '"';
	iter++;
    }

    while(iter != data.end()) {
        stream << ", \"" << *iter << '"';
	iter++;
    }

    stream << "]";
    return stream;
}


void saveList(const char* fileName, const vector<string>& data) {
    ofstream ofs(fileName);
    ofs << data.size();
    ofs << "\n";	// need some sort of separator!
    copy(data.begin(), data.end(),
	 ostream_iterator<string>(ofs, "\n"));
    ofs.close();
}






class SortAlgorithm {
private:
    string algorithmName;

protected:
    vector<string> unsortedArray;

    vector<string> loadList(const char* fileName);

    virtual void doSort() = 0;

public:
    SortAlgorithm(const string& name = "Unknown");

    virtual ~SortAlgorithm();

    void generateData();

    void run();
};


SortAlgorithm::SortAlgorithm(const string& name) : algorithmName(name) {
    unsortedArray = loadList("array.dat");
}


SortAlgorithm::~SortAlgorithm() {
}


vector<string> SortAlgorithm::loadList(const char* fileName) {
    vector<string> result;
    ifstream ifs(fileName);
    size_t size;
    ifs >> size;
    result.resize(size);
    for (size_t i=0; i<size; i++) {
       ifs >> result[i];
    }
    ifs.close();
    return result;
}


void SortAlgorithm::generateData() {
    vector<string> someList;
    someList.push_back("Hello");
    someList.push_back("World");
    someList.push_back("Moon");
    someList.push_back("Earth");
    someList.push_back("Venus");
    someList.push_back("Merkur");
    someList.push_back("Mars");
    someList.push_back("Saturn");
    someList.push_back("Neptun");
    someList.push_back("Uranus");
    someList.push_back("Pluto");
    someList.push_back("Asteroid");
    someList.push_back("Sun");

    saveList("array.dat", someList);
}


void SortAlgorithm::run() {
    cerr << algorithmName << ":" << std::endl;
    cerr << "  BEFORE: " << unsortedArray << std::endl;
    doSort();
    cerr << "  AFTER : " << unsortedArray << std::endl;
}


class BraindeadSort : public SortAlgorithm {
public:
    BraindeadSort();

protected:
    virtual void doSort();
};


BraindeadSort::BraindeadSort() : SortAlgorithm("BraindeadSort") {
}

/**
 * Brain-dead sorting algorithm:
 *  - Search the next value in the unsorted array
 *  - push this value into the sorted array
 *  - start from scratch
 *
 *  - Time complexity: O(n^2)
 *  - Space complexity: O(2n)
 */
void BraindeadSort::doSort() {
    vector<string> sortedArray;

    string prev;
    for (int i = 0;  i < unsortedArray.size();  i++) {

	// Find the smallest element which is still larger than the previous element
	string current;
	for (int idx = 0;  idx < unsortedArray.size();  idx++) {
	    if (unsortedArray[idx] > prev && (current == "" || unsortedArray[idx] < current)) {
		current = unsortedArray[idx];
	    }
        }
        sortedArray.push_back(current);

        prev = current;
    }
    
    unsortedArray = sortedArray;
}


class SimpleSort : public SortAlgorithm {
public:
    SimpleSort();

protected:
    virtual void doSort();
};

SimpleSort::SimpleSort() : SortAlgorithm("SimpleSort") {
}

/**
 * SimpleSort sorting algorithm (in-place sorting):
 *  - Search the next value in the unsorted array
 *  - exchange values in the unsorted array
 *  - start from scratch
 *
 *  - Time complexity: O(n^2)
 *  - Space complexity: O(n)
 */
void SimpleSort::doSort() {
    for (int i = 0;  i < unsortedArray.size();  i++) {
	for (int idx = 0;  idx < unsortedArray.size();  idx++) {
	    if (unsortedArray[idx] > unsortedArray[i]) {
		string temp = unsortedArray[idx];
		unsortedArray[idx] = unsortedArray[i];
		unsortedArray[i] = temp;
	    }
        }
    }
}


class QuickSort : public SortAlgorithm {
    void quicksort(int left, int right);
    int divide(int left, int right);

public:
    QuickSort();

protected:
    virtual void doSort();
};


QuickSort::QuickSort() : SortAlgorithm("Quicksort") {
}


int QuickSort::divide(int left, int right) {
    int i = left; 
    int j = right - 1;
    string pivot = unsortedArray[right];

    do {
        while(unsortedArray[i] <= pivot && i < right) {
	    i++;
	}

	while(unsortedArray[j] >= pivot && j > left) {
            j--;
        }

	if (i < j) {
	    string temp = unsortedArray[j];
	    unsortedArray[j] = unsortedArray[i];
	    unsortedArray[i] = temp;
        }
    } while(i < j);

    if (unsortedArray[i] > pivot) {
	string temp = unsortedArray[right];
	unsortedArray[right] = unsortedArray[i];
	unsortedArray[i] = temp;
    }

    return i;
}


void QuickSort::quicksort(int left, int right) {
    if (left < right) {
        int divider = divide(left, right);
	quicksort(left, divider - 1);
	quicksort(divider + 1, right);
    }
}


/**
 * QuickSort sorting algorithm (in-place sorting)
 */
void QuickSort::doSort() {
    quicksort(0, unsortedArray.size() - 1);
}


int main() {
    BraindeadSort sort1;
    sort1.run();

    SimpleSort sort2;
    sort2.run();

    QuickSort sort3;
    sort3.run();

    return 0;
}
