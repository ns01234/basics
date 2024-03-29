#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class DinnerPlates {
public:
    vector<stack<int>> vec;
    vector<int> v1;
    int capacity;
    int size = 0;

    DinnerPlates(int capacity) {
        this->capacity = capacity;
    }

    void push(int val) {
        if (v1.empty()) {
            stack<int> newStack;
            newStack.push(val);
            vec.push_back(newStack);
            int y = vec.back().size();
            if (y != capacity) {
                v1.push_back(size);
            }
            size++;
        } else {
            int index = v1[0];
            vec[index].push(val);
            v1.erase(v1.begin());
        }
    }

    int pop() {
        for (int i = size - 1; i >= 0; i--) {
            if (!vec[i].empty()) {
                int t = vec[i].top();
                vec[i].pop();

                if (vec[i].empty()) {
                    vec.erase(vec.begin() + i);
                    auto it = find(v1.begin(), v1.end(), i);
                    if (it != v1.end()) {
                        v1.erase(it);
                    }

                    size--;

                    for (int& a : v1) {
                        if (a > i) {
                            a = a - 1;
                        }
                    }
                } else {
                    auto it = lower_bound(v1.begin(), v1.end(), i);
                    v1.insert(it, i);
                }
                return t;
            }
        }
        return -1;
    }

    int popAtStack(int index) {
        if (index >= size || vec[index].empty()) {
            return -1;
        } else {
            int t = vec[index].top();
            vec[index].pop();

            auto it = lower_bound(v1.begin(), v1.end(), index);
            v1.insert(it, index);

            return t;
        }
    }
};

int main () {

    DinnerPlates d = DinnerPlates(2);
    d.push(1);
    d.push(2);
    d.push(3);
    d.push(4);
    d.push(5);
    cout << d.popAtStack(1);
    cout << d.popAtStack(1);
    cout << d.pop();
    cout << d.pop();
    d.push(8);
    cout << d.popAtStack(0);

}