#include <vector>
#include <string>

#ifndef __RANGE_FOR_HPP__
#define __RANGE_FOR_HPP__

namespace cppexamples
{

// Custom class forwarding iterators from private vector to support range-based for loops
class TemperatureSensor
{
public:
    explicit TemperatureSensor(std::string location) :
            m_location(std::move(location))
    {
    }

    void add_reading(float temp)
    {
        m_readings.push_back(temp);
    }

    auto begin() const
    {
        return m_readings.begin();
    }

    auto end() const
    {
        return m_readings.end();
    }

private:
    std::string m_location;
    std::vector<float> m_readings;
};

class VibrationSensor;

// Iterator class for VibrationSensor
class VibrationIterator
{
public:
    VibrationIterator(const VibrationSensor& sensor, int pos) :
            m_pos(pos), m_sensor(sensor)
    {
    }

    bool operator!=(const VibrationIterator& other) const
    {
        return m_pos != other.m_pos;
    }

    const std::pair<float, float>& operator*() const;

    const VibrationIterator& operator++()
    {
        ++m_pos;
        return *this;
    }

private:
    int m_pos;
    const VibrationSensor& m_sensor;
};

// Custom class with custom iterator to support range-based for loops
class VibrationSensor
{
public:
    static const int max_size = 3;

    VibrationSensor() = default;

    void add_reading(float velocity, float frequency)
    {
        m_vibrations[m_index] = std::make_pair(velocity, frequency); //NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
        m_index = (m_index < 2U) ? m_index + 1 : 0U;
    }

    auto begin() const
    {
        return VibrationIterator(*this, 0);
    }

    auto end() const
    {
        return VibrationIterator(*this, max_size);
    }

    const auto& get(unsigned int index) const
    {
        return m_vibrations[index]; //NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    }

private:
    unsigned int m_index = 0;
    std::pair<float, float> m_vibrations[max_size];
};

}
#endif
