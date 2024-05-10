#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template <typename T>
class HashTable
{
public:
	HashTable(int size, int(*hf)(T))
	{
		currentSize = 0; 
		vec.resize(size); // use vector
		myhashPtr = hf; // index number 
	}
	bool contains(const T& x) const // after the inserting contains changed
	{
		list<T>& curList = vec[myhash(x)];
		return (find(curList.begin(), curList.end(), x) != curList.end());
	}
	void makeEmpty()
	{
		for (int i = 0; i < vec.size(); i++)
			vec[i].clear();
	}
	bool insert(const T& x) // add new value
	{
		list<T>& curList = vec[myhash(x)];
		if (find(curList.begin(), curList.end(), x) != curList.end())
			return false;
		curList.push_back(x);
		currentSize++;

		if (currentSize == vec.size())
			rehash();

		return true;
	}
	bool remove(const T& x) // clear one object(value) 
	{
		list<T>& curList = vec[myhash(x)];
		typename list<T>::iterator it = find(curList.begin(), curList.end(), x);
		if (it == curList.end())
			return false;
		curList.erase(it);
		currentSize--;
		return true;
	}

	void display()
	{
		typename list<T>::iterator it;
		for (int i = 0; i < vec.size(); i++) { // searching
			cout << i << ": ";
			for (it = vec[i].begin(); it != vec[i].end(); it++)
				cout << *it << " ";
			cout << endl;
		}
	}
private:
	vector<list<T>> vec; // The array of Lists
	int currentSize;
	int(*myhashPtr)(T);
	void rehash() // important!!!!!!!
	{
		vector<list<T>> tempVec = vec; 
		typename list<T>::iterator it;
		for (int i = 0; i < vec.size(); i++)
			vec[i].clear();
		vec.resize(2 * vec.size());  // Dublicated has table size

		for (int i = 0; i < tempVec.size(); i++)
			for (it = tempVec[i].begin(); it != tempVec[i].end(); it++)
				insert(*it);
	}

	int myhash(const T& x) const
	{
		return myhashPtr(x) % vec.size();
	}
};

int fn(string key)
{
	return key[0] - 'A'; // v = <MERVE> Ascii kodla çıkarır dikat et!
						 //      01234
						 // key[0] = M
}



int main()
{
	HashTable<string> ht(5, fn);

	ht.insert("CAT");
	ht.insert("HEN");
	ht.insert("DOG");
	ht.display();
	cout << "--------" << endl;

	ht.remove("CAT");
	ht.display();
	cout << "--------" << endl;

	ht.insert("RAT");
	ht.insert("BAT");
	ht.insert("PIG");
	ht.insert("SNAKE");
	ht.display();
	cout << "--------" << endl;





	return 0;
}