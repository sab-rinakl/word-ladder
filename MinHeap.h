#include <exception>
#include <vector>

template<class T>
class MinHeap {
public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
       This should work for any d >= 2,
       but doesn't have to do anything for smaller d.*/

    ~MinHeap(){};

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;
    /* returns the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    bool isEmpty();
    /* returns true if there are no elements on the heap. */

    int findMinIndex(int i);
    /* finds smallest child of node and returns its index */

    void swapNode(int i, int j);
    /* swaps nodes of two given indicies */

    void updatePriority(T item, int priority);
    /* updates priority */

private:
    int num, priority;
    std::vector<std::pair<T, int>> pairs;
};

template<class T>
MinHeap<T>::MinHeap(int d) {
    num = d;
}

template<class T>
void MinHeap<T>::add(T item, int priority) {
    std::pair<T, int> node;
    node.first = item;
    node.second = priority;
    pairs.push_back(node);
    int node_index = pairs.size() - 1;
    while (node_index > 0) {
        if (pairs[node_index].second < pairs[(node_index - 1) / num].second) {
            MinHeap<T>::swapNode(node_index, (node_index - 1) / num);
        }
        if (pairs[node_index].second == pairs[(node_index - 1) / num].second) {
            if (pairs[node_index].first < pairs[(node_index - 1) / num].first) {
                MinHeap<T>::swapNode(node_index, (node_index - 1) / num);
            }
        }

        node_index = (node_index - 1) / num;
    }
}

template<class T>
const T& MinHeap<T>::peek() const {
    if (pairs.empty()) {
        throw std::exception();
    }
    return pairs[0].first;
}

template<class T>
void MinHeap<T>::remove() {
    if (pairs.empty()) {
        throw std::exception();
    }
    int min_index, prev_index;
    MinHeap<T>::swapNode(0, pairs.size() - 1);
    pairs.erase(pairs.end() - 1);
    int i = 0;
    while (true) {
        prev_index = i;
        min_index = findMinIndex(i);
        if (prev_index == min_index) {
            break;
        }
        MinHeap<T>::swapNode(prev_index, min_index);
        i = min_index;
    }
}

template<class T>
bool MinHeap<T>::isEmpty() {
    if (pairs.empty()) {
        return true;
    }
    return false;
}

template<class T>
int MinHeap<T>::findMinIndex(int i) {
    int min_index = i;
    for (int j = 0; j <= num; j++) {
        if ((size_t)(num * i) + j >= pairs.size()) {
            return min_index;
        }
        if (pairs[(num * i) + j].second < pairs[min_index].second) {
            min_index = (num * i) + j;
        }
        if (pairs[(num * i) + j].second == pairs[min_index].second) {
            if (pairs[(num * i) + j].first < pairs[min_index].first) {
                min_index = (num * i) + j;
            }
        }
    }
    return min_index;
}

template<class T>
void MinHeap<T>::swapNode(int i, int j) {
    std::pair<T, int> temp;
    temp = pairs[i];
    pairs[i] = pairs[j];
    pairs[j] = temp;
}

template<class T>
void MinHeap<T>::updatePriority(T item, int priority) {
    for (size_t i = 0; i < pairs.size(); i++) {
        if (item == pairs[i].first) {
            while (true) {
                int prev_index = i;
                int min_index = findMinIndex(i);
                if (prev_index == min_index) {
                    break;
                }
                MinHeap<T>::swapNode(prev_index, min_index);
                i = min_index;
            }
            pairs.erase(pairs.end() - 1);
            MinHeap<T>::add(item, priority);
        }
    }
}