#pragma once

namespace CoffeeShop
{

struct Mug
{
    Mug(int temperatureThreshold) :
        m_threshold(temperatureThreshold)
    {

    }

    bool full() const
    {
        return fillStand >= 100;
    }
    bool hot() const
    {
        return temperature >= m_threshold;
    }

    int temperature = 20;
    int fillStand = 0;
private:
    int m_threshold;
};

} // namespace CoffeeShop
