//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionBinaryOperationNode : public IExpressionNode {
    public:
        enum BinaryOperationType {
            ADD,
            SUB,
            MUL,
            DIV,
            MOD,
            OR,
            AND,
            EQUIVALENT,
            NOT_EQUIVALENT,
            LESS,
            LESS_OR_EQUIVALENT,
            MORE,
            MORE_OR_EQUIVALENT
        };

        void accept(IVisitor& visitor) const override {
            visitor.visit(*this);
        }

        BinaryOperationType operation_type;
        std::unique_ptr<IExpressionNode> left;
        std::unique_ptr<IExpressionNode> right;
    };
}
