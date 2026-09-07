//
// Created by djordjes on 8/4/26.
//

#include "../include/SceneController.hpp"

#include <GuiController.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <spdlog/spdlog.h>

namespace app {
void SceneController::initialize() {
    spdlog::info("SceneController initialized");
    engine::graphics::OpenGL::enable_depth_testing();
}

void SceneController::torch_action() {
    auto gui_controller = engine::core::Controller::get<GuiController>();

    if (gui_controller->is_enabled()) {
        return;
    }
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    float light_reach;

    if (platform->key(engine::platform::KeyId::KEY_E).state() == engine::platform::Key::State::JustPressed) {
        toggle_torch_lit();
    }
    if (platform->key(engine::platform::KeyId::KEY_1).is_down()) {
        light_reach = get_light_reach();
        light_reach += 0.2f;
        set_light_reach(light_reach);
    }
    if (platform->key(engine::platform::KeyId::KEY_2).is_down()) {
        light_reach = get_light_reach();
        light_reach -= 0.2f;
        if (light_reach < 0.1f)
            light_reach = 0.1f;
        set_light_reach(light_reach);
    }

    if (platform->key(engine::platform::KeyId::KEY_F).state() ==
        engine::platform::Key::State::JustPressed) {
        float current_time = platform->frame_time().current;
        float elapsed = current_time - get_torch_swing_time_start();
        constexpr float total_duration = 1.5f;
        if (elapsed > total_duration) {
            set_torch_swing_time_start(current_time);
        }
    }
}

void SceneController::update() {
    torch_action();
}

void SceneController::begin_draw() {
    engine::graphics::OpenGL::clear_buffers();
}

void SceneController::draw_torch() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

    float time = platform->frame_time().current;
    constexpr float sway_amount = 0.05f;
    constexpr float sway_speed = 1.5f;
    const float offset_x = sin(time * sway_speed) * sway_amount;
    const float offset_y = cos(time * (sway_speed * 2.0f)) * (sway_amount * 0.5f);

    engine::resources::Model *torch_model = resources->model("torch");
    engine::resources::Shader *torch_shader = resources->shader(
            get_torch_lit_status() ? "torch_on" : "basic");

    graphics->clear_depth_buffer();
    torch_shader->use();

    glm::vec3 light_dir = get_light_dir();
    glm::mat4 camera_view = graphics->camera()->view_matrix();
    glm::vec3 view_space_light_dir = glm::mat3(camera_view) * light_dir;

    torch_shader->set_vec3("lightDir", view_space_light_dir);

    torch_shader->set_mat4("projection", graphics->projection_matrix());

    glm::mat4 view = glm::mat4(1.0f);
    torch_shader->set_mat4("view", view);

    constexpr float total_duration = 1.5f;

    float elapsed = time - get_torch_swing_time_start();

    float swing_deg = 0.0f;

    if (elapsed >= 0.0f && elapsed < total_duration) {
        if (elapsed < 0.25f) {
            swing_deg = glm::mix(0.0f, -45.0f, elapsed / 0.25f);
        } else if (elapsed < 1.25f) {
            swing_deg = -45.0f;
        } else {
            swing_deg = glm::mix(-45.0f, 0.0f, (elapsed - 1.25f) / 0.25f);
        }
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.3f + offset_x, -1.5f + offset_y, -3.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(swing_deg), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.8f));

    torch_shader->set_mat4("model", model);
    torch_model->draw(torch_shader);
}

void SceneController::draw_temple() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

    engine::resources::Model *temple_model = resources->model("temple");
    engine::resources::Shader *temple_shader = resources->shader("basic");

    temple_shader->use();
    temple_shader->set_mat4("projection", graphics->projection_matrix());
    temple_shader->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(17.0f, 0.8f, 8.5f));
    model = glm::scale(model, glm::vec3(18.0f));
    temple_shader->set_mat4("model", model);
    temple_model->draw(temple_shader);
}

void SceneController::draw_jungle() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

    engine::resources::Model *jungle_model = resources->model("jungle");
    engine::resources::Shader *jungle_shader = resources->shader("basic");

    jungle_shader->use();
    jungle_shader->set_mat4("projection", graphics->projection_matrix());
    jungle_shader->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(5.0f, 0.0f, 5.0f));
    model = glm::scale(model, glm::vec3(10.0f));
    jungle_shader->set_mat4("model", model);

    jungle_model->draw(jungle_shader);
}

void SceneController::draw_skybox() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto skybox = resources->skybox(get_current_skybox());
    auto shader = resources->shader("skybox");
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    graphics->draw_skybox(shader, skybox);
}

void SceneController::setup_lighting() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();

    engine::resources::Shader *shader_used = resources->shader("basic");

    get_current_skybox() == "day_skybox"
            ? set_lighting_parameters(glm::vec3(0.3f, 0.35f, 0.4f), glm::vec3(1.0f, 0.95f, 0.8f))
            : set_lighting_parameters(glm::vec3(0.05f, 0.06f, 0.12f), glm::vec3(0.2f, 0.25f, 0.45f));

    shader_used->use();

    shader_used->set_vec3("lightDir", get_light_dir());

    shader_used->set_vec3("lightColor", get_light_color());

    shader_used->set_vec3("ambientColor", get_ambient_color());

    glm::mat4 camera_view = graphics->camera()->view_matrix();
    glm::mat4 camera_inv_view = glm::inverse(camera_view);
    glm::vec3 light_pos_view(0.1f, 0.0f, -0.1f);

    glm::vec3 light_pos_world =
            glm::vec3(camera_inv_view * glm::vec4(light_pos_view, 1.0f));

    shader_used->set_vec3("pointLightPos", light_pos_world);
    shader_used->set_vec3("pointLightColor", glm::vec3(1.0f, 0.6f, 0.2f));
    shader_used->set_float("pointLightConstant", 1.0f);
    shader_used->set_float("pointLightLinear", 0.09f / get_light_reach());
    shader_used->set_float("pointLightQuadratic", 0.032f / (get_light_reach() * get_light_reach()));
    shader_used->set_bool("torchLit", get_torch_lit_status());
}

void SceneController::draw() {
    setup_lighting();

    draw_jungle();
    draw_temple();
    draw_skybox();
    //draw_torch must always be last to be drawn because of depth buffer clearing
    draw_torch();
}

void SceneController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}
}// namespace app
