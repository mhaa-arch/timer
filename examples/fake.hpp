#ifndef MHAA_TIMER_EXAMPLE_FAKE_HPP
#define MHAA_TIMER_EXAMPLE_FAKE_HPP

#include <timer/counter.hpp>
#include <timer/clock_control.hpp>
#include <timer/compare_control.hpp>
#include <timer/input_capture.hpp>

namespace example
{
    using namespace mhaa::timer;

    class Fake final : public Counter
    {
    public:
        explicit Fake(uint8_t width) : width_(width) {}
        uint8_t width_bits() const override { return width_; }
        void start() override { running = true; }
        void stop() override { running = false; }
        Count value() const override { return count_; }
        bool set_value(Count count) override
        {
            if (width_ < 32 && count >= (Count{1} << width_))
            {
                return false;
            }
            count_ = count;
            return true;
        }

        bool running = false;

    private:
        uint8_t width_;
        Count count_ = 0;
    };
}

#endif
