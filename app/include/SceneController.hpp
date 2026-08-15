//
// Created by djordjes on 8/4/26.
//

#ifndef MATF_RG_PROJECT_SCENECONTROLLER_HPP
#define MATF_RG_PROJECT_SCENECONTROLLER_HPP
#include <engine/core/Engine.hpp>

namespace app {
    class SceneController : public engine::core::Controller {
    public:
        std::string_view name() const override {
            return "app::SceneController";
        }

    private:
        void initialize() override;

        void begin_draw() override;

        void draw_torch();

        void draw_temple();

        void draw() override;

        void end_draw() override;
    };
} // app

#endif //MATF_RG_PROJECT_SCENECONTROLLER_HPP
