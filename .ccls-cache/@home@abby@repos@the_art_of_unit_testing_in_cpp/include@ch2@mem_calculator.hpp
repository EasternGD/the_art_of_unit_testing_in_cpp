/* Copyright 2023 Abby */
namespace sample {

class mem_calculator {
 public:
    void add(const int& number);
    int  sum();

 private:
    int sum_ = 0;
};

inline void mem_calculator::add(const int& number) { sum_ += number; }

inline int mem_calculator::sum() {
    int temp = sum_;
    sum_     = 0;
    return temp;
}

} // namespace sample
