# 0225-implement-stack-using-queues

## 📋 Problem Description
Implement a Last-In-First-Out (LIFO) stack using only the standard operations of a First-In-First-Out (FIFO) queue. The `MyStack` class should support all the functions of a normal stack: `push`, `top`, `pop`, and `empty`.

Specifically, you need to implement the following methods:
*   `void push(int x)`: Adds element `x` to the top of the stack.
*   `int pop()`: Removes and returns the element currently at the top of the stack.
*   `int top()`: Returns the element currently at the top of the stack without removing it.
*   `boolean empty()`: Returns `true` if the stack is empty, `false` otherwise.

You are restricted to using only standard queue operations: `push to back` (enqueue), `peek/pop from front` (dequeue), `size`, and `is empty`.

## 🔍 Examples
```
Input:
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
Output:
[null, null, null, 2, 2, false]

Explanation:
MyStack myStack = new MyStack();
myStack.push(1);   // Stack: [1]
myStack.push(2);   // Stack: [1, 2] (2 is top)
myStack.top();     // return 2
myStack.pop();     // return 2, Stack: [1]
myStack.empty();   // return False
```

## 📌 Constraints
*   `1 <= x <= 9`
*   At most `100` calls will be made to `push`, `pop`, `top`, and `empty`.
*   All calls to `pop` and `top` are guaranteed to be valid (i.e., the stack will not be empty when these operations are called).

## 🤔 Understanding the Problem
The core challenge here is to simulate a Last-In-First-Out (LIFO) data structure, a stack, using only First-In-First-Out (FIFO) data structures, queues. This is non-trivial because a queue naturally processes elements in the order they arrive, while a stack needs to process the most recently added element first. We need to devise a strategy to make the "last-in" element always accessible at the "front" of our primary queue, effectively reversing the natural queue order for the top element.

## 💡 Core Idea
The key insight is to maintain the invariant that the "top" element of the stack is always at the front of one of our queues. When a new element is pushed, it must become the new "top," meaning it needs to be moved to the front of the primary queue, effectively reordering all existing elements behind it.

## 🧠 Approach — Data Structure Design / Queue Manipulation
This problem falls under the "Data Structure Design" pattern, specifically focusing on "Queue Manipulation." We use two queues to achieve the stack's LIFO behavior. The reason this pattern fits is that queues inherently operate on a FIFO principle, which is opposite to a stack's LIFO. To overcome this, we leverage a second auxiliary queue to temporarily store elements, allowing us to reorder them such that the most recently added element always ends up at the front of our primary queue, thus simulating the stack's top.

## 📝 Step-by-Step Algorithm

1.  **Initialization (`MyStack()`):**
    *   Create two empty queues, `q1` and `q2`. `q1` will primarily hold our stack elements, with its front representing the stack's top. `q2` will serve as an auxiliary queue for reordering elements during `push` operations.

2.  **Push Operation (`push(int x)`):**
    *   To make the new element `x` the "top" of the stack (i.e., the front of `q1`), we need to move all existing elements from `q1` to `q2`.
    *   While `q1` is not empty, dequeue an element from `q1` and enqueue it into `q2`.
    *   Now, `q1` is empty. Enqueue the new element `x` into `q1`. This makes `x` the very first element in `q1`.
    *   Finally, move all elements back from `q2` to `q1`. While `q2` is not empty, dequeue an element from `q2` and enqueue it into `q1`.
    *   After these steps, `q1` contains `x` at its front, followed by all the elements that were originally in `q1`, preserving their relative order. This ensures `x` is the new "top."

3.  **Pop Operation (`pop()`):**
    *   Since the `push` operation ensures the stack's top element is always at the front of `q1`, simply dequeue and return the element from `q1`.

4.  **Top Operation (`top()`):**
    *   Similar to `pop`, the stack's top element is at the front of `q1`. Simply peek at (return) the element at the front of `q1` without removing it.

5.  **Empty Operation (`empty()`):**
    *   The stack is empty if and only if `q1` is empty. Return `true` if `q1` is empty, `false` otherwise.

## 💻 Solution

```cpp
#include <queue> // Required for using std::queue

class MyStack {
public:
    // q1 will be our primary queue, where the front always represents the stack's top.
    // q2 will be an auxiliary queue used for reordering elements during push operations.
    std::queue<int> q1;
    std::queue<int> q2;

    // Constructor: Initializes the MyStack object.
    // No specific actions needed as queues are default-constructed empty.
    MyStack() {
        
    }
    
    // Pushes element x to the top of the stack.
    // This operation is O(N) because it involves reordering all existing elements.
    void push(int x) {
        // Step 1: Move all existing elements from q1 to q2.
        // After this loop, q1 will be empty, and q2 will hold all previous stack elements.
        while(!q1.empty()){
            q2.push(q1.front()); // Enqueue element from q1's front to q2's back
            q1.pop();            // Dequeue element from q1's front
        }
        
        // Step 2: Push the new element x to q1.
        // This makes x the new front of q1, which will be our stack's top.
        q1.push(x);
        
        // Step 3: Move all elements back from q2 to q1.
        // These elements will now be behind x in q1, maintaining LIFO order.
        while(!q2.empty()){
            q1.push(q2.front()); // Enqueue element from q2's front to q1's back
            q2.pop();            // Dequeue element from q2's front
        }
        // After these steps, q1's front is 'x', followed by the elements that were previously in q1.
        // Example trace:
        // Initial: q1=[], q2=[]
        // push(1): q1=[], q2=[] -> q1.push(1) -> q1=[1], q2=[]
        // push(2): q1=[1], q2=[] -> q2.push(1), q1.pop() -> q1=[], q2=[1]
        //          q1.push(2) -> q1=[2], q2=[1]
        //          q1.push(1), q2.pop() -> q1=[2,1], q2=[]
        //          Stack state: [1, 2] (2 is top)
        // push(3): q1=[2,1], q2=[] -> q2.push(2), q1.pop() -> q1=[1], q2=[2]
        //          q2.push(1), q1.pop() -> q1=[], q2=[2,1]
        //          q1.push(3) -> q1=[3], q2=[2,1]
        //          q1.push(2), q2.pop() -> q1=[3,2], q2=[1]
        //          q1.push(1), q2.pop() -> q1=[3,2,1], q2=[]
        //          Stack state: [1, 2, 3] (3 is top)
    }
    
    // Removes the element on the top of the stack and returns it.
    // This operation is O(1) because the top element is always at q1's front.
    int pop() {
       // Get the element at the front of q1 (which is the stack's top).
       int ans = q1.front();
       // Remove the element from q1.
       q1.pop();
       // Return the removed element.
       return ans;
    }
    
    // Returns the element on the top of the stack without removing it.
    // This operation is O(1) because the top element is always at q1's front.
    int top() {
        // Simply return the element at the front of q1.
        return q1.front();
    }
    
    // Returns true if the stack is empty, false otherwise.
    // This operation is O(1).
    bool empty() {
        // The stack is empty if our primary queue q1 is empty.
        // The expression `true?q1.empty():false` is functionally equivalent to just `q1.empty()`.
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
| **Time (push)** | O(N) | In the worst case, all `N` existing elements are moved from `q1` to `q2`, then the new element is added, then all `N` elements are moved back from `q2` to `q1`. Each move involves a dequeue and an enqueue operation. |
| **Time (pop)** | O(1) | Directly dequeues the front element from `q1`, which is a constant time operation for standard queues. |
| **Time (top)** | O(1) | Directly peeks at the front element of `q1`, which is a constant time operation. |
| **Time (empty)** | O(1) | Checks if `q1` is empty, which is a constant time operation. |
| **Space** | O(N) | Stores all `N` elements in the queues. In the worst case, all elements reside in `q1`. |

## 🔗 Related Problems
*   232. Implement Queue using Stacks
*   155. Min Stack
*   716. Max Stack