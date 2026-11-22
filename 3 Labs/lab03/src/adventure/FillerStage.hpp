#pragma once
#include "AdventureStage.hpp"
class FillerStage : public AdventureStage {
    std::string prompt;
    Responses responses;

  public:
    explicit FillerStage(std::string p, Responses r = {}) : prompt(p), responses(r) {}
    void playStage() override {}
    std::string nextStagePrompt() const override {
        return prompt;
    }
    const Responses &getResponses() const override {
        return responses;
    }
};
