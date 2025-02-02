#pragma once
#include <iostream>

class Message
{
public:
    std::string gameId;
    std::string objectId;
    std::string operationId;
    std::string args;

    Message(std::string gameId, std::string objectId,
            std::string operationId, std::string args)
    {
        this->gameId = gameId;
        this->objectId = objectId;
        this->operationId = operationId;
        this->args = args;
    }

    std::string getGameId()
    {
        return gameId;
    }
    std::string getObjectId()
    {
        return objectId;
    }
    std::string getOperationId()
    {
        return operationId;
    }
    std::string getArgs()
    {
        return args;
    }
};

class Builder
{
public:
    std::string gameId;
    std::string objectId;
    std::string operationId;
    std::string args;

    Builder* setGameId(std::string gameId)
    {
        this->gameId = gameId;
        return this;
    }
    Builder* setObjectId(std::string objectId)
    {
        this->objectId = objectId;
        return this;
    }
    Builder* setOperationId(std::string operationId)
    {
        this->operationId = operationId;
        return this;
    }
    Builder* setArgs(std::string args)
    {
        this->args = args;
        return this;
    }
    Builder* clear()
    {
        this->gameId.clear();
        this->objectId.clear();
        this->operationId.clear();
        this->args.clear();
        return this;
    }
    Message* build()
    {
        return new Message(gameId, objectId, operationId, args);
    }
};
