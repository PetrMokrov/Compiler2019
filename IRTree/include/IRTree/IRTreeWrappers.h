//
// Created by l1onsun on 23.12.19.
//
#pragma once

#include <memory>
#include <cassert>
#include <ExpressionNode/IExpressionNode.h>
#include <StatementNode/IStatementNode.h>
#include <LabelNode/LabelNode.h>
#include <StatementNode/StatementExpressionNode.h>

namespace IRTree {

    class IWrapper {
    public:
        virtual ~IWrapper() {};

        virtual std::unique_ptr<const IExpressionNode> to_expression() { assert(false); };
        virtual std::unique_ptr<const IStatementNode> to_statement() { assert(false); };
        virtual std::unique_ptr<const IStatementNode> to_conditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                                            const std::unique_ptr<const LabelNode>& negativeLabel) { assert(false); };
    };

    class ExpressionWrapper : public IWrapper {
    public:
        explicit ExpressionWrapper(std::unique_ptr<IExpressionNode>&& expression): expression_(std::move(expression)) {}

        std::unique_ptr<const IExpressionNode> to_expression() override { return std::move(expression_); }
        std::unique_ptr<const IStatementNode> to_statement() override;
        std::unique_ptr<const IStatementNode> to_conditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                                    const std::unique_ptr<const LabelNode>& negativeLabel) override;

    private:
        std::unique_ptr<const IExpressionNode> expression_;
    };

    class StatementWrapper : public IWrapper {
    public:
        explicit StatementWrapper(std::unique_ptr<const IStatementNode>&& statement): statement_(std::move(statement)) {}

        std::unique_ptr<const IStatementNode> to_statement() override { return std::move(statement_); }

    private:
        std::unique_ptr<const IStatementNode> statement_;
    };

    class ConditionalWrapper : public IWrapper {
    public:
        virtual ~ConditionalWrapper() {};

        std::unique_ptr<const IExpressionNode> to_expression() override;
        virtual std::unique_ptr<const IStatementNode> to_conditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                                            const std::unique_ptr<const LabelNode>& negativeLabel) override = 0;
    };

    // пока поддерживаем только "меньше <"
    class RelativeConditionalWrapper : public ConditionalWrapper {
    public:
        RelativeConditionalWrapper(const std::unique_ptr<const IExpressionNode>& _leftOperand,
                                   const std::unique_ptr<const IExpressionNode>& _rightOperand);

        std::unique_ptr<const IStatementNode> to_conditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                                    const std::unique_ptr<const LabelNode>& negativeLabel) override;

    private:
        const std::unique_ptr<const IExpressionNode>& leftOperand;
        const std::unique_ptr<const IExpressionNode>& rightOperand;
    };

    class AndConditionalWrapper : public ConditionalWrapper {
    public:
        AndConditionalWrapper(std::unique_ptr<const IWrapper>&& leftOperand,
                              std::unique_ptr<const IWrapper>&& rightOperand);

        std::unique_ptr<const IStatementNode> to_conditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                                    const std::unique_ptr<const LabelNode>& negativeLabel) override;

    private:
        std::unique_ptr<const IWrapper> leftOperand_;
        std::unique_ptr<const IWrapper> rightOperand_;
    };

    class OrConditionalWrapper : public ConditionalWrapper {
    public:
        OrConditionalWrapper(std::unique_ptr<const IWrapper>&& leftOperand,
                             std::unique_ptr<const IWrapper>&& rightOperand);

        std::unique_ptr<const IStatementNode> to_conditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                                    const std::unique_ptr<const LabelNode>& negativeLabel) override;

    private:
        std::unique_ptr<const IWrapper> leftOperand_;
        std::unique_ptr<const IWrapper> rightOperand_;
    };

    class OppositeConditionalWrapper : public ConditionalWrapper {
    public:
        explicit OppositeConditionalWrapper(std::unique_ptr<const IWrapper>&& wrapper) : internalWrapper_(std::move(wrapper)) {}

        std::unique_ptr<const IStatementNode> to_conditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                                    const std::unique_ptr<const LabelNode>& negativeLabel) override;

    private:
        std::unique_ptr<const IWrapper> internalWrapper_;
    };

    //from Make.h
    template <typename T, class... Args>
    inline const std::unique_ptr<const T> makeNode(Args&&... args) {
        return std::make_unique<const T>(std::forward<Args>(args)...);
    }

    template <typename T, class... Args>
    inline const std::unique_ptr<const T> makeWrapper(Args&&... args) {
        return std::make_unique<const T>(std::forward<Args>(args)...);
    }
}
