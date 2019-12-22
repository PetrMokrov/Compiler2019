//
// Created by l1onsun on 17.12.19.
//


#include "gtest/gtest.h"
#include <Builder.h>
#include <SymbolTableBuilder.h>
#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <IRTreeTranslator.h>

const std::array<std::string, 9> Paths = {
//        "BinarySearch.java",
//        "BinaryTree.java",
//        "BubbleSort.java",
        "Factorial.java",
//        "LinearSearch.java",
//        "LinkedList.java",
//        "QuickSort.java",
//        "TreeVisitor.java",
//        "Test"
};


const std::string PathPrefix("../../tests/Samples/");
const std::string ResultPrefix("../../tests/Samples/Digraph/SymbolTable/");
//const std::string PathPrefix("Samples/");
//const std::string ResultPrefix("Samples/Digraph/SyntaxTree/");

TEST(IRTree, Test) {
    BisonBuilder::Builder builder;
    for (const auto &path : Paths) {
        std::ifstream sample(PathPrefix + path);
        ASSERT_TRUE(sample.is_open());
        auto analyzer = builder.parse(sample);
        ASSERT_EQ(analyzer, 0);
        std::cout << "Ok: " << PathPrefix + path << "   result: " << analyzer << std::endl;
        sample.close();
        SyntaxTree::Tree tree(std::move(builder.root));
        SymbolTree::SymbolTree symbol_tree;
        ASSERT_NO_THROW(symbol_tree = SymbolTree::SymbolTableBuilder::build(tree));

        IRTree::IRTreeTranslator(tree, symbol_tree);
    }
}