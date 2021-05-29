#include <iostream>
#include <vector>
#include <cmath>

#define ll long long
#define mod 1000000007

using namespace std;

/* Range Minimum Query
 *
 * Intuition: Any number can be broken down into a sum of powers of 2. Ex. 13 (1101) = 8 + 4 + 1
 *            Thus, an interval of some length x and be broken down into small intervals with
 *            lengths that are power of 2. So lets precompute answers to our queries for every
 *            interval with lengths that are power of 2.
 *
 *              0  1  2  3  4  5  6
 * Given arr = [1, 5, 3, 1, 4, 2, 7]
 *
 * Sparse Table: st[i][j] = minimum value in range [j, j+2^i-1] of length 2^i
 *               This splits into two intervals of length 2^(i-1):
 *               [j, j+2^(i-1)-1] and [j+2^(i-1), j+2^i-1]
 *
 * Size of table: (K+1) * N where N is the max size of the array. 2^(log2(N)) is the max length
 *                we need to support, so K >= ceil(log2(N)).
 * +---+---+---+---+---+---+---+---+
 * |   | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
 * +---+---+---+---+---+---+---+---+
 * | 0 | 1 | 5 | 3 | 1 | 4 | 2 | 7 |
 * | 1 | 1 | 3 | 1 | 1 | 2 | 2 |   |
 * | 2 | 1 | 1 | 1 | 1 |   |   |   |
 * +---+---+---+---+---+---+---+---+
 *
 * Given a range [l,r], we know it has length (r-l+1). Split this into overlapping intervals
 * of the largest power of 2 size less than (r-l+1). So we need to find floor(log2(r-1+1)) which 
 * gives us which row in the ST to look at.
 *
 * The two intervals would start at l and r-(1<<i)+1
 *
 * Ex. query = [1, 3], length = 3, largest power of 2 is 2. So we can use two intervals of length
 * 2 to find the answer to the query. These two intervals are [1, 2] and [2, 3]. This corresponds
 * to st[i][1] and st[i][2 (3-largest_power+1)] where i is the floor(log2(3))
 *
 *
 * O(nlogn) preprocessing, O(1) minimum query
 */
class RMQ {
    public:
        RMQ(vector<int> arr) {
            // Find the smallest 2^k that can accomdate `arr`
            k_ = (int)ceil(log2(arr.size()));

            // st[i][j] is the MQ for array starting at arr[j] of length 2^i
            st_ = vector<vector<int>>(k_+1, vector<int>(arr.size(), 0));

            // Base case: arrays of size 1
            for (int j=0; j<arr.size(); ++j) {
               st_[0][j] = arr[j];
            }
            // for arrays of size 2^i
            for (int i=1; i<=k_; ++i) {
                // Note that 2^i == 1<<i
                for (int j=0; j+(1<<i)<=arr.size(); ++j) {
                    // Min of the arrays 2^(i-1) starting at j and j+2^(i-1)
                    st_[i][j] = min(st_[i-1][j], st_[i-1][j+(1<<(i-1))]);
                }
            }
            // Cache of log2 binaries - log2(x) = y where x is the length of array, y is the row
            // in the ST
            //
            // Note this we are actually doing floor(log2(x))
            log_ = vector<int>(arr.size()+1);
            log_[1] = 0;
            for (int i=2; i<=k_; ++i) {
                log_[i] = log_[i/2] + 1;
            }
        }

        // Returns the minimum element in the `arr` between range [l, r]
        int RangeMin(int l, int r) {
            int i = log_[r-l+1];
            return min(st_[i][l], st_[i][r-(1<<i)+1]);
        }
    private:
        vector<vector<int>> st_;
        vector<int> log_;
        int k_;
};

int main() {
    vector<int> v = {1,5,3,1,4,2,7};
    RMQ rmq = RMQ(v);
    cout << rmq.RangeMin(5,6) << '\n';
}
