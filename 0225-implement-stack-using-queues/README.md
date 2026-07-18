# 0225-implement-stack-using-queues

## 📋 Problem Description
Implement a Last-In-First-Out (LIFO) stack using only the standard operations of a First-In-First-Out (FIFO) queue. The `MyStack` class should support all the functions of a normal stack: `push`, `top`, `pop`, and `empty`.

Specifically, you need to implement the following methods:
*   `void push(int x)`: Adds element `x` to the top of the stack.
*   `int pop()`: Removes and returns the element currently at the top of the stack.
*   `int top()`: Returns the element currently at the top of the stack without removing it.
*   `boolean empty()`: Returns `true` if the stack is empty, `false` otherwise.

You are restricted to using only standard queue operations: `push to back`, `peek/pop from front`, `size`, and `is empty`.

## 🔍 Examples
**Example 1:**
```
Input:
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
Output:
[null, null, null, 2, 2, false]
Explanation:
MyStack myStack = new MyStack();
myStack.push(1);   // Stack: [1]
myStack.push(2);   // Stack: [1, 2] (2 is the top element)
myStack.top();     // return 2
myStack.pop();     // return 2, Stack becomes: [1]
myStack.empty();   // return false
```

**Example 2:**
```
Input:
["MyStack", "push", "empty", "pop", "empty"]
[[], [5], [], [], []]
Output:
[null, null, false, 5, true]
Explanation:
MyStack myStack = new MyStack();
myStack.push(5);   // Stack: [5]
myStack.empty();   // return false
myStack.pop();     // return 5, Stack becomes: []
myStack.empty();   // return true
```

## 📌 Constraints
*   `1 <= x <= 9`
*   At most `100` calls will be made to `push`, `pop`, `top`, and `empty`.
*   All calls to `pop` and `top` are valid (i.e., the stack will not be empty when `pop` or `top` is called).

## 🤔 Understanding the Problem
The problem asks us to simulate a Last-In-First-Out (LIFO) data structure, a stack, using only the operations available for a First-In-First-Out (FIFO) data structure, a queue. The core challenge is that queues naturally expose the *oldest* element first, while stacks need to expose the *newest* element first. We need to devise a strategy to reorder elements within queues to always make the most recently added item accessible as the "front" of a queue.

## 💡 Core Idea
The central idea is to always maintain the stack's top element at the front of one of our queues. This can be achieved by using an auxiliary queue to temporarily store elements, allowing us to reorder them during the `push` operation so that the newly added element becomes the primary queue's front.

## 🧠 Approach — Data Structure Design / Queue Manipulation
This problem falls under the "Data Structure Design" pattern, specifically focusing on "Queue Manipulation". We utilize two queues to mimic the LIFO behavior of a stack. One queue (`q1`) is designated as the primary storage, always ensuring its front element is the current stack top. The second queue (`q2`) serves as a temporary buffer to facilitate the reordering of elements. This approach is necessary because queues inherently provide FIFO access, so to achieve LIFO, we must strategically move elements to ensure the "last-in" element is always made the "first-out" (front) of our primary queue.

## 📝 Step-by-Step Algorithm

We will use two `std::queue<int>` objects, `q1` and `q2`. `q1` will be our main queue, where its front element will always represent the top of our simulated stack. `q2` will serve as a temporary helper queue.

1.  **`MyStack()` Constructor**:
    *   Initialize both `q1` and `q2` as empty queues. No explicit code is needed as `std::queue` objects are empty by default upon construction.

2.  **`push(int x)` Operation**:
    *   **Step 1**: Transfer all elements from `q1` to `q2`.
        *   While `q1` is not empty, take the element from `q1.front()`, push it into `q2`, and then `q1.pop()`.
        *   After this loop, `q1` will be empty, and `q2` will contain all the previous stack elements in their original relative order.
    *   **Step 2**: Push the new element `x` into `q1`.
        *   Since `q1` is now empty, `x` becomes the first and only element in `q1`, effectively placing it at the front. This `x` is the new stack top.
    *   **Step 3**: Transfer all elements back from `q2` to `q1`.
        *   While `q2` is not empty, take the element from `q2.front()`, push it into `q1`, and then `q2.pop()`.
        *   These elements will be added to the back of `q1`, behind `x`.
    *   After these three steps, `q1` will contain `x` at its front, followed by all the elements that were previously in the stack, maintaining their relative order.

3.  **`pop()` Operation**:
    *   Since the `push` operation ensures that the stack's top element is always at `q1.front()`, simply retrieve this element using `q1.front()`, then remove it using `q1.pop()`, and return the retrieved value.

4.  **`top()` Operation**:
    *   Similar to `pop()`, the stack's top element is always at `q1.front()`. Simply return `q1.front()` without removing it.

5.  **`empty()` Operation**:
    *   The stack is considered empty if and only if `q1` contains no elements. Return the result of `q1.empty()`.

## 💻 Solution
```cpp
#include <queue> // Required for using std::queue

class MyStack {
public:
    // Declare two queues.
    // q1 will be our primary queue, always holding the stack's top element at its front.
    // q2 will serve as an auxiliary queue for temporarily holding elements during push operations.
    std::queue<int> q1;
    std::queue<int> q2;

    // Constructor: Initializes the MyStack object.
    // Queues are default-constructed as empty, so no explicit action is needed here.
    MyStack() {
        // No specific initialization logic required as queues are empty by default.
    }
    
    // Pushes element x to the top of the stack.
    // This operation is O(N) because it involves moving all existing elements.
    void push(int x) {
        // Step 1: Move all existing elements from q1 to q2.
        // This effectively empties q1 and preserves the relative order of elements in q2.
        // After this loop, q1 is empty, and q2 contains all previous stack elements.
        while (!q1.empty()) {
            q2.push(q1.front()); // Add element from q1's front to q2's back
            q1.pop();            // Remove element from q1's front
        }
        
        // Step 2: Push the new element x into q1.
        // Since q1 was just emptied, x becomes the first and only element in q1.
        // This means x is now at the front of q1, making it the new stack top.
        q1.push(x);
        
        // Step 3: Move all elements back from q2 to q1.
        // These elements will be pushed to the back of q1, behind 'x'.
        // This restores the original elements to q1, but now 'x' is at the very front.
        while (!q2.empty()) {
            q1.push(q2.front()); // Add element from q2's front to q1's back
            q2.pop();            // Remove element from q2's front
        }
    }
    
    // Removes the element on the top of the stack and returns it.
    // This operation is O(1) because the top element is always at q1's front.
    int pop() {
       // The stack's top element is always at the front of q1.
       int ans = q1.front(); // Get the top element
       q1.pop();             // Remove the top element
       return ans;           // Return the removed element
    }
    
    // Returns the element on the top of the stack.
    // This operation is O(1) because the top element is always at q1's front.
    int top() {
        // The stack's top element is always at the front of q1.
        return q1.front(); // Return the top element without removing it
    }
    
    // Returns true if the stack is empty, false otherwise.
    // This operation is O(1) as it only checks the size of q1.
    bool empty() {
        // The stack is empty if and only if q1 is empty.
        // The expression `true?q1.empty():false` is equivalent to simply `q1.empty()`.
        return q1.empty(); 
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time - `push`** | O(N) | In the worst case, all `N` existing elements are moved from `q1` to `q2` and then back to `q1`. |
| **Time - `pop`** | O(1) | Only involves a single `front()` and `pop()` operation on `q1`. |
| **Time - `top`** | O(1) | Only involves a single `front()` operation on `q1`. |
| **Time - `empty`** | O(1) | Only involves checking if `q1` is empty. |
| **Space** | O(N) | Two queues are used to store up to `N` elements, where `N` is the current number of elements in the stack. |

## 🔗 Related Problems
- 232. Implement Queue using Stacks
- 155. Min Stack
- 716. Max Stack (Premium)