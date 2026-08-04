//
// Created by djordjes on 8/4/26.
//

#include "../include/ApplicationController.hpp"

#include <spdlog/spdlog.h>

namespace app {
    void ApplicationController::initialize() {
        spdlog::info("ApplicationController initialized");
    }

    bool ApplicationController::loop() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) {
            return false;
        }
        return true;
    }
} // app
