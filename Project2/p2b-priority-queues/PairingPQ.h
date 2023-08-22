// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure
            //       to initialize it here.
            explicit Node(const TYPE &val): 
                elt{ val }, 
                child{ nullptr }, 
                sibling{ nullptr }, 
                parent{ nullptr }
            {}

            // Description: Allows access to the element at that Node's
            //              position. There are two versions, getElt() and a
            //              dereference operator, use whichever one seems
            //              more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            // const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data
            // members of this Node class from within the PairingPQ class.
            // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
            // function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node *parent;
            // TODO: Add one extra pointer (parent or previous) as desired.
    }; // Node


    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, rootPtr{ nullptr }, count{ 0 } {
        // TODO: Implement this function.
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, rootPtr{ nullptr }, count{ 0 } {
        // // TODO: Implement this function.
        for (InputIterator it = start; it != end; ++it){
            push(*it);
        }
        // // These lines are present only so that this provided file compiles.
        // (void)start; // TODO: Delete this line
        // (void)end;   // TODO: Delete this line
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare }, rootPtr{ nullptr }, count{ 0 } {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
        std::deque<Node*> containerQueue;
        Node* currentPtr;  
        containerQueue.push_back(other.rootPtr);
        while (!containerQueue.empty()){
            currentPtr = containerQueue.front();
            containerQueue.pop_front();
            if (currentPtr -> child != nullptr){
                containerQueue.push_back(currentPtr -> child);
            }
            if (currentPtr -> sibling != nullptr){
                containerQueue.push_back(currentPtr -> sibling);
            }
            push(currentPtr -> getElt());
        }
        
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs) {
        // // TODO: Implement this function.
        // // HINT: Use the copy-swap method from the "Arrays and Containers"
        // //       lecture.
        PairingPQ temp(rhs);
        std::swap(rootPtr, temp.rootPtr);
        std::swap(count, temp.count);
        return *this;
        // // This line is present only so that this provided file compiles.
        // (void)rhs; // TODO: Delete this line

        // return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.
        std::deque<Node*> containerQueue;
        Node* currentPtr;
        if (rootPtr != 0){
            containerQueue.push_back(rootPtr);
        }
        while (!containerQueue.empty()){
            currentPtr = containerQueue.front();
            containerQueue.pop_front();
            if (currentPtr -> child != nullptr){
                containerQueue.push_back(currentPtr -> child);
            }
            if (currentPtr -> sibling != nullptr){
                containerQueue.push_back(currentPtr -> sibling);
            }
            delete currentPtr;
        }
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant. You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        std::deque<Node*> containerQueue;
        Node* currentPtr;
        containerQueue.push_back(rootPtr);
        if (rootPtr == nullptr){
            return;
        }
        while (!containerQueue.empty()){
            currentPtr = containerQueue.front();
            containerQueue.pop_front();
            if (currentPtr -> child != nullptr){
                containerQueue.push_back(currentPtr -> child);
            }
            if (currentPtr -> sibling != nullptr){
                containerQueue.push_back(currentPtr -> sibling);
            }
            currentPtr -> child = nullptr;
            currentPtr -> sibling = nullptr;
            currentPtr -> parent = nullptr;
            if (rootPtr != currentPtr){
                rootPtr = meld(rootPtr, currentPtr);
            } 
        }
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely in
    //              the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    //       an element when the pairing heap is empty. Though you are
    //       welcome to if you are familiar with them, you do not need to use
    //       exceptions in this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        // TODO: Implement this function.
        std::deque<Node*> containerDeque;
        Node* newPtr = rootPtr -> child;
        Node* prevPtr;
        while (newPtr != nullptr){
            prevPtr = newPtr;
            containerDeque.push_back(newPtr);
            newPtr = newPtr -> sibling;
            prevPtr -> sibling = nullptr;
            prevPtr -> parent = nullptr;
        }
        delete rootPtr;
        while (containerDeque.size() > 1){
            containerDeque.push_back(meld(containerDeque[0],containerDeque[1]));
            containerDeque.pop_front();
            containerDeque.pop_front();
        }
        if (containerDeque.size() == 1){
            rootPtr = containerDeque[0];
        }
        else if (containerDeque.size() == 0){
            rootPtr = nullptr;
        }
        --count;
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // // TODO: Implement this function
        return rootPtr -> getElt();
        // // These lines are present only so that this provided file compiles.
        // static TYPE temp; // TODO: Delete this line
        // return temp;      // TODO: Delete or change this line
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function
        return count; // TODO: Delete or change this line
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function
        if (count == 0){
            return true;
        }
        return false; // TODO: Delete or change this line
    } // empty()


    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value. Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //               extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    void updateElt(Node* node, const TYPE &new_value) {
        // // TODO: Implement this function
        node -> elt = new_value;
        // if (std::compare(node -> parent -> getElt(), new_value)){
        if (this -> compare(new_value, node -> parent -> getElt())){
            return;
        }
        // left most
        if (node -> parent -> child == node){
            node -> parent -> child = node -> sibling;
        }
        else {
            Node* tempPtr = node -> parent -> child;
            while (tempPtr -> sibling != node){
                tempPtr = tempPtr -> sibling;
            }
            tempPtr -> sibling = node -> sibling;

        }
        node -> sibling = nullptr;
        node -> parent = nullptr;
        rootPtr = meld(rootPtr, node);
        // }
        
        // // These lines are present only so that this provided file compiles.
        // (void)node;      // TODO: Delete this line
        // (void)new_value; // TODO: Delete this line
    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    // Runtime: O(1)
    Node* addNode(const TYPE &val) {
        // // TODO: Implement this function
        Node* newNode = new Node(val);
        if (!empty()){
            rootPtr = meld(rootPtr, newNode);
        }
        else{
            rootPtr = newNode;
        }
        ++count;
        return newNode;
        // // This line is present only so that this provided file compiles.
        // (void)val;      // TODO: Delete this line
        // return nullptr; // TODO: Delete or change this line
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you
    //       require here.
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    //       papers).
    Node* rootPtr;
    std::size_t count;
    Node* meld(Node* &aPtr, Node* &bPtr) {
        if (this -> compare(aPtr -> getElt(), bPtr -> getElt())){
            aPtr -> sibling = bPtr -> child;
            bPtr -> child = aPtr;
            aPtr -> parent = bPtr;
            return bPtr;
        }
        bPtr -> sibling = aPtr -> child;
        aPtr -> child = bPtr;
        bPtr -> parent = aPtr; 
        return aPtr;
    }
    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};


#endif // PAIRINGPQ_H
