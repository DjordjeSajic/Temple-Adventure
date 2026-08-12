//
// Created by djordjes on 8/12/26.
//

#ifndef MATF_RG_PROJECT_PLAYERCONTROLLER_HPP
#define MATF_RG_PROJECT_PLAYERCONTROLLER_HPP
#include <engine/core/Engine.hpp>

namespace app {
    class PlayerController : public::engine::core::Controller {
    public:
        std::string_view name() const override {
            return "app::PlayerController";
        }

    private:
        void initialize() override;

        void player_movement_keyboard();

        void update() override;
    };
} // app

#endif //MATF_RG_PROJECT_PLAYERCONTROLLER_HPP
