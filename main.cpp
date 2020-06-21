#include "allocator.h"
#include "container.h"

#include <iostream>
#include <map>

using namespace std;

template<class T>
void fact(T& container) {
	int number = 1;
	container[0] = number;
	for (int i = 1; i < 10; ++i) {
		number *= i;
		container[i] = number;
	}
}

template<class T>
void printMap(const T& container) {
	for (auto& cont : container)
		cout << cont.first << " " << cont.second << endl;
}

template<class T, typename Allocator = std::allocator<T>>
void addItems(Container<T, Allocator>& container) {
	for (size_t i = 0; i < 10; ++i)
		container.push_back(i);
}

int main() {
	map<int, int> containerA;
	map<int, int, std::less<int>, MyAllocator<pair<int, int>, 10>> containerB;

	fact(containerA);
	fact(containerB);

	printMap(containerA);
	printMap(containerB);

	Container<int> containerC;
	Container<int, MyAllocator<int, 10>> containerD;

	addItems(containerC);
	addItems(containerD);

	containerC.print();
	containerD.print();

	return 0;
}