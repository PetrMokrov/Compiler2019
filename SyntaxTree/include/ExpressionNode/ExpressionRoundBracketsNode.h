//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionNotOperatorNode : public virtual IExpressionNode {
    public:
        explicit ExpressionNotOperatorNode(IExpressionNode *expression)
                : expression_(expression) {
        }

        NodeType get_type() const override {
            return NodeType::EXPRESSION_ROUND_BRACKETS;
        }

        const IExpressionNode *get_expression() const {
            return expression_.get();
        }

        ~ExpressionNotOperatorNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> expression_;
    };
}