//
// Created by djordjes on 8/4/26.
//

#include <ApplicationController.hpp>
#include <GuiController.hpp>
#include <PlayerController.hpp>
#include <SceneController.hpp>
#include <TempleAdventure.hpp>
#include <spdlog/spdlog.h>

namespace app {
void TempleAdventure::app_setup() {
    spdlog::info("App setup works for Temple Adventure");
    auto application_controller = register_controller<app::ApplicationController>();
    application_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());

    auto scene_controller = register_controller<app::SceneController>();
    scene_controller->after(application_controller);

    auto player_controller = register_controller<app::PlayerController>();
    player_controller->after(scene_controller);

    auto gui_controller = register_controller<app::GuiController>();
    gui_controller->after(player_controller);
}
}// namespace app
