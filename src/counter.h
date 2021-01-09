#ifndef COUNTER_H_
#define COUNTER_H_

#include <mutex>

class Counter {
public:
	Counter() {}
	Counter(unsigned long value) : value_(value) {}
	unsigned long Increment() {
		std::lock_guard<std::mutex> lock(mtx_);
		return ++value_;
	}
	unsigned long Value() const { return value_; }
	Counter(const Counter& other) = delete;
	Counter& operator=(const Counter& other) = delete;
private:
	unsigned long value_{0};
	std::mutex mtx_;
};

#endif // COUNTER_H
