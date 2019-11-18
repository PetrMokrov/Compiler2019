//
// Created by Zinenko Dmytro on 20.10.2019.
//
#include "gtest/gtest.h"
#include <include/Builder.h>
#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <unordered_set>

const std::array<std::string, 8> Paths = {
    "BinarySearch.java",
    "BinaryTree.java",
    "BubbleSort.java",
    "Factorial.java",
    "LinearSearch.java",
    "LinkedList.java",
    "QuickSort.java",
    "TreeVisitor.java"
};

const std::string PathPrefix("../../tests/Samples/");

TEST(LexicalAnalyz, FindUnknownToken) {
    BisonBuilder::Builder builder;
    for (const auto &path : Paths) {
        std::ifstream sample(PathPrefix + path);
        ASSERT_TRUE(sample.is_open());
        auto analyzer = builder.parse(sample);
        ASSERT_EQ(analyzer, 0);
        std::cout << "Ok: " << PathPrefix + path << "   result: "<< analyzer << std::endl;
        sample.close();
    }
}

//TEST(LexicalAnalyz, FindUnknownIterator) {
//    BisonBuilder::Builder builder;
//    std::ifstream sample(PathPrefix + "EmptyClass.java");
//    ASSERT_TRUE(sample.is_open());
//    auto analyzer = builder.parse(sample);
//    ASSERT_EQ(analyzer, 0);
//    std::cout << "Ok: " << PathPrefix + "BinarySearch.java" << "   result: "<< analyzer << std::endl;
//    sample.close();
//}
