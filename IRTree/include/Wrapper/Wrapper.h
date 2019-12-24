//
// Created by Zinenko Dmytro on 23.12.2019.
//
#pragma once

#include <memory>
#include "IWrapper.h"
#include "cassert"

namespace IRTree {

    template<class NodeType>
    class Wrapper : public IWrapper {
    public:
        explicit Wrapper(std::unique_ptr<NodeType> node) : node_(std::move(node)) {
        }

//        template<typename T = std::enable_if_t<std::is_base_of_v<IExpressionNode,NodeType>>>
//        inline std::unique_ptr<IExpressionNode> to_expression_check() {
//            return std::move(node_);
//        }
        template<typename T>
        std::unique_ptr<IExpressionNode> to_expression_check();

        static constexpr bool is_expression = std::is_base_of_v<IExpressionNode,NodeType>;

        std::unique_ptr<IExpressionNode> to_expression() override {
            //return to_expression_check<int>();
            if (is_expression) {
                return std::unique_ptr<IExpressionNode>(dynamic_cast<IExpressionNode*>(node_.release()));
            } else {
                assert(false);
                return nullptr;
            }
        }

        static constexpr bool is_statement = std::is_base_of_v<IStatementNode,NodeType>;

        std::unique_ptr<IStatementNode> to_statement() override {
            if (is_statement) {
                auto bla = std::unique_ptr<IStatementNode>(dynamic_cast<IStatementNode*>(node_.release()));
                return bla;
            } else {
                assert(false);
                return nullptr;
            }
        }

        std::unique_ptr<IStatementNode> to_conditional(std::unique_ptr<LabelNode> & /*true_label*/,
                                                       std::unique_ptr<LabelNode> & /*false_label*/) override {
            assert(false);
        }

    private:
        std::unique_ptr<NodeType> node_;
    };
}
