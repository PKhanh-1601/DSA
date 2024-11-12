// STT:
// Full Name: Ngô Hoàng Phương  Khanh
// Student ID: 22520639
// Classwork & Homework
// Notes or Remarks: ......

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <limits>
#include <random>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <queue>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>
#include <set>
#define MAX_PATTERN_SIZE 1000

using namespace std;
using namespace std::chrono;

int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int BinarySearch(int arr[], int size, int target) {
    int index = binarySearch(arr, size, target);

    if (index == -1) {
        return 0;
    }

    int count = 1;
    int left = index - 1;
    while (left >= 0 && arr[left] == target) {
        count++;
        left--;
    }

    int right = index + 1;
    while (right < size && arr[right] == target) {
        count++;
        right++;
    }

    return count;
}

void Problem1() {
    int size;
    cout << "Enter the array size: ";
    cin >> size;
    int arr[size];

    cout << "Enter the sorted array: ";
    for(int i = 0; i < size; i++){
        cin >> arr[i];
    }

    int target;
    cout << "Enter the target value: ";
    cin >> target;

    cout << "The target value appears " << BinarySearch(arr, size, target) << " times";
}

int jumpSearch(int arr[], int size, int target) {
    int step = sqrt(size);
    int prev = 0;

    double avgDiff = 0;
    for(int i = 1; i < size; i++) {
        avgDiff += abs(arr[i] - arr[i-1]);
    }
    avgDiff /= (size - 1);

    if(avgDiff > (arr[size-1] - arr[0]) / size) {
        step = step * 1.5;
    }
    else if(avgDiff < (arr[size-1] - arr[0]) / (size * 2)) {
        step = max(step / 2, 1);
    }

    while(prev < size && arr[min(step, size)-1] < target) {
        prev = step;
        step += sqrt(size);
        if(prev >= size){
            return -1;
        }
    }

    while(prev < min(step, size)) {
        if(arr[prev] == target){
            return prev;
        }
        prev++;
    }

    return -1;
}

void Problem2() {
    int size;
    cout << "Enter the array size: ";
    cin >> size;
    int arr[size];

    cout << "Enter the sorted array: ";
    for(int i = 0; i < size; i++){
        cin >> arr[i];
    }

    int target;
    cout << "Enter the target value: ";
    cin >> target;

    int result = jumpSearch(arr, size, target);

    if(result != -1) {
        cout << "The target value found at index " << result << endl;
    } else {
        cout << "The target value not found in array" << endl;
    }
}

int interpolationSearch(const string A[], int n, const string& x) {
    int low = 0, high = n - 1;

    while (low <= high && x[0] >= A[low][0] && x[0] <= A[high][0]) {
        if (low == high) {
            return (A[low] == x) ? low : -1;
        }

        int pos = low + ((high - low) * (x[0] - A[low][0])) / (A[high][0] - A[low][0]);

        if (A[pos] == x) {
            return pos;
        }

        if (A[pos][0] < x[0]) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return -1;
}

void Problem3() {
    int n;
    cout << "Enter the array size: ";
    cin >> n;

    string A[n];
    cout << "Enter the array of strings: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    string x;
    cout << "Enter the target string: ";
    cin >> x;

    int result = interpolationSearch(A, n, x);

    if (result != -1) {
        cout << "The target string found at index " << result << endl;
    } else {
        cout << "The target string not found in the array" << endl;
    }
}

int findMissingNumber(int A[], int n) {
    int expected_sum = n * (n + 1) / 2;

    int actual_sum = 0;
    for (int i = 0; i < n; i++) {
        actual_sum += A[i];
    }

    return expected_sum - actual_sum;
}

void Problem4() {
    int n;
    cout << "Enter the total count of numbers from 0 to n (including the missing one): ";
    cin >> n;

    int A[n - 1];
    cout << "Enter the array elements: ";
    for (int i = 0; i < n - 1; i++) {
        cin >> A[i];
    }

    int missingNumber = findMissingNumber(A, n - 1);
    cout << "The missing number is " << missingNumber << endl;
}

void linearSearch(const vector<int>& arr, int target, atomic<int>& comparisons, atomic<bool>& found) {
    comparisons = 0;
    for (int i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] == target) {
            found = true;
            return;
        }
    }
    found = false;
}

void vectorBinarySearch(const vector<int>& arr, int target, atomic<int>& comparisons, atomic<bool>& found) {
    comparisons = 0;
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            found = true;
            return;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    found = false;
}

void JumpSearch(const vector<int>& arr, int target, atomic<int>& comparisons, atomic<bool>& found) {
    comparisons = 0;
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < target) {
        comparisons++;
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            found = false;
            return;
        }
    }

    while (arr[prev] < target) {
        comparisons++;
        prev++;
        if (prev == min(step, n)) {
            found = false;
            return;
        }
    }

    comparisons++;
    found = (arr[prev] == target);
}

void runSearches(const vector<int>& arr, int target, int iterations = 10000) {
    atomic<int> linearComparisons{0}, binaryComparisons{0}, jumpComparisons{0};
    atomic<bool> linearFound{false}, binaryFound{false}, jumpFound{false};

    long long totalLinearTime = 0;
    long long totalBinaryTime = 0;
    long long totalJumpTime = 0;

    for (int i = 0; i < iterations; i++) {
        auto linearStart = high_resolution_clock::now();
        linearSearch(arr, target, linearComparisons, linearFound);
        auto linearEnd = high_resolution_clock::now();
        totalLinearTime += duration_cast<nanoseconds>(linearEnd - linearStart).count();

        auto binaryStart = high_resolution_clock::now();
        vectorBinarySearch(arr, target, binaryComparisons, binaryFound);
        auto binaryEnd = high_resolution_clock::now();
        totalBinaryTime += duration_cast<nanoseconds>(binaryEnd - binaryStart).count();

        auto jumpStart = high_resolution_clock::now();
        JumpSearch(arr, target, jumpComparisons, jumpFound);
        auto jumpEnd = high_resolution_clock::now();
        totalJumpTime += duration_cast<nanoseconds>(jumpEnd - jumpStart).count();
    }

    double avgLinearTime = static_cast<double>(totalLinearTime) / iterations;
    double avgBinaryTime = static_cast<double>(totalBinaryTime) / iterations;
    double avgJumpTime = static_cast<double>(totalJumpTime) / iterations;

    cout << fixed << setprecision(2);
    cout << "\nResults after " << iterations << " iterations:\n";
    cout << "-----------------------\n";
    cout << "Linear Search:\n";
    cout << "  Comparisons: " << linearComparisons
         << "\n  Average Time: " << avgLinearTime << " nanoseconds"
         << "\n  Target: " << (linearFound ? "found" : "not found") << "\n\n";

    cout << "Binary Search:\n";
    cout << "  Comparisons: " << binaryComparisons
         << "\n  Average Time: " << avgBinaryTime << " nanoseconds"
         << "\n  Target: " << (binaryFound ? "found" : "not found") << "\n\n";

    cout << "Jump Search:\n";
    cout << "  Comparisons: " << jumpComparisons
         << "\n  Average Time: " << avgJumpTime << " nanoseconds"
         << "\n  Target: " << (jumpFound ? "found" : "not found") << "\n\n";

    string mostComparisons;
    if (linearComparisons >= binaryComparisons && linearComparisons >= jumpComparisons) {
        mostComparisons = "Linear Search";
    } else if (binaryComparisons >= linearComparisons && binaryComparisons >= jumpComparisons) {
        mostComparisons = "Binary Search";
    } else {
        mostComparisons = "Jump Search";
    }

    string slowest;
    if (avgLinearTime >= avgBinaryTime && avgLinearTime >= avgJumpTime) {
        slowest = "Linear Search";
    } else if (avgBinaryTime >= avgLinearTime && avgBinaryTime >= avgJumpTime) {
        slowest = "Binary Search";
    } else {
        slowest = "Jump Search";
    }

      cout << "-----------------------\n";

    cout << "The most comparisons: " << mostComparisons << "\n";
    cout << "The slowest algorithm: " << slowest << "\n";
}

// Program use 500 sorted element array for example
void Problem5() {
    int n = 500;
    int target;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    cout << "Enter the target value (0 - 499): ";
    cin >> target;

    // sort(arr.begin(), arr.end()); // In case the user want to use unsorted array

    cout << "\nRunning...\n";
    runSearches(arr, target);
}

int bidirectionalBinarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int leftMid = left + (mid - left) / 2;
        int rightMid = mid + (right - mid) / 2;

        if (arr[leftMid] == target) return leftMid;
        if (arr[mid] == target) return mid;
        if (arr[rightMid] == target) return rightMid;

        if (target < arr[leftMid]) {
            right = leftMid - 1;
        } else if (target > arr[rightMid]) {
            left = rightMid + 1;
        } else if (target < arr[mid]) {
            right = mid - 1;
            left = leftMid + 1;
        } else {
            left = mid + 1;
            right = rightMid - 1;
        }
    }

    return -1;
}

void runBinarySearches(int arr[], int size, int target, int iterations = 10000) {
    for (int i = 0; i < 1000; i++) {
        binarySearch(arr, size, target);
        bidirectionalBinarySearch(arr, size, target);
    }

    long long totalRegularTime = 0;
    long long totalBidirectionalTime = 0;
    int regularResult = -1;
    int bidirectionalResult = -1;

    for (int i = 0; i < iterations; i++) {
        auto regularStart = high_resolution_clock::now();
        regularResult = binarySearch(arr, size, target);
        auto regularEnd = high_resolution_clock::now();
        totalRegularTime += duration_cast<nanoseconds>(regularEnd - regularStart).count();

        auto bidirectionalStart = high_resolution_clock::now();
        bidirectionalResult = bidirectionalBinarySearch(arr, size, target);
        auto bidirectionalEnd = high_resolution_clock::now();
        totalBidirectionalTime += duration_cast<nanoseconds>(bidirectionalEnd - bidirectionalStart).count();
    }

    double avgRegularTime = static_cast<double>(totalRegularTime) / iterations;
    double avgBidirectionalTime = static_cast<double>(totalBidirectionalTime) / iterations;

    cout << fixed << setprecision(2);
    cout << "\nResults after " << iterations << " iterations:\n";
    cout << "-----------------------\n";

    cout << "Regular Binary Search:\n";
    cout << "  Result: " << (regularResult != -1 ? "Found at index " + to_string(regularResult) : "Not found")
         << "\n  Average Time: " << avgRegularTime << " nanoseconds\n\n";

    cout << "Bidirectional Binary Search:\n";
    cout << "  Result: " << (bidirectionalResult != -1 ? "Found at index " + to_string(bidirectionalResult) : "Not found")
         << "\n  Average Time: " << avgBidirectionalTime << " nanoseconds\n\n";

    if (regularResult != bidirectionalResult) {
        cout << "WARNING: Search results don't match! This indicates a bug in one of the implementations.\n";
    }

    double timeDiff = abs(avgRegularTime - avgBidirectionalTime);
    double percentDiff = (timeDiff / min(avgRegularTime, avgBidirectionalTime)) * 100;

      cout << "-----------------------\n";

    cout << "The time difference: " << timeDiff << " nanoseconds\n";
    cout << "The percentage difference: " << percentDiff << "%\n";
    cout << "The faster algorithm: "
         << (avgRegularTime < avgBidirectionalTime ? "Regular" : "Bidirectional")
         << " Binary Search\n";
}

void Problem6() {
    const int size = 500;
    int target;
    int arr[size];

    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }

    cout << "Enter the target value to search for (0 - " << size - 1 << "): ";
    cin >> target;

    if (target < 0 || target >= size) {
        cout << "Invalid target value. Please enter a number between 0 and " << size - 1 << ".\n";
        return;
    }

    cout << "\nSearching for target value: " << target;
    runBinarySearches(arr, size, target);
}

int countLessEqual(const vector<int>& arr, int target) {
    int count = 0;
    for (int num : arr) {
        if (num <= target) {
            count++;
        }
    }
    return count;
}

int modifiedBinarySearchForKthSmallest(const vector<int>& arr, int k) {
    if (arr.empty() || k < 1 || k > arr.size()) {
        return -1;
    }

    int left = *min_element(arr.begin(), arr.end());
    int right = *max_element(arr.begin(), arr.end());

    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = countLessEqual(arr, mid);

        if (count < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

int quickSelect(vector<int>& arr, int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }

    int pivotIndex = partition(arr, left, right);
    int count = pivotIndex - left + 1;

    if (count == k) {
        return arr[pivotIndex];
    }
    if (count > k) {
        return quickSelect(arr, left, pivotIndex - 1, k);
    }
    return quickSelect(arr, pivotIndex + 1, right, k - count);
}

void findKthElement(vector<int>& arr, int k) {
    if (arr.empty() || k < 1 || k > arr.size()) {
        cout << "Invalid input parameters!\n";
        return;
    }

    vector<int> arrCopy = arr;

    auto startBinary = chrono::high_resolution_clock::now();
    int resultBinary = modifiedBinarySearchForKthSmallest(arr, k);
    auto endBinary = chrono::high_resolution_clock::now();
    auto durationBinary = chrono::duration_cast<chrono::microseconds>(endBinary - startBinary);

    auto startQuick = chrono::high_resolution_clock::now();
    int resultQuick = quickSelect(arrCopy, 0, arrCopy.size() - 1, k);
    auto endQuick = chrono::high_resolution_clock::now();
    auto durationQuick = chrono::duration_cast<chrono::microseconds>(endQuick - startQuick);

    cout << "\nResults for finding the " << k << "th smallest element:\n";
    cout << "----------------------------------------\n";
    cout << "Modified Binary Search:\n";
    cout << "  Result: " << resultBinary << "\n";
    cout << "  Time: " << durationBinary.count() << " microseconds\n\n";

    cout << "QuickSelect:\n";
    cout << "  Result: " << resultQuick << "\n";
    cout << "  Time: " << durationQuick.count() << " microseconds\n\n";

    sort(arrCopy.begin(), arrCopy.end());
    int actualKth = arrCopy[k - 1];

    cout << "Verification:\n";
    cout << "  Actual " << k << "th smallest: " << actualKth << "\n";
    cout << "  Binary Search " << (resultBinary == actualKth ? "correct" : "incorrect") << "\n";
    cout << "  QuickSelect " << (resultQuick == actualKth ? "correct" : "incorrect") << "\n";
}

void Problem7() {
    random_device rd;
    mt19937 gen(rd());

    int size, k;
    cout << "Enter the size of the array: ";
    cin >> size;
    cout << "Enter k (1 to " << size << "): ";
    cin >> k;

    if (size <= 0 || k < 1 || k > size) {
        cout << "Invalid input parameters!\n";
        return;
    }

    vector<int> arr(size);
    uniform_int_distribution<> dis(1, 1000);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }

    cout << "\nElements of the array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    findKthElement(arr, k);
}

struct Point {
    vector<double> coords;

    Point(const vector<double>& coordinates) : coords(coordinates) {}

    double distance(const Point& other) const {
        double dist = 0;
        for (size_t i = 0; i < coords.size(); i++) {
            double diff = coords[i] - other.coords[i];
            dist += diff * diff;
        }
        return sqrt(dist);
    }
};

struct KDNode {
    Point point;
    KDNode* left;
    KDNode* right;

    KDNode(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    KDNode* root;
    int k;

    KDNode* buildTree(vector<Point>& points, int depth, int start, int end) {
        if (start >= end) return nullptr;

        int axis = depth % k;
        int mid = start + (end - start) / 2;

        nth_element(points.begin() + start, points.begin() + mid,
                   points.begin() + end,
                   [axis](const Point& a, const Point& b) {
                       return a.coords[axis] < b.coords[axis];
                   });

        KDNode* node = new KDNode(points[mid]);
        node->left = buildTree(points, depth + 1, start, mid);
        node->right = buildTree(points, depth + 1, mid + 1, end);

        return node;
    }

    void nearestNeighborSearch(KDNode* node,
                            const Point& target,
                            int depth,
                            Point& bestPoint,
                            double& bestDist) const
    {
        if (!node) {
            return;
        }

        double currentDist = node->point.distance(target);
        if (currentDist < bestDist) {
            bestDist = currentDist;
            bestPoint = node->point;
        }

        int axis = depth % k;
        double axisDist = target.coords[axis] - node->point.coords[axis];

        KDNode* firstSide = (axisDist < 0) ? node->left : node->right;
        KDNode* secondSide = (axisDist < 0) ? node->right : node->left;

        nearestNeighborSearch(firstSide, target, depth + 1, bestPoint, bestDist);

        if (axisDist * axisDist < bestDist) {
            nearestNeighborSearch(secondSide, target, depth + 1, bestPoint, bestDist);
        }
    }

    void cleanup(KDNode* node) {
        if (node) {
            cleanup(node->left);
            cleanup(node->right);
            delete node;
        }
    }

public:
    KDTree(int dimensions) : root(nullptr), k(dimensions) {}

    ~KDTree() {
        cleanup(root);
    }

    void build(vector<Point>& points) {
        root = buildTree(points, 0, 0, points.size());
    }

    Point findNearest(const Point& target) const {
        Point bestPoint(vector<double>(k, 0));
        double bestDist = numeric_limits<double>::max();
        nearestNeighborSearch(root, target, 0, bestPoint, bestDist);
        return bestPoint;
    }
};

Point bruteForceNearest(const vector<Point>& points, const Point& target) {
    Point nearest = points[0];
    double minDist = target.distance(points[0]);

    for (size_t i = 1; i < points.size(); i++) {
        double dist = target.distance(points[i]);
        if (dist < minDist) {
            minDist = dist;
            nearest = points[i];
        }
    }

    return nearest;
}

void printPoint(const Point& p) {
    cout << "(";
    for (size_t i = 0; i < p.coords.size(); i++) {
        cout << fixed << setprecision(2) << p.coords[i];
        if (i < p.coords.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")";
}

void Problem8() {
    random_device rd;
    mt19937 gen(rd());

    int dimensions, numPoints;
    cout << "Enter number of dimensions (2-10): ";
    cin >> dimensions;
    cout << "Enter number of points to generate (100-10000): ";
    cin >> numPoints;

    if (dimensions < 2 || dimensions > 10 || numPoints < 100 || numPoints > 10000) {
        cout << "Invalid input parameters!\n";
        return;
    }

    vector<Point> points;
    uniform_real_distribution<> dis(-100.0, 100.0);

    for (int i = 0; i < numPoints; i++) {
        vector<double> coords;
        for (int j = 0; j < dimensions; j++) {
            coords.push_back(dis(gen));
        }
        points.push_back(Point(coords));
    }

    KDTree kdTree(dimensions);
    auto startBuild = chrono::high_resolution_clock::now();
    kdTree.build(points);
    auto endBuild = chrono::high_resolution_clock::now();
    auto buildTime = chrono::duration_cast<chrono::milliseconds>(endBuild - startBuild);

    vector<double> targetCoords;
    for (int i = 0; i < dimensions; i++) {
        targetCoords.push_back(dis(gen));
    }
    Point target(targetCoords);

    cout << "\nTarget point: ";
    printPoint(target);
    cout << "\n\n";

    auto startKD = chrono::high_resolution_clock::now();
    Point nearestKD = kdTree.findNearest(target);
    auto endKD = chrono::high_resolution_clock::now();
    auto kdTime = chrono::duration_cast<chrono::microseconds>(endKD - startKD);

    auto startBrute = chrono::high_resolution_clock::now();
    Point nearestBrute = bruteForceNearest(points, target);
    auto endBrute = chrono::high_resolution_clock::now();
    auto bruteTime = chrono::duration_cast<chrono::microseconds>(endBrute - startBrute);

    cout << "Results:\n";
    cout << "----------------------------------------\n";
    cout << "K-D Tree Build Time: " << buildTime.count() << " ms\n\n";

    cout << "Nearest Neighbor Search Results:\n";
    cout << "K-D Tree Method:\n";
    cout << "  Nearest point: ";
    printPoint(nearestKD);
    cout << "\n  Distance: " << target.distance(nearestKD);
    cout << "\n  Search time: " << kdTime.count() << " microseconds\n\n";

    cout << "Brute Force Method:\n";
    cout << "  Nearest point: ";
    printPoint(nearestBrute);
    cout << "\n  Distance: " << target.distance(nearestBrute);
    cout << "\n  Search time: " << bruteTime.count() << " microseconds\n\n";

    if (abs(target.distance(nearestKD) - target.distance(nearestBrute)) > 1e-10) {
        cout << "Warning: Different results obtained from K-D tree and brute force methods!\n";
    }

    double speedup = static_cast<double>(bruteTime.count()) / kdTime.count();
    cout << "K-D Tree speedup factor: " << fixed << setprecision(2) << speedup << "x\n";
}

struct Point2D {
    int x, y;
};

double distance(const Point2D& p1, const Point2D& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

pair<Point2D, Point2D> closestPairRec(vector<Point2D>& pointsX, vector<Point2D>& pointsY) {
    int n = pointsX.size();
    if (n <= 3) {
        double minDist = numeric_limits<double>::max();
        pair<Point2D, Point2D> minPair;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double d = distance(pointsX[i], pointsX[j]);
                if (d < minDist) {
                    minDist = d;
                    minPair = {pointsX[i], pointsX[j]};
                }
            }
        }
        return minPair;
    }

    int mid = n / 2;
    Point2D midPoint = pointsX[mid];

    vector<Point2D> pointsYLeft, pointsYRight;
    for (const auto& point : pointsY) {
        if (point.x <= midPoint.x) {
            pointsYLeft.push_back(point);
        } else {
            pointsYRight.push_back(point);
        }
    }

    vector<Point2D> pointsXLeft(pointsX.begin(), pointsX.begin() + mid);
    vector<Point2D> pointsXRight(pointsX.begin() + mid, pointsX.end());

    auto leftPair = closestPairRec(pointsXLeft, pointsYLeft);
    auto rightPair = closestPairRec(pointsXRight, pointsYRight);

    double leftDist = distance(leftPair.first, leftPair.second);
    double rightDist = distance(rightPair.first, rightPair.second);
    double minDist = min(leftDist, rightDist);
    pair<Point2D, Point2D> minPair = (leftDist < rightDist) ? leftPair : rightPair;

    vector<Point2D> strip;
    for (const auto& point : pointsY) {
        if (abs(point.x - midPoint.x) < minDist) {
            strip.push_back(point);
        }
    }

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            double d = distance(strip[i], strip[j]);
            if (d < minDist) {
                minDist = d;
                minPair = {strip[i], strip[j]};
            }
        }
    }

    return minPair;
}

pair<Point2D, Point2D> closestPair(vector<Point2D>& points) {
    vector<Point2D> pointsX = points;
    vector<Point2D> pointsY = points;

    sort(pointsX.begin(), pointsX.end(), [](const Point2D& a, const Point2D& b) { return a.x < b.x; });
    sort(pointsY.begin(), pointsY.end(), [](const Point2D& a, const Point2D& b) { return a.y < b.y; });

    return closestPairRec(pointsX, pointsY);
}

void Problem9() {
    vector<Point2D> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    auto result = closestPair(points);

    cout << "The closest pair of points are: (" << result.first.x << ", " << result.first.y << ") and ("
         << result.second.x << ", " << result.second.y << ")\n";
}

bool performSearch(int attempt) {
    return rand() % 2 == 0;
}

void exponentialBackoffSearch(int maxRetries) {
    int attempt = 0;
    int baseDelay = 1;

    while (attempt < maxRetries) {
        if (performSearch(attempt)) {
            cout << "Search successful on attempt " << attempt + 1 << "\n";
            return;
        } else {
            cout << "Search failed on attempt " << attempt + 1 << ". Retrying...\n";
            int delay = baseDelay * (1 << attempt);
            this_thread::sleep_for(chrono::seconds(delay));
            attempt++;
        }
    }

    cout << "Search failed after " << maxRetries << " attempts.\n";
}

void Problem10() {
    srand(time(0));
    int maxRetries = 5;
    exponentialBackoffSearch(maxRetries);
}

class product
{
    private:
        string name;
        string brand;
        string category;
        int price;
        string decription;
    public:
        product() : name(""), category(""), price(0), decription(""){}
        product(string newName, string newBrand, string newCategory, int newwPrice, string newDecription) : name(newName), brand(newBrand), category(newCategory), price(newwPrice), decription(newDecription) {}
        string Name()
        {
            return name;
        }
        string Brand()
        {
            return brand;
        }
        string Category()
        {
            return category;
        }
        int Price()
        {
            return price;
        }
        string Decription()
        {
            return decription;
        }

        void Name(string newName)
        {
            name = newName;
        }
        void Brand(string newBrand)
        {
            brand = newBrand;
        }
        void Category(string newCategory)
        {
            category = newCategory;
        }
        int Price(int newPrice)
        {
            price = newPrice;
        }
        string Decription(string newDecription)
        {
            decription = newDecription;
        }
};
class productManager : product
{
    private:
        vector<product> productList;
    public:
        void addProduct(product newProduct)
        {
            productList.push_back(newProduct);
        }

        vector<product> search(string keyword)
        {
            vector<product> result;
            for(int i=0; i<productList.size(); i++)
                if(productList[i].Name().find(keyword)!=-1 || productList[i].Decription().find(keyword)!=-1)
                    result.push_back(productList[i]);
            return result;
        }

        vector<product> filterSearch(int lowPrice, int highPrice)
        {
            vector<product> result;
            for(int i=0; i<productList.size(); i++)
                if(productList[i].Price() >= lowPrice && productList[i].Price() <= highPrice)
                    result.push_back(productList[i]);
            return result;
        }

        vector<product> filterSearch(string keyword)
        {
            vector<product> result;
            for(int i=0; i<productList.size(); i++)
                if(productList[i].Category().find(keyword) || productList[i].Brand().find(keyword)!=-1)
                    result.push_back(productList[i]);
            return result;
        }

        vector<product> facetedSearch(int lowPrice=0, int highPrice=0, string keyword ="")
        {
            bool checked = false;
            vector<product> result;
            for(int i=0; i<productList.size(); i++)
            {
                if((lowPrice!=0 || highPrice!=0))
                {
                    if(keyword!="")
                    {
                        if( (productList[i].Price() >= lowPrice && productList[i].Price() <= highPrice) && (productList[i].Category().find(keyword) || productList[i].Brand().find(keyword)!=-1) )
                            result.push_back(productList[i]);
                    }
                    else
                        if(productList[i].Price() >= lowPrice && productList[i].Price() <= highPrice)
                            result.push_back(productList[i]);

                }
                else
                    if(keyword!="")
                        if(productList[i].Category().find(keyword) || productList[i].Brand().find(keyword)!=-1)
                            result.push_back(productList[i]);
            }
            return result;
        }
};

void Problem11() {
    productManager manager;

    manager.addProduct(product("Laptop", "Apple", "Electronics", 1200, "A high-performance laptop"));
    manager.addProduct(product("Smartphone", "Samsung", "Electronics", 800, "An Android smartphone"));
    manager.addProduct(product("TV", "Sony", "Electronics", 500, "Smart TV with 4K resolution"));
    manager.addProduct(product("Blender", "Philips", "Home Appliance", 100, "Kitchen blender with multiple speeds"));
    manager.addProduct(product("Toaster", "Breville", "Home Appliance", 60, "Two-slice toaster"));

    cout << "Search for 'smart':" << endl;
    vector<product> searchResults = manager.search("smart");
    for (int i = 0; i < searchResults.size(); i++) {
        cout << "Product: " << searchResults[i].Name() << ", Price: $" << searchResults[i].Price() << endl;
    }

    cout << "Filter products in price range $100 - $800:" << endl;
    vector<product> priceFiltered = manager.filterSearch(100, 800);
    for (int i = 0; i < priceFiltered.size(); i++) {
        cout << "Product: " << priceFiltered[i].Name() << ", Price: $" << priceFiltered[i].Price() << endl;
    }

    cout << "Filter products in category 'Electronics':" << endl;
    vector<product> categoryFiltered = manager.filterSearch("Electronics");
    for (int i = 0; i < categoryFiltered.size(); i++) {
        cout << "Product: " << categoryFiltered[i].Name() << ", Price: $" << categoryFiltered[i].Price() << endl;
    }

    cout << "Faceted search for 'Electronics' in price range $500 - $1500:" << endl;
    vector<product> facetedResults = manager.facetedSearch(500, 1500, "Electronics");
    for (int i = 0; i < facetedResults.size(); i++) {
        cout << "Product: " << facetedResults[i].Name() << ", Price: $" << facetedResults[i].Price() << endl;
    }
}

class researchPaper
{
    private:
        string title;
        string abstract;
        string authors;
        string keywords;

    public:
        researchPaper() : title(""), abstract(""), authors(""), keywords("") {};
        researchPaper(string newTitle, string newAbstract, string newAuthor, string newKeywords) : title(newTitle), abstract(newAbstract), authors(newAuthor), keywords(newKeywords) {};
        string Title()
        {
            return title;
        }
        string Abstract()
        {
            return abstract;
        }
        string Authors()
        {
            return authors;
        }
        string Keywords()
        {
            return keywords;
        }

        void Title(string newTitle)
        {
            title = newTitle;
        }
        void Abstract(string newAbstract)
        {
            abstract = newAbstract;
        }
        void Authors(string newAuthors)
        {
            authors = newAuthors;
        }
        void Keywords(string newKeywords)
        {
            keywords = newKeywords;
        }
        string Title() const { return title; }
        string Abstract() const { return abstract; }
        string Authors() const { return authors; }
        string Keywords() const { return keywords; }
};

class paperManager : researchPaper
{
    private:
        vector<researchPaper> paperList;
        string toLowerCase(string str)
        {
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            return str;
        }
        vector<string> splitString(string str, char delimiter)
        {
            vector<string> tokens;
            stringstream ss(str);
            string token;
            while (getline(ss, token, delimiter))
                if (!token.empty())
                    tokens.push_back(toLowerCase(token));
             return tokens;
        }
    public:
        void addPaper(researchPaper newPaper)
        {
            paperList.push_back(newPaper);
        }
        vector<researchPaper> getAllPapers()
        {
            return paperList;
        }
        bool removePaper(string deleteTitle)
        {
            for(int i = 0; i<paperList.size(); i++)
            {
                if(paperList[i].Title() == deleteTitle)
                {
                    paperList.erase(paperList.begin()+i);
                    return true;
                }
            }
            return false;
        }
        vector<researchPaper> searchByKeywords(string queryKeywords)
        {
            vector<researchPaper> results;
            vector<string> searchKeywords = splitString(queryKeywords, ',');

            for(auto paper : paperList) {
                vector<string> paperKeywords = splitString(paper.Keywords(), ',');

                bool found = false;
                for(auto searchKeyword : searchKeywords)
                {
                    for(auto paperKeyword : paperKeywords)
                    {
                        if (toLowerCase(paperKeyword).find(toLowerCase(searchKeyword)) != string::npos)
                        {
                            found = true;
                            break;
                        }
                    }
                    if(found)
                        break;
                }

                if(found)
                    results.push_back(paper);
            }
            return results;
        }
};

void Problem12() {
    paperManager manager;

    manager.addPaper(researchPaper("AI in Healthcare", "Exploring AI applications in healthcare", "John Doe", "AI, healthcare, medicine"));
    manager.addPaper(researchPaper("Quantum Computing", "Basics of quantum computing", "Alice Smith", "quantum, computing, physics"));
    manager.addPaper(researchPaper("Climate Change Impacts", "Impact of climate change on global ecosystems", "Emma Jones", "climate, environment, ecosystems"));
    manager.addPaper(researchPaper("Blockchain Technology", "Decentralization through blockchain", "Bob Brown", "blockchain, decentralization, technology"));

    cout << "All research papers:" << endl;
    vector<researchPaper> allPapers = manager.getAllPapers();
    for (int i = 0; i < allPapers.size(); i++) {
        cout << "Title: " << allPapers[i].Title() << ", Authors: " << allPapers[i].Authors() << endl;
    }

    cout << "\nSearch for papers with keywords 'AI, technology':" << endl;
    vector<researchPaper> keywordResults = manager.searchByKeywords("AI, technology");
    for (int i = 0; i < keywordResults.size(); i++) {
        cout << "Title: " << keywordResults[i].Title() << ", Keywords: " << keywordResults[i].Keywords() << endl;
    }

    cout << "\nRemoving paper titled 'Quantum Computing':" << endl;
    bool removed = manager.removePaper("Quantum Computing");
    if (removed) {
        cout << "Paper removed successfully." << endl;
    } else {
        cout << "Paper not found." << endl;
    }

    cout << "\nRemaining research papers after deletion:" << endl;
    allPapers = manager.getAllPapers();
    for (int i = 0; i < allPapers.size(); i++) {
        cout << "Title: " << allPapers[i].Title() << ", Authors: " << allPapers[i].Authors() << endl;
    }
}

struct Patient {
    int id;
    string name;
    string dob;
    string contact;
    Patient* next;

    Patient(int _id, string _name, string _dob, string _contact) {
        id = _id;
        name = _name;
        dob = _dob;
        contact = _contact;
        next = nullptr;
    }

    void display() {
        cout << "ID: " << id << "\nName: " << name
             << "\nDOB: " << dob << "\nContact: " << contact << "\n\n";
    }
};

class HospitalSystem {
private:
    Patient* head;
    int* indexArray;
    int size;
    int capacity;

    void sortIndexArray() {
        for(int i = 0; i < size - 1; i++) {
            for(int j = 0; j < size - i - 1; j++) {
                if(indexArray[j] > indexArray[j + 1]) {
                    int temp = indexArray[j];
                    indexArray[j] = indexArray[j + 1];
                    indexArray[j + 1] = temp;
                }
            }
        }
    }

public:
    HospitalSystem(int _capacity = 100) {
        head = nullptr;
        capacity = _capacity;
        size = 0;
        indexArray = new int[capacity];
    }

    ~HospitalSystem() {
        Patient* current = head;
        while(current != nullptr) {
            Patient* next = current->next;
            delete current;
            current = next;
        }
        delete[] indexArray;
    }

    void addPatient(int id, string name, string dob, string contact) {
        if(size >= capacity) {
            cout << "Database is full!\n";
            return;
        }

        if(findByIdLinear(id) != nullptr) {
            cout << "Patient with ID " << id << " already exists!\n";
            return;
        }

        Patient* newPatient = new Patient(id, name, dob, contact);

        if(head == nullptr || head->id > id) {
            newPatient->next = head;
            head = newPatient;
        } else {
            Patient* current = head;
            while(current->next != nullptr && current->next->id < id) {
                current = current->next;
            }
            newPatient->next = current->next;
            current->next = newPatient;
        }

        indexArray[size] = id;
        size++;
        sortIndexArray();
    }

    void deletePatient(int id) {
        if(head == nullptr) {
            cout << "Database is empty!\n";
            return;
        }

        Patient* current = head;
        Patient* prev = nullptr;

        while(current != nullptr && current->id != id) {
            prev = current;
            current = current->next;
        }

        if(current == nullptr) {
            cout << "Patient not found!\n";
            return;
        }

        if(prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        for(int i = 0; i < size; i++) {
            if(indexArray[i] == id) {
                for(int j = i; j < size - 1; j++) {
                    indexArray[j] = indexArray[j + 1];
                }
                break;
            }
        }
        size--;

        delete current;
        cout << "\nPatient with ID " << id << " deleted.\n";
    }

    Patient* findByIdLinear(int id) {
        Patient* current = head;
        int comparisons = 0;

        while(current != nullptr) {
            comparisons++;
            if(current->id == id) {
                cout << "Linear search took " << comparisons << " comparisons\n";
                return current;
            }
            current = current->next;
        }

        cout << "Linear search took " << comparisons << " comparisons\n";
        return nullptr;
    }

    Patient* findByIdIndexed(int id) {
        int left = 0;
        int right = size - 1;
        int comparisons = 0;

        while(left <= right) {
            comparisons++;
            int mid = (left + right) / 2;

            if(indexArray[mid] == id) {
                cout << "Index search took " << comparisons << " comparisons\n";
                return findByIdLinear(id);
            }

            if(indexArray[mid] < id)
                left = mid + 1;
            else
                right = mid - 1;
        }

        cout << "Index search took " << comparisons << " comparisons\n";
        return nullptr;
    }

    void displayAllPatients() {
        if(head == nullptr) {
            cout << "No patients in database.\n";
            return;
        }

        cout << "\nPatient Records:\n";
        Patient* current = head;
        while(current != nullptr) {
            current->display();
            current = current->next;
        }
    }

    void compareSearchMethods(int id) {
        cout << "\nComparing search methods for ID " << id << ":\n";
        Patient* p1 = findByIdLinear(id);
        Patient* p2 = findByIdIndexed(id);

        if(p1 == nullptr) {
            cout << "Patient not found!\n";
        }
    }
};

void Problem13() {
    HospitalSystem hospital;

    hospital.addPatient(103, "John Smith", "1990-05-15", "555-0101");
    hospital.addPatient(101, "Emma Wilson", "1985-12-23", "555-0102");
    hospital.addPatient(105, "Michael Brown", "1978-08-30", "555-0103");
    hospital.addPatient(102, "Sarah Davis", "1995-03-17", "555-0104");
    hospital.addPatient(104, "James Johnson", "1982-11-08", "555-0105");

    cout << "Initial Database:";
    hospital.displayAllPatients();

    cout << "\nSearching for patient with ID 103:";
    hospital.compareSearchMethods(103);

    cout << "\nDeleting patient with ID 103";
    hospital.deletePatient(103);

    cout << "\nSearching for deleted patient (ID 103):";
    hospital.compareSearchMethods(103);

    cout << "\nSearching for patient with ID 102:";
    hospital.compareSearchMethods(102);

    cout << "\nFinal Database:";
    hospital.displayAllPatients();
}

class Node {
public:
    string url;
    time_t timestamp;
    int frequency;
    Node *left, *right;

    Node(string u) {
        url = u;
        timestamp = time(0);
        frequency = 1;
        left = right = nullptr;
    }
};

class WebCache {
private:
    Node* root;
    int size;

    Node* insert(Node* node, string url) {
        if(!node) {
            size++;
            return new Node(url);
        }

        if(url < node->url)
            node->left = insert(node->left, url);
        else if(url > node->url)
            node->right = insert(node->right, url);
        else {
            node->frequency++;
            node->timestamp = time(0);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while(node->left)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, string url) {
        if(!node) return nullptr;

        if(url < node->url)
            node->left = remove(node->left, url);
        else if(url > node->url)
            node->right = remove(node->right, url);
        else {
            if(!node->left && !node->right) {
                delete node;
                size--;
                return nullptr;
            }
            else if(!node->left) {
                Node* temp = node->right;
                delete node;
                size--;
                return temp;
            }
            else if(!node->right) {
                Node* temp = node->left;
                delete node;
                size--;
                return temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->url = temp->url;
                node->timestamp = temp->timestamp;
                node->frequency = temp->frequency;
                node->right = remove(node->right, temp->url);
            }
        }
        return node;
    }

    Node* search(Node* node, string url) {
        if(!node || node->url == url)
            return node;

        if(url < node->url)
            return search(node->left, url);
        return search(node->right, url);
    }

    void inorderTraversal(Node* node) {
        if(!node) return;

        inorderTraversal(node->left);
        cout << "URL: " << node->url
             << " | Frequency: " << node->frequency
             << " | Last Access: " << ctime(&node->timestamp);
        inorderTraversal(node->right);
    }

    void clearOldCache(Node* node, time_t threshold) {
        if(!node) return;

        clearOldCache(node->left, threshold);
        clearOldCache(node->right, threshold);

        if(difftime(time(0), node->timestamp) > threshold) {
            remove(root, node->url);
        }
    }

public:
    WebCache() : root(nullptr), size(0) {}

    void insert(string url) {
        root = insert(root, url);
    }

    void remove(string url) {
        root = remove(root, url);
    }

    bool find(string url) {
        Node* result = search(root, url);
        if(result) {
            result->frequency++;
            result->timestamp = time(0);
            return true;
        }
        return false;
    }

    void display() {
        cout << "\nCache Contents (" << size << " entries):\n";
        inorderTraversal(root);
    }

    void clearOldEntries(int seconds) {
        clearOldCache(root, seconds);
    }

    int getSize() {
        return size;
    }
};

void Problem14() {
    WebCache cache;

    cache.insert("www.google.com");
    cache.insert("www.github.com");
    cache.insert("www.stackoverflow.com");

    cache.display();

    cout << "\nSearching for www.google.com...\n";
    if(cache.find("www.google.com")) {
        cout << "Found and updated access time\n";
    }

    cache.display();

    cout << "\nRemoving www.github.com...\n";
    cache.remove("www.github.com");

    cache.display();

    cout << "\nClearing entries older than 60 seconds...\n";
    cache.clearOldEntries(60);

    cache.display();
}

struct CancerDataPoint {
    int id;
    vector<double> features;
    int label;

    CancerDataPoint(int _id, vector<double> f, int l)
        : id(_id), features(f), label(l) {}
};

class BreastCancerKNN {
private:
    vector<CancerDataPoint> dataset;
    int k;
    int num_threads;
    mutex mtx;
    const vector<string> feature_names = {
        "radius", "texture", "perimeter", "area", "smoothness",
        "compactness", "concavity", "concave_points", "symmetry", "fractal_dimension"
    };

    double calculateDistance(const vector<double>& a, const vector<double>& b) {
        double sum = 0.0;
        for (size_t i = 0; i < a.size(); i++) {
            double diff = a[i] - b[i];
            sum += diff * diff;
        }
        return sqrt(sum);
    }

public:
    BreastCancerKNN(int num_neighbors, int threads) : k(num_neighbors), num_threads(threads) {}

    bool loadDataset(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return false;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string value;

            getline(ss, value, ',');
            int id = stoi(value);

            getline(ss, value, ',');
            int label = (value == "M") ? 1 : 0;

            vector<double> features;
            while (getline(ss, value, ',')) {
                features.push_back(stod(value));
            }

            dataset.emplace_back(id, features, label);
        }

        cout << "Dataset loaded: " << dataset.size() << " samples" << endl;
        cout << "Features per sample: " << dataset[0].features.size() << endl;

        int malignant = count_if(dataset.begin(), dataset.end(),
            [](const CancerDataPoint& p) { return p.label == 1; });
        cout << "Class distribution:" << endl;
        cout << "Malignant: " << malignant << " ("
                  << (100.0 * malignant / dataset.size()) << "%)" << endl;
        cout << "Benign: " << (dataset.size() - malignant) << " ("
                  << (100.0 * (dataset.size() - malignant) / dataset.size()) << "%)" << endl;

        return true;
    }

    void performCrossValidation(int folds = 5) {
        vector<double> accuracies;
        vector<double> execution_times;

        random_device rd;
        mt19937 g(rd());
        vector<CancerDataPoint> shuffled_data = dataset;
        shuffle(shuffled_data.begin(), shuffled_data.end(), g);

        size_t fold_size = dataset.size() / folds;

        for (int fold = 0; fold < folds; fold++) {
            cout << "\nFold " << (fold + 1) << "/" << folds << endl;

            vector<CancerDataPoint> test_data(
                shuffled_data.begin() + fold * fold_size,
                shuffled_data.begin() + (fold + 1) * fold_size
            );

            vector<CancerDataPoint> train_data;
            train_data.insert(train_data.end(),
                shuffled_data.begin(),
                shuffled_data.begin() + fold * fold_size);
            train_data.insert(train_data.end(),
                shuffled_data.begin() + (fold + 1) * fold_size,
                shuffled_data.end());

            int correct = 0;
            auto start_time = chrono::high_resolution_clock::now();

            for (const auto& test_point : test_data) {
                int prediction = predict(test_point.features, train_data);
                if (prediction == test_point.label) correct++;
            }

            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(
                end_time - start_time
            ).count();

            double accuracy = 100.0 * correct / test_data.size();
            accuracies.push_back(accuracy);
            execution_times.push_back(duration);

            cout << "Fold accuracy: " << fixed << setprecision(2)
                      << accuracy << "%" << endl;
            cout << "Execution time: " << duration << "ms" << endl;
        }

        double mean_accuracy = accumulate(accuracies.begin(), accuracies.end(), 0.0) / folds;
        double mean_time = accumulate(execution_times.begin(), execution_times.end(), 0.0) / folds;

        cout << "\nCross-validation results (" << folds << " folds):" << endl;
        cout << "Average accuracy: " << fixed << setprecision(2)
                  << mean_accuracy << "%" << endl;
        cout << "Average execution time: " << mean_time << "ms" << endl;
    }

    int predict(const vector<double>& query_point,
                const vector<CancerDataPoint>& training_data = vector<CancerDataPoint>()) {
        const vector<CancerDataPoint>& data_to_use =
            training_data.empty() ? dataset : training_data;

        vector<thread> threads;
        vector<priority_queue<pair<double, int>>> local_results(num_threads);

        size_t chunk_size = data_to_use.size() / num_threads;
        size_t remainder = data_to_use.size() % num_threads;

        size_t start_idx = 0;
        for (int i = 0; i < num_threads; i++) {
            size_t end_idx = start_idx + chunk_size + (i < remainder ? 1 : 0);

            threads.emplace_back([this, &query_point, &data_to_use, start_idx, end_idx, &local_results, i]() {
                for (size_t j = start_idx; j < end_idx; j++) {
                    double dist = calculateDistance(query_point, data_to_use[j].features);
                    local_results[i].push(make_pair(dist, data_to_use[j].label));
                    if (local_results[i].size() > k) {
                        local_results[i].pop();
                    }
                }
            });

            start_idx = end_idx;
        }

        for (auto& thread : threads) {
            thread.join();
        }

        vector<int> votes(2, 0);
        for (auto& local_result : local_results) {
            while (!local_result.empty()) {
                votes[local_result.top().second]++;
                local_result.pop();
            }
        }

        return votes[1] > votes[0] ? 1 : 0;
    }
};

// Import dataset with the correct data path of the .csv file
void Problem15() {
    cout << "Breast Cancer Classification using Multi-threaded KNN\n" << endl;

    vector<int> thread_counts = {1, 2, 4, 8};

    for (int threads : thread_counts) {
        cout << "\nTesting with " << threads << " threads:" << endl;
        BreastCancerKNN knn(5, threads);

        if (!knn.loadDataset("./dataset/KNNAlgorithmDataset.csv")) {
            cerr << "Failed to load dataset" << endl;
            return;
        }

        knn.performCrossValidation(5);
    }
}

struct StockData {
    string symbol;
    int date;
    double open;
    double high;
    double low;
    double close;
    double volume;

    StockData() = default;

    StockData(string sym, int dt, double o, double h, double l, double c, double v) :
        symbol(sym),
        date(dt),
        open(o),
        high(h),
        low(l),
        close(c),
        volume(v) {}
};

class RealTimeSearchEngine {
private:
    unordered_map<string, map<int, StockData>> stockDataBySymbol;
    vector<int> tradingDates;
    int currentDateIndex;

    void updateTradingDates() {
        set<int> uniqueDates;
        for (const auto& [symbol, dateData] : stockDataBySymbol) {
            for (const auto& [date, _] : dateData) {
                uniqueDates.insert(date);
            }
        }
        tradingDates = vector<int>(uniqueDates.begin(), uniqueDates.end());
        sort(tradingDates.begin(), tradingDates.end());
        currentDateIndex = 0;
    }

public:
    RealTimeSearchEngine() : currentDateIndex(0) {}

    bool importFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return false;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string symbol, temp;
            int date;
            double open, high, low, close, volume;

            getline(ss, symbol, ',');
            getline(ss, temp, ',');
            date = stoi(temp);

            getline(ss, temp, ','); open = stod(temp);
            getline(ss, temp, ','); high = stod(temp);
            getline(ss, temp, ','); low = stod(temp);
            getline(ss, temp, ','); close = stod(temp);
            getline(ss, temp, ','); volume = stod(temp);

            stockDataBySymbol[symbol][date] = StockData(symbol, date, open, high, low, close, volume);
        }

        file.close();
        updateTradingDates();
        return true;
    }

    bool advanceToNextDay() {
        if (currentDateIndex < tradingDates.size() - 1) {
            currentDateIndex++;
            return true;
        }
        return false;
    }

    int getCurrentDate() const {
        if (tradingDates.empty()) return 0;
        return tradingDates[currentDateIndex];
    }

    StockData* searchBySymbol(const string& symbol) {
        auto symbolIt = stockDataBySymbol.find(symbol);
        if (symbolIt != stockDataBySymbol.end()) {
            auto dateIt = symbolIt->second.find(getCurrentDate());
            if (dateIt != symbolIt->second.end()) {
                return &dateIt->second;
            }
        }
        return nullptr;
    }

    vector<StockData> getCurrentPrices() {
        vector<StockData> results;
        int currentDate = getCurrentDate();

        for (const auto& [symbol, dateData] : stockDataBySymbol) {
            auto it = dateData.find(currentDate);
            if (it != dateData.end()) {
                results.push_back(it->second);
            }
        }
        return results;
    }

    vector<StockData> searchByPriceRange(double minPrice, double maxPrice) {
        vector<StockData> results;
        int currentDate = getCurrentDate();

        for (const auto& [symbol, dateData] : stockDataBySymbol) {
            auto it = dateData.find(currentDate);
            if (it != dateData.end() &&
                it->second.close >= minPrice &&
                it->second.close <= maxPrice) {
                results.push_back(it->second);
            }
        }
        return results;
    }

    vector<StockData> getTopNStocks(int n) {
        vector<StockData> currentPrices = getCurrentPrices();

        sort(currentPrices.begin(), currentPrices.end(),
            [](const StockData& a, const StockData& b) {
                return a.close > b.close;
            });

        if (n < currentPrices.size()) {
            currentPrices.resize(n);
        }
        return currentPrices;
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Import dataset with the correct data path of the .csv file
void Problem16() {
    RealTimeSearchEngine engine;

    string filename = "./dataset/BID.csv";
    if (engine.importFromCSV(filename)) {
        cout << "Data imported successfully!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    } else {
        cout << "Failed to import data." << endl;
        return;
    }

    do {
        clearScreen();
        int currentDate = engine.getCurrentDate();

        string dateStr = to_string(currentDate);
        string formattedDate = dateStr.substr(0, 4) + "-" +
                               dateStr.substr(4, 2) + "-" +
                               dateStr.substr(6, 2);

        cout << "\n=== Trading Day: " << formattedDate << " ===" << endl;

        cout << "\nCurrent Stock Prices:" << endl;
        cout << setw(10) << "Symbol" << " | "
             << setw(10) << "Open" << " | "
             << setw(10) << "Close" << " | "
             << setw(15) << "Volume" << endl;
        cout << string(50, '-') << endl;

        auto currentPrices = engine.getCurrentPrices();
        for (const auto& stock : currentPrices) {
            cout << setw(10) << stock.symbol << " | "
                 << setw(10) << fixed << setprecision(2) << stock.open << " | "
                 << setw(10) << stock.close << " | "
                 << setw(15) << setprecision(0) << stock.volume << endl;
        }

        cout << "\nTop 3 Stocks by Price:" << endl;
        cout << string(30, '-') << endl;
        auto topStocks = engine.getTopNStocks(3);
        for (const auto& stock : topStocks) {
            cout << setw(10) << stock.symbol << ": "
                 << fixed << setprecision(2) << stock.close << endl;
        }

        cout << "\nStocks between 10000 and 50000:" << endl;
        cout << string(30, '-') << endl;
        auto rangeResults = engine.searchByPriceRange(10000, 50000);
        for (const auto& stock : rangeResults) {
            cout << setw(10) << stock.symbol << ": "
                 << fixed << setprecision(2) << stock.close << endl;
        }

        this_thread::sleep_for(chrono::seconds(5));

    } while (engine.advanceToNextDay());

    cout << "\nReached the end of simulation data." << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

void computeLPSArray(string& pattern, int lps[]) {
    int m = pattern.size();
    int length = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPsearch(string& text, string& pattern) {
    int n = text.size();
    int m = pattern.size();
    int lps[MAX_PATTERN_SIZE];
    computeLPSArray(pattern, lps);
    int i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
}

const int PRIME = 101;

vector<int> RabinKarpSearch(string& text, string& pattern) {
    int n = text.size();
    int m = pattern.size();
    int base = 256;
    int patternHash = 0;
    int textHash = 0;
    int h = 1;
    vector<int> result;

    for (int i = 0; i < m - 1; i++) {
        h = (h * base) % PRIME;
    }
    for (int i = 0; i < m; i++) {
        patternHash = (base * patternHash + pattern[i]) % PRIME;
        textHash = (base * textHash + text[i]) % PRIME;
    }
    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match == true) {
                result.push_back(i);
            }
        }
        if (i < n - m) {
            textHash = (base * (textHash - text[i] * h) + text[i + m]) % PRIME;
            if (textHash < 0) {
                textHash += PRIME;
            }
        }
    }
    return result;
}

void Problem17a() {
    cout << "Enter the large string: ";
    string text;
    cin >> text;
    cout << "Enter the pattern: ";
    string pattern;
    cin >> pattern;
    KMPsearch(text, pattern);
}
void Problem17b(){
     cout << "Enter the large string: ";
    string text;
    cin >> text;
    cout << "Enter the pattern: ";
    string pattern;
    cin >> pattern;
    vector<int> matches = RabinKarpSearch(text, pattern);
    for (int index : matches) {
        cout << "Pattern found at index " << index << endl;
    }
}

int main()
{
    cout << "Select a problem to run (Classwork: 1-10, Homework: 11-18): ";
    int option;
    cin >> option;

    switch (option)
    {
    case 1:
        Problem1();
        break;
    case 2:
        Problem2();
        break;
    case 3:
        Problem3();
        break;
    case 4:
        Problem4();
        break;
    case 5:
        Problem5();
        break;
    case 6:
        Problem6();
        break;
    case 7:
        Problem7();
        break;
    case 8:
        Problem8();
        break;
    case 9:
        Problem9();
        break;
    case 10:
        Problem10();
        break;
    case 11:
        Problem11();
        break;
    case 12:
        Problem12();
        break;
    case 13:
        Problem13();
        break;
    case 14:
        Problem14();
        break;
    case 15:
        Problem15();
        break;
    case 16:
        Problem16();
        break;
    case 17:
        Problem17a();
        break;
    case 18:
        Problem17b();
        break;
    default:
        break;
    }
    return 0;
}
