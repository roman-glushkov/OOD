#pragma once

// интерфейс команд
class ICommand 
{
public:
    virtual ~ICommand() = default;
    virtual void Execute() = 0;
};
