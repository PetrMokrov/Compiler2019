//
// Created by l1onsun on 23.12.19.
//

#pragma once

#include <unordered_map>
#include <string>
#include <IRTree/IRTreeWrappers.h>


namespace SyntaxTreeVisitor {

    class IRTreeGoal {
    public:
        std::unordered_map<std::string,
            std::unordered_map<std::string,
                std::unique_ptr<IStatementNode> > > wrappers;

        void add_class(std::string class_name) {
            wrappers.emplace(std::make_pair(class_name,
                    std::unordered_map<std::string, std::unique_ptr<IStatementNode> >()));
        }

        void add_method(std::string class_name,
                std::string method_name,
                std::unique_ptr<IStatementNode>&& wrapper ) {
           wrappers[class_name].emplace(method_name, std::move(wrapper));
        }
    };


}
