//
// Created by djordjes on 9/3/26.
//

#ifndef MATF_RG_PROJECT_GUICONTROLLER_HPP
#define MATF_RG_PROJECT_GUICONTROLLER_HPP
#include <engine/core/Engine.hpp>

namespace app {
    class GuiController : public engine::core::Controller {


    public:
        std::string_view name() const override {
            return "app::GuiController";
        }

    private:
        void initialize() override;
        void poll_events() override;
        void draw() override;
    };
} // app

#endif //MATF_RG_PROJECT_GUICONTROLLER_HPP
