#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono; 

int countName(string fileName);
bool readFile(string fileName, string arr[], int size);
string* createRandFile(string fileName, string arr[], int arrSize, int size);
int* linearSearch(string keyArr[], int sizeKeyArr, string arr[], int sizeArr);
void printNames(string arr[], int size);
void outputRes(string fileName, string keyArr[], int sizeKeyArr, int res[]);
int *binarySearch(string arrKey[], int sizeKeyArr, string arr[], int size);
void bubbleSort(string arr[], int size);
void selectionSort(string arr[], int size);
void insertionSort(string arr[], int size);
void mergeSort(string arr[], int left, int right);
void quickSort(string arr[], int left, int right);
void radixSort(string arr[], int size);
string* copyArr(string arr[], int size);
void swap(string *x, string *y);

int main()
{
	srand((int)time(NULL));
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

	string name100 = "100.txt";
	string name1k = "1k.txt";
	string name10k = "10k.txt";
	string name50k = "50k.txt";

	const int A = 100;
	const int B = 1000;
	const int C = 10000;
	const int D = 50000;

	string *arrA, *arrB, *arrC, *arrD;
	int *resA, *resB, *resC, *resD;
	//Task 4:
	cout << "\nTask 4:\n";
	cout << "Creating " << name100 << " : ";
	arrA = createRandFile(name100, arr, size, A);

	cout << "Creating " << name1k << " : ";
	arrB = createRandFile(name1k, arr, size, B);

	cout << "Creating " << name10k << " : ";
	arrC = createRandFile(name10k, arr, size, C);

	cout << "Creating " << name50k << " : ";
	arrD = createRandFile(name50k, arr, size, D); 

	//printNames(arrA, A);
	//Task 5:
	//Linear search:
	string resFileName;
	

	cout << "\nTask 5:\n";
	cout << "Linear Search: In " << inputFileName << " - Unsorted:\n";

	auto start = high_resolution_clock::now();
	resA = linearSearch(arrA, A, arr, size);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << endl << A << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultLinear" + to_string(A) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n\n";
	outputRes(resFileName, arrA, A, resA);


	start = high_resolution_clock::now();
	resB = linearSearch(arrB, B, arr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
 	cout << B << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultLinear" + to_string(B) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n\n";
	outputRes(resFileName, arrB, B, resB);


	start = high_resolution_clock::now();
 	resC = linearSearch(arrC, C, arr, size);
 	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	cout << C << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultLinear" + to_string(C) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n\n";
	outputRes(resFileName, arrC, C, resC);


	start = high_resolution_clock::now();
	resD = linearSearch(arrD, D, arr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	cout << D << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultLinear" + to_string(D) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrD, D, resD);



	

	string* tempArr = new string[size];


	//Bubble sort + BS
	cout << "\n\nBubble Sort + Binary Search: Please wait because bubble sort is really slow.\n\n";
	//copy arr
	tempArr = copyArr(arr, size);
	//printNames(tempArr, size);
	start = high_resolution_clock::now();
	//sort the array
	bubbleSort(tempArr, size);
	//search
	resA = binarySearch(arrA, A, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << A << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultBubble" + to_string(A) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrA, A, resA);
	delete []tempArr;



	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	bubbleSort(tempArr, size);

	resB = binarySearch(arrB, B, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << B << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultBubble" + to_string(B) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrB, B, resB);
	delete []tempArr;



	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	bubbleSort(tempArr, size);
	resC = binarySearch(arrC, C, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << C << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultBubble" + to_string(C) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrC, C, resC);
	delete []tempArr;



	
	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	bubbleSort(tempArr, size);
	resD = binarySearch(arrD, D, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	cout << D << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultBubble" + to_string(D) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrD, D, resD);
	delete []tempArr;

	//Selection sort + BS
	cout << "\n\nSelection Sort + Binary Search: Please wait because selection sort is really slow.\n\n";
	//copy arr
	tempArr = copyArr(arr, size);
	//printNames(tempArr, size);
	start = high_resolution_clock::now();
	//sort the array
	selectionSort(tempArr, size);
	//search
	resA = binarySearch(arrA, A, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << A << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultSelection" + to_string(A) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrA, A, resA);
	delete []tempArr;

	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	selectionSort(tempArr, size);

	resB = binarySearch(arrB, B, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << B << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultSelection" + to_string(B) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrB, B, resB);
	delete []tempArr;



	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	selectionSort(tempArr, size);
	resC = binarySearch(arrC, C, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << C << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultSelection" + to_string(C) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrC, C, resC);
	delete []tempArr;



	
	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	selectionSort(tempArr, size);
	resD = binarySearch(arrD, D, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	cout << D << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultSelection" + to_string(D) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrD, D, resD);
	delete []tempArr;

	//Insertion sort + BS
	cout << "\n\nInsertion Sort + Binary Search: Please wait because insertion sort is really slow.\n\n";
	//copy arr
	tempArr = copyArr(arr, size);
	//printNames(tempArr, size);
	start = high_resolution_clock::now();
	//sort the array
	insertionSort(tempArr, size);
	//search
	resA = binarySearch(arrA, A, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << A << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultInsertion" + to_string(A) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrA, A, resA);
	delete []tempArr;

	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	insertionSort(tempArr, size);

	resB = binarySearch(arrB, B, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << B << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultInsertion" + to_string(B) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrB, B, resB);
	delete []tempArr;



	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	insertionSort(tempArr, size);
	resC = binarySearch(arrC, C, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << C << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultInsertion" + to_string(C) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrC, C, resC);
	delete []tempArr;



	
	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	insertionSort(tempArr, size);
	resD = binarySearch(arrD, D, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	cout << D << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultInsertion" + to_string(D) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrD, D, resD);
	delete []tempArr;


	//Merge sort + BS
	cout << "\n\nMerge Sort + Binary Search:\n\n";
	//copy arr
	tempArr = copyArr(arr, size);
	//printNames(tempArr, size);
	start = high_resolution_clock::now();
	//sort the array
	mergeSort(tempArr, 0, size-1);
	//search
	resA = binarySearch(arrA, A, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << A << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultMerge" + to_string(A) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrA, A, resA);
	delete []tempArr;

	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	mergeSort(tempArr, 0, size-1);

	resB = binarySearch(arrB, B, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << B << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultMerge" + to_string(B) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrB, B, resB);
	delete []tempArr;



	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	mergeSort(tempArr, 0, size-1);
	resC = binarySearch(arrC, C, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << C << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultMerge" + to_string(C) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrC, C, resC);
	delete []tempArr;



	
	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	mergeSort(tempArr, 0, size-1);
	resD = binarySearch(arrD, D, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	cout << D << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultMerge" + to_string(D) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrD, D, resD);
	delete []tempArr;

	//Quick sort + BS
	cout << "\n\nQuick Sort + Binary Search:\n\n";
	//copy arr
	tempArr = copyArr(arr, size);
	//printNames(tempArr, size);
	start = high_resolution_clock::now();
	//sort the array
	quickSort(tempArr, 0, size-1);
	//search
	resA = binarySearch(arrA, A, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << A << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultQuick" + to_string(A) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrA, A, resA);
	delete []tempArr;

	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	quickSort(tempArr, 0, size-1);

	resB = binarySearch(arrB, B, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << B << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultQuick" + to_string(B) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrB, B, resB);
	delete []tempArr;



	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	quickSort(tempArr, 0, size-1);
	resC = binarySearch(arrC, C, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << C << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultQuick" + to_string(C) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrC, C, resC);
	delete []tempArr;



	
	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	quickSort(tempArr, 0, size-1);
	resD = binarySearch(arrD, D, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	cout << D << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultQuick" + to_string(D) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrD, D, resD);
	delete []tempArr;

	//Radix sort + BS
	cout << "\n\nRadix Sort + Binary Search:\n\n";
	//copy arr
	tempArr = copyArr(arr, size);
	//printNames(tempArr, size);
	start = high_resolution_clock::now();
	//sort the array
	radixSort(tempArr, size);
	//search
	resA = binarySearch(arrA, A, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << A << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultRadix" + to_string(A) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrA, A, resA);
	delete []tempArr;

	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	radixSort(tempArr, size);

	resB = binarySearch(arrB, B, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << B << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultRadix" + to_string(B) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrB, B, resB);
	delete []tempArr;



	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	radixSort(tempArr, size);
	resC = binarySearch(arrC, C, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);

	cout << C << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultRadix" + to_string(C) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrC, C, resC);
	delete []tempArr;



	
	tempArr = copyArr(arr, size);
	start = high_resolution_clock::now();
	//sort the array
	radixSort(tempArr, size);
	resD = binarySearch(arrD, D, tempArr, size);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start);
	cout << D << " names: ";
	cout << "Running time = " << duration.count() << " ms." << endl;
	resFileName = "ResultRadix" + to_string(D) + ".txt";
	cout << "Output result to file " << resFileName << ": Successfully.\n";
	outputRes(resFileName, arrD, D, resD);
	delete []tempArr;
	
	delete []arrA;
	delete []arrB;
	delete []arrC;
	delete []arrD;

	delete []resA;
	delete []resB;
	delete []resC;
	delete []resD;

	delete []arr;
	return 0;
}
void printNames(string arr[], int size)
{
	for(int i = 0; i < size; ++i)
		cout << arr[i] << endl;
}
string* copyArr(string arr[], int size)
{
	string* p = new string [size];
	for(int i = 0; i < size; ++i)
		p[i] = arr[i];
	return p;
}
void outputRes(string fileName, string keyArr[], int sizeKeyArr, int res[])
{
	ofstream file;
	file.open(fileName);
	if(file.is_open())
	{
		for(int i = 0; i < sizeKeyArr; ++i)
			file << keyArr[i] << ": " << res[i] << endl;
	}
	else
		cout << "Unable to create result file.\n";
	file.close();
}
string* createRandFile(string fileName, string arr[], int arrSize, int size)
{
	ofstream file;
	file.open(fileName);
	string *res = new string[size];
	if (file.is_open())
	{
		int idx;
		for(int i = 0; i < size; ++i)
		{
			idx = rand() % arrSize;
			file << arr[idx] << endl;
			res[i] = arr[idx];
		}
		file.close();
		cout << "File created successfully.\n";
		return res;
	}
	else
		cout << "Unable to create/ open file.\n";
	return res;
}

int* linearSearch(string keyArr[], int sizeKeyArr, string arr[], int sizeArr)
{
	int *res = new int[sizeKeyArr];
	int flag = 0;
	for(int i = 0; i < sizeKeyArr; ++i)
	{
		for(int j = 0; j < sizeArr; ++j)
		{
			if(keyArr[i] == arr[j])
				{
					res[flag] = j+1;
					++flag;
				}
		}
	}
	return res;
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

int *binarySearch(string arrKey[], int sizeKeyArr, string arr[], int size)
{
	int *res = new int[sizeKeyArr];
	int left, right, mid;
	bool flag;

	for(int i = 0; i < sizeKeyArr; ++i)
	{
		left = 0;
		right = size - 1;

		while(left <= right)
		{
			mid = left + (right - left) / 2;
			if(arrKey[i] == arr[mid])
				{
					res[i] = mid;
					break;
				}
			else if(arrKey[i] > arr[mid])
				left = mid + 1;
			else
				right = mid - 1;
		}
	}
	return res;
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
void swap(string *x, string *y)
{
	string temp = *x;
	*x = *y;
	*y = temp;
}
void bubbleSort(string arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			if(arr[j] > arr[j+1])
				{
					// string temp = arr[j];
					// arr[j] = arr[j+1];
					// arr[j+1] = temp;
					swap(arr[j], arr[j+1]);
				}
		}
	}
}