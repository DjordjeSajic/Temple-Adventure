//
// Created by djordjes on 8/4/26.
//

#ifndef MATF_RG_PROJECT_APPLICATIONCONTROLLER_HPP
#define MATF_RG_PROJECT_APPLICATIONCONTROLLER_HPP
#include <engine/core/Engine.hpp>

namespace app {
    class ApplicationController : public engine::core::Controller {
    public:
        std::string_view name() const override {
            return "app::ApplicationController";
        }

    private:
        void initialize() override;
    };
} // app

#endif //MATF_RG_PROJECT_APPLICATIONCONTROLLER_HPP
