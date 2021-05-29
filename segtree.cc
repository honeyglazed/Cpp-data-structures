#include <iostream>

#define ll long long
#define mod 1000000007

using namespace std;

class SegementSumTree {
    public:
        SegementSumTree(vector<int> arr) {
            // top node is tree_[1], tree_[n] = arr[0] .. tree_[2n-1] = arr[n-1]
            tree_ = vector<int>(2*arr.size());
            size_ = arr.size();
            for (int i=size_; i<2*size_; ++i) {
                tree[i] = arr[i-size_];
            }
            for (int i=size_-1; i>0; --i) {
                tree_[i] = tree_[2*i] + tree_[2*i+1];
            }
        }

        void sum(int l, int r) {
            l += size_; r += size;
            int s = 0;
            while (l <= r) {
                // if L is odd(right child), add value
                if (l&1) s += tree_[l++];
                // if R is even(left child), add value
                if (!r&1) s += tree_[r--];
                l /= 2; // same as l = l/2;
                r /= 2;
            }
        }

        // add x to value at k
        void add(int k, int x) {
            k += size_;
            tree_[k] += x;
            while (k/2 > 0) {
                k = k/2;
                tree_[k] = tree[2*k] + tree[2*k+1]; 
            }
        }

     private:
        vector<int> tree_;
        int size_;

}

int main() {
    return 0;
}

