//
// Created by djordjes on 9/3/26.
//

#include "../include/GuiController.hpp"

#include <imgui.h>
#include <SceneController.hpp>
#include <engine/graphics/GraphicsController.hpp>

namespace app {
    void GuiController::initialize() {
        set_enable(false);
    }

    void GuiController::poll_events() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if (platform->key(engine::platform::KeyId::KEY_TAB).state() == engine::platform::Key::State::JustPressed) {
            auto scene_controller = engine::core::Controller::get<app::SceneController>();

            float current_time                   = platform->frame_time().current;
            float elapsed                        = current_time - scene_controller->get_torch_swing_time_start();
            constexpr float total_swing_duration = 1.5f;
            if (elapsed > total_swing_duration) {
                set_enable(true);
                platform->set_enable_cursor(true);
            }
        }
    }

    void GuiController::draw() {
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        graphics->begin_gui();

        ImGui::Begin("Temple adventure - menu");

        float button_width = 150.0f;
        float window_width = ImGui::GetWindowWidth();
        float centered_x   = (window_width - button_width) * 0.5f;

        ImGui::SetCursorPosX(centered_x);
        if (ImGui::Button("Continue", ImVec2(button_width, 30))) {
            set_enable(!is_enabled());
            platform->set_enable_cursor(false);
        }

        ImGui::Spacing();
        ImGui::SetCursorPosX(centered_x);
        if (ImGui::Button("Change time of day", ImVec2(button_width, 30))) {
            std::string next_skybox = (app::SceneController::get_current_skybox() == "day_skybox")
                                          ? "night_skybox"
                                          : "day_skybox";
            app::SceneController::set_current_skybox(next_skybox);
        }

        ImGui::Spacing();
        ImGui::SetCursorPosX(centered_x);
        if (ImGui::Button("Exit Game", ImVec2(button_width, 30))) {
            set_gui_exit_game_flag();
        }

        ImGui::End();

        graphics->end_gui();
    }

    void GuiController::set_gui_exit_game_flag() {
        m_gui_exit_game = true;
    }

    bool GuiController::loop() {
        if (m_gui_exit_game) {
            return false;
        }
        return true;
    }
} // app
