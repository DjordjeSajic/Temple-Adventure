//
// Created by djordjes on 9/3/26.
//

#include "../include/GuiController.hpp"

#include <imgui.h>
#include <engine/graphics/GraphicsController.hpp>

namespace app {
    void GuiController::initialize() {
        set_enable(false);
    }

    void GuiController::poll_events() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if (platform->key(engine::platform::KeyId::KEY_TAB).state() == engine::platform::Key::State::JustPressed) {
            set_enable(!is_enabled());
        }
    }

    void GuiController::draw() {
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        graphics->begin_gui();

        ImGui::Begin("Temple adventure - menu");

        if (ImGui::Button("Continue", ImVec2(120, 30))) {
            set_enable(!is_enabled());
        }

        if (ImGui::Button("Exit Game", ImVec2(120, 30))) {
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
