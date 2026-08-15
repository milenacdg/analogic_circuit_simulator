#pragma once
#include <memory>

namespace crt
{
    struct Component;
    struct Wire;

    using Component_ref = std::shared_ptr<Component>;
    using Wire_ref = std::shared_ptr<Wire>;

    struct Pin
    {
        double intensity;
        Component_ref component;
        Wire_ref wire;
    };

    using Pin_ref = std::shared_ptr<Pin>;

}