//
// Created by l1onsun on 15.12.19.
//
#include <IVisitor.h>
#include <SymbolTree.h>
#include <Tree.h>
#include "IRTreeNode.h"

namespace IRTree {
    class IRTreeTranslator: public SyntaxTree::IVisitor  {
    public:
        IRTreeTranslator(SyntaxTree::Tree& tree, SymbolTree::SymbolTree symbol_tree);
        void visit(const SyntaxTree::TypeIntNode& node) override;
        void visit(const SyntaxTree::TypeBooleanNode& node) override;
        void visit(const SyntaxTree::TypeArrayNode& node) override;
        void visit(const SyntaxTree::TypeUserNode& node) override;
        void visit(const SyntaxTree::TypeVoidNode& node) override;
        void visit(const SyntaxTree::TypeStringNode& node) override;
        void visit(const SyntaxTree::IdentifierNode& node) override;
        void visit(const SyntaxTree::ExpressionIdentifierNode& node) override;
        void visit(const SyntaxTree::ExpressionBinaryOperationNode& node) override;
        void visit(const SyntaxTree::ExpressionIndexNode& node) override;
        void visit(const SyntaxTree::ExpressionGetLengthNode& node) override;
        void visit(const SyntaxTree::ExpressionMethodCallNode& node) override;
        void visit(const SyntaxTree::ExpressionStaticMethodCallNode& node) override;
        void visit(const SyntaxTree::ExpressionIntegerLiteralNode& node) override;
        void visit(const SyntaxTree::ExpressionBooleanLiteralNode& node) override;
        void visit(const SyntaxTree::ExpressionThisNode& node) override;
        void visit(const SyntaxTree::ExpressionNewArrayNode& node) override;
        void visit(const SyntaxTree::ExpressionNewNode& node) override;
        void visit(const SyntaxTree::ExpressionNotOperatorNode& node) override;
        void visit(const SyntaxTree::ExpressionRoundBracketsNode& node) override;
        void visit(const SyntaxTree::StatementIfNode& node) override;
        void visit(const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode>& node) override; //StatementList
        void visit(const SyntaxTree::StatementEmptyNode& node) override;
        void visit(const SyntaxTree::StatementWhileNode& node) override;
        void visit(const SyntaxTree::StatementPrintlnNode& node) override;
        void visit(const SyntaxTree::StatementAssignNode& node) override;
        void visit(const SyntaxTree::StatementAssignArrayNode& node) override;
        void visit(const SyntaxTree::StatementReturnNode& node) override;
        void visit(const SyntaxTree::DeclarationMethodNode& node) override;
        void visit(const SyntaxTree::DeclarationClassNode& node) override;
        void visit(const SyntaxTree::DeclarationVarNode& node) override;
        void visit(const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase>& node) override; //GoalNode


        //supporting methods
        SymbolTree::ClassInfo* getClassFromName(std::string& name) {
            auto search = symbol_tree_.classes_info.find(name);
            if (search != symbol_tree_.classes_info.end()) {
                return &search->second;
            } else {
                return nullptr; //Is it okay behavior?
            }
        }

        void findMain() {
            bool mainFound = false;
            for (const auto& class_info : symbol_tree_.classes_info) {
                for (const auto& method : class_info.second.method_info)
                    if (method.first == "void main(String[], )") {
                        if (mainFound)
                            throw std::runtime_error("two main methods found");
                        mainFound = true;
                        mainClass = &class_info.second;
                    }
            }
            if (!mainFound)
                throw std::runtime_error("no main method found");
        }

    protected:
        SymbolTree::SymbolTree symbol_tree_;
        IRTreeGoal* goal = nullptr;
        const SymbolTree::ClassInfo *mainClass;
    };
}