//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionConstNode : public IExpressionNode {
    public:
        explicit ExpressionConstNode(int value) : value(value) {}

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        const int value{};
    };
}
