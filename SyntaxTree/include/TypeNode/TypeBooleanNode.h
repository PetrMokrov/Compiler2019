//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "ITypeNode.h"

namespace SyntaxTree {
    class TypeBooleanNode : public ITypeNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::TYPE_BOOLEAN;
        }
    };
}
