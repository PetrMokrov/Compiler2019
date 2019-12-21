//
// Created by l1onsun on 21.12.19.
//
#pragma once

#include "IRTreeVisitor.h"
#include <memory>
#include <utility>
#include <vector>

namespace IRTree {
    class IRTreeNode {
    public:
        virtual ~IRTreeNode() = default;
        virtual void AcceptVisitor(IRTreeVisitor* visitor) const = 0;
    };

    class IRTreeExpression : public IRTreeNode {
    };

    class IRTreeStatement : public IRTreeNode {
    };

    class IRTreeGoal : public IRTreeStatement {
    public:
        IRTreeGoal(std::shared_ptr<const IRTreeStatement>  _mainMethod) : mainMethod(std::move(_mainMethod)) {}

        void AcceptVisitor(IRTreeVisitor* visitor) const override { visitor->VisitNode(this); }

        void AddMethod(const std::shared_ptr<const IRTreeStatement>& method) { methods.push_back(method); }
        [[nodiscard]] std::shared_ptr<const IRTreeStatement> GetMainMethod() const { return mainMethod; }
        [[nodiscard]] const std::vector<std::shared_ptr<const IRTreeStatement>>& GetMethods() const { return methods; }

    private:
        std::shared_ptr<const IRTreeStatement> mainMethod;
        std::vector<std::shared_ptr<const IRTreeStatement>> methods;
    };

};