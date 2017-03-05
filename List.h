#pragma once
#include <list>
#include <iterator>

template<class T> class List {
private:
	std::list<T> storage;
public:
	List<T>();
	List<T>(std::list<T> input);
	// inner access functions;
	std::list<T>& getInnerList();
	// inserting functions;
	List<T>& push(T el);
	List<T>& insert(T el, int i);
	// getting functions;
	T get(int i);
	T operator[](int i);
	T pop();
	// deleting functions;
	void remove(int i);
	void removeElement(T el);
	// informations function;
	int size();
	bool contains(T el);
	// recalling std::list<T> methods;
	void unique();
	void reverse();
	void sort();
	template<class Compare>	void sort(Compare comp);
	// others;
	List<T> operator=(List<T> input);
	List<T> operator+(List<T> first);
	//
	~List<T>();
};

template<class T>
List<T>::List()
	:storage() {
}

template<class T>
List<T>::List(std::list<T> input)
	:storage(input){
}

template<class T>
List<T>::~List() {
}

template<class T>
std::list<T>& List<T>::getInnerList() {
	return this->storage;
}

template<class T>
List<T>& List<T>::push(T el) {
	this->storage.push_back(el);
	return *(this);
}

template<class T>
List<T>& List<T>::insert(T el, int i) {
	std::list<T>::iterator insertIt = this->storage.begin();
	std::advance(insertIt, i);
	this->storage.insert(insertIt, el);
	return *(this);

}

template<class T>
T List<T>::get(int i) {
	std::list<T>::iterator begIt = this->storage.begin();
	std::list<T>::iterator lookedIt = this->storage.begin();
	std::advance(lookedIt, i);
	std::list<T> tmp = std::list<T>(this->storage);
	for (begIt; begIt != lookedIt; begIt++) {
		tmp.pop_front();
	}
	return tmp.front();
}

template<class T>
inline T List<T>::operator[](int i){
	return this->get(i);
}

template<class T>
T List<T>::pop() {
	T result = this->storage.back();
	this->storage.pop_back();
	return result;
}

template<class T>
void List<T>::remove(int i) {
	std::list<T>::iterator remIt = this->storage.begin();
	std::advance(remIt, i);
	this->storage.erase(remIt);
}

template<class T>
void List<T>::removeElement(T el) {
	this->storage.remove(el);
}

template<class T>
int List<T>::size() {
	return this->storage.size();
}

template<class T>
bool List<T>::contains(T el) {
	for (T current : this->storage) {
		if (current == el) {
			return true;
		}
	}
	return false;
}

template<class T>
void List<T>::unique() {
	this->storage.unique();
}

template<class T>
void List<T>::reverse() {
	this->storage.reverse();
}

template<class T>
void List<T>::sort() {
	this->storage.sort();
}

template<class T>
List<T> List<T>::operator=(List<T> input) {
	std::list<T> copied = input.getInnerList();
	return List<T>(copied);
}

template<class T>
List<T> List<T>::operator+(List<T> first) {
	std::list<T> result = this->getInnerList();
	std::list<T>::iterator it = result.end();
	std::list<T> appender = first.getInnerList();
	result.splice(it, appender);
	return List<T>(result);
}

template<class T>
template<class Compare>
void List<T>::sort(Compare comp) {
	this->storage.sort(comp);
}


// iterators;


//operators;

template<class T>
std::ostream& operator<<(std::ostream& os, List<T>& dt) {
	os << "[";
	for (T it : dt.getInnerList()) {
		os << it << ", ";
	}
	os << "\b\b]"; // this is beautiful;
	return os;
}

