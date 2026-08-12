//
// Created by djordjes on 8/4/26.
//

#include "../include/TempleAdventure.hpp"

#include <ApplicationController.hpp>
#include <PlayerController.hpp>
#include <SceneController.hpp>
#include <spdlog/spdlog.h>

namespace app {
    void TempleAdventure::app_setup() {
        spdlog::info("App setup works for Temple Adventure");
        auto application_controller = register_controller<app::ApplicationController>();
        application_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());

        auto scene_controller = register_controller<app::SceneController>();
        scene_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());

        auto player_controller = register_controller<app::PlayerController>();
        scene_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
    }
} // app
