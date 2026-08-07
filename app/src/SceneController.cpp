//
// Created by djordjes on 8/4/26.
//

#include "../include/SceneController.hpp"

#include <engine/graphics/GraphicsController.hpp>
#include <spdlog/spdlog.h>

namespace app {
    void SceneController::initialize() {
        spdlog::info("SceneController initialized");
        engine::graphics::OpenGL::enable_depth_testing();
    }

    void SceneController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void SceneController::draw_torch() {
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        engine::resources::Model *torch_model = resources->model("torch");
        engine::resources::Shader *torch_shader = resources->shader("basic");
        torch_shader->use();
        torch_shader->set_mat4("projection", graphics->projection_matrix());
        torch_shader->set_mat4("view", graphics->camera()->view_matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
        model           = glm::scale(model, glm::vec3(0.3f));
        torch_shader->set_mat4("model", model);

        torch_model->draw(torch_shader);
    }

    void SceneController::draw() {
        draw_torch();
    }

    void SceneController::end_draw() {
        auto platfrom = engine::core::Controller::get<engine::platform::PlatformController>();
        platfrom->swap_buffers();
    }
} // app
