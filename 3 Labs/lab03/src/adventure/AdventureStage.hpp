#pragma once
#include "Support.hpp"
class AdventureStage;
using Stage = std::shared_ptr<AdventureStage>;
using Responses = std::map<std::string, Stage>;
class AdventureStage {
  public:
    virtual ~AdventureStage() = default;
    virtual void playStage() = 0;
    virtual std::string nextStagePrompt() const = 0;
    virtual const Responses &getResponses() const = 0;
};
