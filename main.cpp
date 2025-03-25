#include <iostream>
#include "SimpleSegmentTree.h"
#include "MultiflowSegmentTree.h"

int main() {
    MultiflowSegmentTree<int> mst(std::vector<int>{1, 2, 3, 4, 5});
    std::cout << mst.GetSegment(2, 4) << "\n";
    return 0;
}