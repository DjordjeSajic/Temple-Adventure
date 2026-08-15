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

        graphics->clear_depth_buffer();
        torch_shader->use();
        torch_shader->set_mat4("projection", graphics->projection_matrix());

        glm::mat4 view = glm::mat4(1.0f);
        torch_shader->set_mat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, glm::vec3(1.3f, -1.5f, -3.0f));
        model           = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model           = glm::scale(model, glm::vec3(0.8f));
        torch_shader->set_mat4("model", model);
        torch_model->draw(torch_shader);
    }

    void SceneController::draw_temple() {
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics  = engine::core::Controller::get<engine::graphics::GraphicsController>();

        engine::resources::Model *temple_model   = resources->model("temple");
        engine::resources::Shader *temple_shader = resources->shader("basic");

        temple_shader->use();
        temple_shader->set_mat4("projection", graphics->projection_matrix());
        temple_shader->set_mat4("view", graphics->camera()->view_matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
        model           = glm::scale(model, glm::vec3(10.0f));
        temple_shader->set_mat4("model", model);

        temple_model->draw(temple_shader);
    }

    void SceneController::draw() {
        draw_temple();
        //draw_torch must always be last to be drawn because of depth buffer clearing
        draw_torch();
    }

    void SceneController::end_draw() {
        auto platfrom = engine::core::Controller::get<engine::platform::PlatformController>();
        platfrom->swap_buffers();
    }
} // app
