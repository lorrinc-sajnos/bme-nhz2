#ifndef WEIGHTED_LIST
#define WEIGHTED_LIST

#include <cstddef>
#include "util.hpp"
#include "memory_test.h"

using size_t = std::size_t;

template
<typename T>


class WeightedList {
	size_t _capacity;
	size_t _size;
	int _weight_sum;
	bool _is_locked;
	T* _elements;
	int* _weights;

public:
	WeightedList<T>(size_t capacity) : _capacity(capacity), _size(0), _weight_sum(0),  _is_locked(false) {
		_elements = new T[capacity];
		_weights = new int[capacity];

	}

	WeightedList<T>(WeightedList<T>& w_list) : _capacity(w_list._capacity), _size(w_list._size), _weight_sum(w_list._weight_sum) {
		_elements = new T[w_list._capacity];
		_weights = new int[_capacity];
		if (_size >= _capacity) throw "Hiba! size nagyobbmint capacity!";
		for (size_t i = 0; i < _size; i++) {
			//this->put(w_list._elements[i], w_list._weights[i]);
			_elements[i] = w_list._elements[i];
			_weights[i] = w_list._weights[i];
		}
		_is_locked = w_list._is_locked;
	}

	void freeMem() {
		for (size_t i = 0; i < _size; i++) {
			delete _elements[i];
		}
	}

	~WeightedList<T>() {
		delete[] _elements;
		delete[] _weights;
	}


	size_t size() { return _size; }
	int weight_sum() { return _weight_sum; }

	T get_at(size_t  i) { 
		if (i >= _size) throw "Tul nagy index!";
		return _elements[i]; 
	}


	int get_w_at(size_t  i) {
		if (i >= _size) throw "Tul nagy index!";
		return _weights[i]; 
	}


	void lock() { _is_locked = true; }

	void put(T obj, int weight) {
		if (_size == _capacity) throw "Hiba! Tele a lista.";
		if (_is_locked) return;

		_weight_sum += weight;
		_elements[_size] = obj;
		_weights[_size] = weight;
		_size++;
	}


	T get_rand(int seed) {
	//a seed-rõl feltételezzük, hogy egy normál eloszlású véletlen integer
		int rem = p_mod(seed, _weight_sum);

		int checked_w = 0;
		for (size_t i = 0; i < _size; i++) {
			checked_w += _weights[i];
			if (checked_w > rem) return _elements[i];
		}
		return _elements[_size - 1];
	}


};

#endif