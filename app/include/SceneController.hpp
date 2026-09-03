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

        static void set_current_skybox(const std::string &skybox_name) {
            s_current_skybox = skybox_name;
        }

        static std::string get_current_skybox() {
            return s_current_skybox;
        }

    private:
        void initialize() override;

        void begin_draw() override;

        void draw_torch();

        void draw_temple();

        void draw_jungle();

        void draw_skybox();

        void draw() override;

        void end_draw() override;

        inline static std::string s_current_skybox = "day_skybox";
    };
} // app

#endif //MATF_RG_PROJECT_SCENECONTROLLER_HPP
