#ifndef EMPTY_H
#define EMPTY_H
#include "element.h"
#include "elements_data.h"
#include "resource_manager.h"

class empty final :
    public element
{
public:
    empty()
    {
        id = ELEMENT_EMPTY
    	sprite = resource_manager::get_texture("empty");
        color = glm::vec3(0.0f);
    }

    void step(std::vector<std::vector<element*>> elements) override;
    bool receive_heat() override;
};

inline void empty::step(std::vector<std::vector<element*>> elements)
{
}

inline bool empty::receive_heat()
{
    return true;
}
#endif
