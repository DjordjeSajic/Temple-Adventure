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

        glm::vec3 get_ambient_color() const {
            return m_ambient_color;
        }

        glm::vec3 get_light_dir() const {
            return m_light_dir;
        }

        glm::vec3 get_light_color() const {
            return m_light_color;
        }

        void set_lighting_parameters(const glm::vec3 &ambient_color, const glm::vec3 &light_color) {
            m_ambient_color = ambient_color;
            m_light_color   = light_color;
        }

        bool get_torch_lit_status() const {
            return m_torch_lit;
        }

        void toggle_torch_lit() {
            m_torch_lit = !m_torch_lit;
        }

        void set_torch_swing_time_start(float time_start) {
            m_torch_swing_time_start = time_start;
        }

        float get_torch_swing_time_start() const {
            return m_torch_swing_time_start;
        }

        float get_light_reach() const {
            return m_light_reach;
        }

        void increase_light_reach(float light_reach_inc_factor) {
            m_light_reach += light_reach_inc_factor;
        }

        void decrease_light_reach(float light_reach_dec_factor) {
            m_light_reach = ((m_light_reach - light_reach_dec_factor < 0.1f))
                                ? 0.1f
                                : (m_light_reach - light_reach_dec_factor);
        }

    private:
        void initialize() override;

        void torch_action();

        void update() override;

        void begin_draw() override;

        void draw_torch();

        void draw_temple();

        void draw_jungle();

        void draw_skybox();

        void setup_lighting();

        void draw() override;

        void end_draw() override;

        inline static std::string s_current_skybox = "day_skybox";
        //light_color and ambient_color can be just 0, but I added default day values because the skybox is day by default
        glm::vec3 m_ambient_color                  = glm::vec3(0.3f, 0.35f, 0.4f);
        glm::vec3 m_light_color                    = glm::vec3(1.0f, 0.95f, 0.8f);
        glm::vec3 m_light_dir                      = glm::vec3(60.0f, 40.0f, 13.0f);

        bool m_torch_lit               = false;
        //m_toch_swing_time_start can be any negative number I just wanted to put the answer to the universe for reference in my project
        float m_torch_swing_time_start = -42.0f;
        float m_light_reach            = 1.0f;
    };
} // namespace app

#endif//MATF_RG_PROJECT_SCENECONTROLLER_HPP
