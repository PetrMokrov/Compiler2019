//
// Created by l1onsun on 15.12.19.
//
#include <IVisitor.h>
#include <SymbolTree.h>
#include <Tree.h>
#include <IRTree/INodeBase.h>
#include <Wrapper/IWrapper.h>
#include <IRTree/IRTreeGoal.h>

namespace SyntaxTreeVisitor {
    class IRTreeTranslator : public SyntaxTree::IVisitor {
    public:

        explicit IRTreeTranslator(const SymbolTree::SymbolTree &symbol_tree) : symbol_tree_(symbol_tree) {
        };

        void visit(const SyntaxTree::TypeIntNode &node) override;

        void visit(const SyntaxTree::TypeBooleanNode &node) override;

        void visit(const SyntaxTree::TypeArrayNode &node) override;

        void visit(const SyntaxTree::TypeUserNode &node) override;

        void visit(const SyntaxTree::TypeVoidNode &node) override;

        void visit(const SyntaxTree::TypeStringNode &node) override;

        void visit(const SyntaxTree::IdentifierNode &node) override;

        void visit(const SyntaxTree::ExpressionIdentifierNode &node) override;

        void visit(const SyntaxTree::ExpressionBinaryOperationNode &node) override;

        void visit(const SyntaxTree::ExpressionIndexNode &node) override;

        void visit(const SyntaxTree::ExpressionGetLengthNode &node) override;

        void visit(const SyntaxTree::ExpressionMethodCallNode &node) override;

        void visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) override;

        void visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) override;

        void visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) override;

        void visit(const SyntaxTree::ExpressionThisNode &node) override;

        void visit(const SyntaxTree::ExpressionNewArrayNode &node) override;

        void visit(const SyntaxTree::ExpressionNewNode &node) override;

        void visit(const SyntaxTree::ExpressionNotOperatorNode &node) override;

        void visit(const SyntaxTree::ExpressionRoundBracketsNode &node) override;

        void visit(const SyntaxTree::StatementIfNode &node) override;

        void
        visit(const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) override; //StatementList
        void visit(const SyntaxTree::StatementEmptyNode &node) override;

        void visit(const SyntaxTree::StatementWhileNode &node) override;

        void visit(const SyntaxTree::StatementPrintlnNode &node) override;

        void visit(const SyntaxTree::StatementAssignNode &node) override;

        void visit(const SyntaxTree::StatementAssignArrayNode &node) override;

        void visit(const SyntaxTree::StatementReturnNode &node) override;

        void visit(const SyntaxTree::DeclarationMethodNode &node) override;

        void visit(const SyntaxTree::DeclarationClassNode &node) override;

        void visit(const SyntaxTree::DeclarationVarNode &node) override;

        void
        visit(const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) override; //GoalNode

        std::unique_ptr<IRTree::IRTreeGoal> goal{nullptr};
    private:
        void buildStatement(const std::unique_ptr<SyntaxTree::IStatementNode> &statement,
                            std::unique_ptr<IRTree::IWrapper>& result_wrapper);

        const SymbolTree::SymbolTree &symbol_tree_;
        const SymbolTree::MethodInfo *current_method_{};
        const SymbolTree::ClassInfo *current_class_{};
        std::unique_ptr<IRTree::IWrapper> last_wrapper_{};

        IRTree::TempNode return_expression = IRTree::TempNode("return@return");
    };
}
