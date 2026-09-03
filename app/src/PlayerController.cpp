//
// Created by djordjes on 8/12/26.
//

#include "../include/PlayerController.hpp"

#include <GuiController.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <spdlog/spdlog.h>

namespace app {
    class PlayerPlatfromEventObserver : public::engine::platform::PlatformEventObserver {
    public:
        void on_mouse_move(engine::platform::MousePosition position) override;
    };

    void PlayerPlatfromEventObserver::on_mouse_move(engine::platform::MousePosition position) {
        auto gui_controller = engine::core::Controller::get<GuiController>();
        if (!gui_controller->is_enabled()) {
            auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
            camera->rotate_camera(position.dx, position.dy);
        }
    }

    void PlayerController::initialize() {
        spdlog::info("PlayerController::initialize");

        auto player_observer = std::make_unique<PlayerPlatfromEventObserver>();
        auto platform        = engine::core::Controller::get<engine::platform::PlatformController>();

        platform->register_platform_event_observer(std::move(player_observer));
        platform->set_enable_cursor(false);
    }

    void PlayerController::player_movement_keyboard() {
        auto gui_controller = engine::core::Controller::get<GuiController>();

        if (gui_controller->is_enabled()) {
            return;
        }
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera   = graphics->camera();
        float dt      = platform->dt();
        if (platform->key(engine::platform::KeyId::KEY_W).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
        }

        if (platform->key(engine::platform::KeyId::KEY_S).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
        }

        if (platform->key(engine::platform::KeyId::KEY_A).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
        }

        if (platform->key(engine::platform::KeyId::KEY_D).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt * 0.75);
        }
        if (platform->key(engine::platform::KeyId::KEY_SPACE).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::UP, dt * 0.50);
        }
        if (platform->key(engine::platform::KeyId::KEY_LEFT_CONTROL).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::DOWN, dt * 0.50);
        }
    }

    void PlayerController::update() {
        player_movement_keyboard();
    }
} // app
