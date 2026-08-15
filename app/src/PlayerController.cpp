//
// Created by djordjes on 8/12/26.
//

#include "../include/PlayerController.hpp"

#include <engine/graphics/GraphicsController.hpp>
#include <spdlog/spdlog.h>

namespace app {
    class PlayerPlatfromEventObserver : public::engine::platform::PlatformEventObserver {
    public:
        void on_mouse_move(engine::platform::MousePosition position) override;
    };

    void PlayerPlatfromEventObserver::on_mouse_move(engine::platform::MousePosition position) {
        auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
        camera->rotate_camera(position.dx, position.dy);
    }

    void PlayerController::initialize() {
        spdlog::info("PlayerController::initialize");

        auto player_observer = std::make_unique<PlayerPlatfromEventObserver>();
        auto platform        = engine::core::Controller::get<engine::platform::PlatformController>();

        platform->register_platform_event_observer(std::move(player_observer));

        platform->set_enable_cursor(false);
    }

    void PlayerController::player_movement_keyboard() {
        auto platfrom = engine::core::Controller::get<engine::platform::PlatformController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera   = graphics->camera();
        float dt      = platfrom->dt();
        if (platfrom->key(engine::platform::KeyId::KEY_W).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
        }

        if (platfrom->key(engine::platform::KeyId::KEY_S).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
        }

        if (platfrom->key(engine::platform::KeyId::KEY_A).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
        }

        if (platfrom->key(engine::platform::KeyId::KEY_D).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt * 0.75);
        }
    }

    void PlayerController::update() {
        player_movement_keyboard();
    }
} // app
