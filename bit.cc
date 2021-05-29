#include <iostream>
#include <vector>

#define ll long long
#define mod 1000000007

using namespace std;

/* Binary Index Tree
 *
 * Good for performing range sum queries on a mutable array.
 *
 * Assume 1-index definition.
 *
 * Inspiration: Every number can be represented as the sum of powers of 2. 13 = 8 + 4 + 1.
 *              So each index can represent a partial sum value. So to get a range of [1, 13],
 *              we can break it down into partial sums of length 1 + 4 + 8. This is just
 *              bit[13] (length of 1) + bit[12] (length of 4) + bit[8] (length of 8)
 *
 *              0 1 2 3 4 5 6
 * Input array: 4 8 2 0 5 9 0
 *
 * Tree is represented as an array where each position k, bit[k] contains sum of values in a range
 * of the original input array that ends in position k and has length p(k). This means bit[k]
 * contains the sum of [k-p(k)+1, k]. p(k) is (1<<r) where r is the lowest set bit in k.
 *
 * If k is an odd number, bit[k] only contains the single value at arr[k]
 * If k is a power of 2, bit[k] will contain the range sum of [1, k]
 *
 *
 * O(logn) for query and sum
 * 
 */
class BIT {
    public:
        BIT(int n) {
            bit_ = vector<int>(n+1); // 1-indexed
            size_ = n;
        }

        BIT(vector<int> arr) {
            bit_ = arr; // convert arr to bit
            size_ = arr.size();
            for (int i = 1; i <= size_; ++i) {
                int j = i+(i&-1); // adding the value to the next higher index
                if (j <= size_) {
                    bit_[j] += bit_[i];
                }
            }
        }

        // Returns the sum of the array in the range [1, k]
        int sum(int k) {
            int s = 0;
            while (k > 0) {
                s += bit_[k];
                // lowest set bit of k
                // Example: k=13, lowest set bit is 1
                //          k=12, lowest set bit is 4
                //          k=8, lowest set bit is 8
                //          k=0, done
                k -= k&-k;
            }
            return s;
        }

        int sum_range(int l, int r) {
            return sum(r) - sum(l-1);
        }

        // k - the 1-index to modify
        // val - the value to add
        void add(int k, int val) {
            while (k <= size_) {
                bit_[k] += val;
                k += k&-k;
            }
        }

    private:
        vector<int> bit_;
        int size_;
};

int main() {
    auto bit = BIT(5);
    bit.add(1,3);
    bit.add(2,2);
    bit.add(3,4);
    bit.add(4,4);
    bit.add(5,5);
    cout << bit.sum_range(3,5);
    cout << bit.sum(4);
}
