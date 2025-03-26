#pragma once

#include <iostream>
#include <string>

#include "Test.h"
#include "TestGenerator.h"
#include "Timer.h"

#include "../SegmentTrees/SimpleSegmentTree.h"
#include "../SegmentTrees/MultiflowSegmentTree.h"

void WhoIsFaster() {
    std::cout << std::endl << "===============WHO IS FASTER ?===============" << std::endl << std::endl;
    for (size_t test_id = 1; test_id <= 15; test_id++) {
        std::cout << "Testing on test " << test_id << std::endl;

        Test<int> test = GenerateTest<int>(200000, 200000);

        std::vector<int> SimpleSegmentTree_answer;
        std::vector<int> MultiflowSegmentTree_answer;
        std::vector<int> StupidSegmentTree_answer;

        std::cout << "  Start execution test " << test_id << " on SimpleSegmentTree" << std::endl;

        Timer timer;

        SegmentTree<int> st(test.GetArray());

        for (const auto& query : test.GetQuery()) {
            if (!query.type_) {
                st.Update(query.position_, query.value_);
            } else {
                SimpleSegmentTree_answer.push_back(st.GetSegment(
                        query.left_border_, query.right_border_));
            }
        }

        std::cout << "  End execution test " << test_id << " on SimpleSegmentTree" << std::endl;
        std::cout << "  Execution time: " << timer.GetTime() << std::endl << std::endl;


        std::cout << "  Start execution test " << test_id << " on MultiflowSegmentTree" << std::endl;

        timer.SetStart();

        MultiflowSegmentTree<int> mst(test.GetArray());

        for (const auto& query : test.GetQuery()) {
            if (!query.type_) {
                mst.Update(query.position_, query.value_);
            } else {
                MultiflowSegmentTree_answer.push_back(mst.GetSegment(
                        query.left_border_, query.right_border_));
            }
        }

        std::cout << "  End execution test " << test_id << " on MultiflowSegmentTree" << std::endl;
        std::cout << "  Execution time: " << timer.GetTime() << std::endl << std::endl;

        std::cout << std::endl;
    }
}