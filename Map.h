#pragma once
#include <map>
#include <iterator>
#include <set>

template <class K, class V> class Map{
private:
	std::map<K, V> storage;
public:
	Map<K, V>();
	Map<K, V>(std::map<K, V> input);
	// inner access functions;
	std::map<K, V>& getInnerMap();
	// inserting functions;
	Map<K, V>& insert(K key, V value);
	// getting functions;
	V get(K key);
	V operator[](K key);
	std::set<K> keySet();
	// deleting functions;
	void remove(K key);
	// information functions;
	int size();
	bool contains(K key);
	// recalling std::map<T> methods;

	// other;
	Map<K, V> operator=(Map<K, V>input);
	//
	~Map();
};

template<class K, class V>
Map<K, V>::Map()
	:storage() {
}

template<class K, class V>
Map<K, V>::Map(std::map<K, V> input) 
	:storage(input){
}

template<class K, class V>
std::map<K, V>& Map<K, V>::getInnerMap() {
	return this->storage;
}

template<class K, class V>
Map<K, V>& Map<K, V>::insert(K key, V value) {
	this->storage.insert(std::pair<K, V>(key, value));
	return *(this);
}

template<class K, class V>
V Map<K, V>::get(K key) {
	return this->storage[key];
}

template<class K, class V>
void Map<K, V>::remove(K key) {
	this->storage.erase(this->storage.find(key));
}

template<class K, class V>
int Map<K, V>::size() {
	return this->storage.size();
}

/* rewrite this using std::map::find()
template<class K, class V>
bool Map<K, V>::contains(K key) {
	for (std::pair<K, V> current : this->storage) {
		if (current.first == el) {
			return true;
		}
	}
	return false;
}
*/
template<class K, class V>
bool Map<K, V>::contains(K key) {
	std::map<K, V>::iterator elementIt = this->storage.find(key);
	if (elementIt != this->storage.end()) {
		return true;
	}
	return false;
}

template<class K, class V>
Map<K, V> Map<K, V>::operator=(Map<K, V> input) {
	std::map<K, V> copied = input.getInnerMap();
	return Map<K, V>(copied);
}

template<class K, class V>
Map<K, V>::~Map(){
}

template<class K, class V>
V Map<K, V>::operator[](K key) {
	return this->storage[key];
}

template<class K, class V>
std::set<K> Map<K, V>::keySet(){
	std::set<K> result = std::set<K>();
	std::set<K>::iterator it;
	for (std::pair<K, V>coup : this->storage) {
		it = result.end();
		result.insert(it, coup.first);
	}
	return result;
}

template<class K, class V>
std::ostream& operator<<(std::ostream& os, Map<K, V>& map) {
	os << "{";
	for (K key : map.keySet()) {
		os << key << ":" << map[key] << ", ";
	}
	os << "\b\b}"; // this is beautiful;
	return os;
}