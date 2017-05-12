#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

class MyQueue {
  
    public:
        stack<int> stack_newest_on_top, stack_oldest_on_top;   
        void push(int x) 
        {
                stack_newest_on_top.push(x);
        }


        void pop() 
        {
                adjust_stacks();
                stack_oldest_on_top.pop();
        }

        int front() {
                adjust_stacks();
                return stack_oldest_on_top.top();
        
        }

    private:
        // Call this before calling pop or front to adjust stacks if needed
        void adjust_stacks() 
        {
                if (stack_oldest_on_top.empty()) {
                        while (!stack_newest_on_top.empty()) {
                                stack_oldest_on_top.push(stack_newest_on_top.top());
                                stack_newest_on_top.pop();
                        }
                }
        }

};

int main() {
    MyQueue q1;


    q1.push(42);
    q1.pop();
    q1.push(14);
    cout << q1.front() << endl;
    //assert(q1.front() == 14);
    q1.push(28);
    cout << q1.front() << endl;
    //assert(q1.front() == 14);
    q1.push(60);
    q1.push(78);
    q1.pop();
    q1.pop();
    
}
