#pragma once


namespace llgl 
{

class Object
{
public:
    virtual ~Object() = default;

    virtual bool draw() = 0;

private:
};


} // namespace llgl