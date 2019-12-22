//
// Created by Zinenko Dmytro on 22.12.2019.
//

#include <TempNode/TempNode.h>
#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionTempNode : public IExpressionNode {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<TempNode> temp;
    };
}