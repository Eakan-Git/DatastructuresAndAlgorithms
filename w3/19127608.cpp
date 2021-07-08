#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 

void swap(string *x, string *y);
int countName(string fileName);
bool readFile(string fileName, string arr[], int size);
void printNames(string arr[], int size);

void bubbleSort(string arr[], int size);
void selectionSort(string arr[], int size);
void insertionSort(string arr[], int size);
void mergeSort(string arr[], int left, int right);
void quickSort(string arr[], int left, int right);
void radixSort(string arr[], int size);
void outputToFile(string fileName, string arr[], int size);
bool menu(string inputFileName, string arr[], int size);

int main()
{
	string inputFileName;

	begin:
	cout << "Input file name: ";
	getline(cin, inputFileName);
	int size = countName(inputFileName);

	string *arr;
	arr = new string[size];

	bool flag = true;

	flag = readFile(inputFileName, arr, size);
	if(flag == false) //can't read the file
		goto begin;

	bool flag2 = true;
	flag2 = menu(inputFileName, arr, size);
	if(flag2 == true) //user want to change input file;
		{
			cin.ignore();
			goto begin;
		}
	delete []arr;
	return 0;
}

bool menu(string inputFileName, string arr[], int size)
{
	char choice;
	menu:
	cout << "\nSelect sort algorithm to perform:\n";
	cout << "[1] Bubble Sort.\n";
	cout << "[2] Selection Sort\n";
	cout << "[3] Insertion Sott\n";
	cout << "[4] Merge Sort\n";
	cout << "[5] Quick Sort\n";
	cout << "[6] Radix Sort\n";
	cout << "[7] Change executing file\n";
	cout << "[0] Exit program\n";
	
	do
	{
		cout << "Your choice: ";
		cin >> choice;
	} while(choice < '0' || choice > '7');

	switch(choice)
	{
		case '1':
		{
			cout << "\nPlease wait...\n";
			auto start = high_resolution_clock::now();
			bubbleSort(arr, size);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			outputToFile("Bubble_Sort.txt", arr, size);

			cout << "Output result to file: Successfully!" << endl;
			cout << "Used algorithm: Bubble sort." << endl;
			cout << "Used data type: " << inputFileName[0] << endl;
			cout << "Running time: " << duration.count() << " ms." << endl;
			cout << "Student ID: 19127608"<< endl << endl;
			goto menu;
			break;
		}
		case '2':
		{
			cout << "\nPlease wait...\n";
			auto start = high_resolution_clock::now();
			selectionSort(arr, size);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			outputToFile("Selection_Sort.txt", arr, size);

			cout << "Output result to file: Successfully!" << endl;
			cout << "Used algorithm: Selection sort." << endl;
			cout << "Used data type: " << inputFileName[0] << endl;
			cout << "Running time: " << duration.count() << " ms." << endl;
			cout << "Student ID: 19127608"<< endl << endl;
			goto menu;
			break;
		}
		case '3':
		{
			cout << "\nPlease wait...\n";
			auto start = high_resolution_clock::now();
			insertionSort(arr, size);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			outputToFile("Insertion_Sort.txt", arr, size);

			cout << "Output result to file: Successfully!" << endl;
			cout << "Used algorithm: Insertion sort." << endl;
			cout << "Used data type: " << inputFileName[0] << endl;
			cout << "Running time: " << duration.count() << " ms." << endl;
			cout << "Student ID: 19127608"<< endl << endl;
			goto menu;
			break;
		}
		case '4':
		{
			cout << "\nPlease wait...\n";
			auto start = high_resolution_clock::now();
			mergeSort(arr, 0, size - 1);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			outputToFile("Merge_Sort.txt", arr, size);

			cout << "Output result to file: Successfully!" << endl;
			cout << "Used algorithm: Merge sort." << endl;
			cout << "Used data type: " << inputFileName[0] << endl;
			cout << "Running time: " << duration.count() << " ms." << endl;
			cout << "Student ID: 19127608" << endl<< endl;
			goto menu;
			break;
		}
		case '5':
		{
			cout << "\nPlease wait...\n";
			auto start = high_resolution_clock::now();
			quickSort(arr, 0, size - 1);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			outputToFile("Quick_Sort.txt", arr, size);

			cout << "Output result to file: Successfully!" << endl;
			cout << "Used algorithm: Quick sort." << endl;
			cout << "Used data type: " << inputFileName[0] << endl;
			cout << "Running time: " << duration.count() << " ms." << endl;
			cout << "Student ID: 19127608"<< endl << endl;
			goto menu;
			break;
		}
		case '6':
		{
			cout << "\nPlease wait...\n";
			auto start = high_resolution_clock::now();
			radixSort(arr, size);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start); 

			outputToFile("Radix_Sort.txt", arr, size);
			cout << "Output result to file: Successfully!" << endl;
			cout << "Used algorithm: Radix sort." << endl;
			cout << "Used data type: " << inputFileName[0] << endl;
			cout << "Running time: " << duration.count() << " ms." << endl;
			cout << "Student ID: 19127608" << endl<< endl;
			goto menu;
			break;
		}
		case '7':
			{
				cin.clear();
				return true;
			}
		case '0':
			return false;
		default:
			return false;
	}
}
void swap(string *x, string *y)
{
	string temp = *x;
	*x = *y;
	*y = temp;
}
int countName(string fileName)
{
	int counter = 0;
	ifstream file;
	file.open(fileName);
	if(file.is_open())
	{
		string str;
		while(getline(file, str))
			counter++;
	}
	file.close();
	return counter;
}

bool readFile(string fileName, string arr[], int size)
{
	ifstream file;
	file.open(fileName);
	
	if(file.is_open())
	{
		for(int i = 0; i < size; ++i)
		{
			file >> arr[i];
		}
		file.close();
		return true;
	}
	else
		{
			cout << "Can't open file.\n";
			file.close();
			return false;
		}
	file.close();
	return true;
}
void printNames(string arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << arr[i] << endl;
	}
}

void bubbleSort(string arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			if(arr[j] > arr[j+1])
				{
					swap(&arr[j], &arr[j+1]);
				}
		}
	}
}
void outputToFile(string fileName, string arr[], int size)
{
	ofstream file;
	file.open(fileName);
	if(file.is_open())
	{
		for(int i = 0; i < size; ++i)
			file << arr[i] << endl;
	}
}
void selectionSort(string arr[], int size)
{
	string minVal;
	int minIdx;

	for(int i = 0; i < size - 1; ++i)
	{
		minIdx = i;
		minVal = arr[i];

		for(int j = i + 1; j < size; ++j)
		{
			if(arr[j] < minVal)
			{
				minVal = arr[j];
				minIdx = j;
			}
		}
		arr[minIdx] = arr[i];
		arr[i] = minVal;
	}
}

void insertionSort(string arr[], int size)
{
	int i, j;
	string key;
	for(i = 1; i< size; ++i)
	{
		key = arr[i];
		j = i - 1;
		while(j >= 0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			--j;
		}
		arr[j+1] = key;
	}
}

void merge(string arr[], int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	string *arrL = new string[n1];
	string *arrR = new string[n2];

	//copy
	for(int i = 0; i < n1; ++i)
		arrL[i] = arr[left+i];

	for(int i = 0; i < n2; ++i)
		arrR[i] = arr[mid+i+1];
	//printNames(arrL, n1);

	int i = 0;
	int j = 0;
	int k = left;

	while(i < n1 && j < n2)
	{
		if(arrL[i] <= arrR[j])
			arr[k++] = arrL[i++];
		else
			arr[k++] = arrR[j++];
	}

	while(i < n1)
		arr[k++] = arrL[i++];
	while(j < n2)
		arr[k++] = arrR[j++];

	delete []arrL;
	delete []arrR;
}

void mergeSort(string arr[], int left, int right)
{
	if(left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid+1, right);
		merge(arr, left, mid, right); 
	}
}

int partition(string arr[], int left, int right)
{
	int mid = (left + right) / 2;
	string pivot = arr[mid];
	int i = left - 1;

	for(int j = left; j <= right - 1; ++j)
	{
		if(arr[j] < pivot)
		{
			++i;
			swap(arr[i], arr[j]);
		}
	}

	swap(arr[i+1], arr[right]);
	return i+1;
}

void quickSort(string arr[], int left, int right)
{
	if(left < right)
	{
		int pi = partition(arr, left, right);
		quickSort(arr, left, pi-1);
		quickSort(arr, pi+1, right);
	}
}

void radixSort(string arr[], int size)
{
	int maxLen = 256;
	const int BUCKETS = 256;
	vector<vector<string>> wordsByLen(maxLen + 1);
	vector<vector<string>> buckets(BUCKETS);


	for (int i = 0; i < size; ++i)
	{
		string s = arr[i];
		wordsByLen[s.length()].push_back(move(s));
	}

	int idx = 0;
	for (auto & wordList : wordsByLen)
	{
		for (string &s : wordList)
		{
			arr[idx++] = move(s);
		}
	}

	int startingIdx = size;

	for (int pos = maxLen - 1; pos >= 0; --pos)
	{
		startingIdx -= wordsByLen[pos+1].size();

		for (int i = startingIdx; i < size; ++i)
		{
			buckets[arr[i][pos]].push_back(move(arr[i]));
		}

		idx = startingIdx;
		for (auto &thisBucket : buckets)
		{
			for (string &s : thisBucket)
			{
				arr[idx++] = move(s);
			}
			thisBucket.clear();
		}
	}
}	