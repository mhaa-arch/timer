#include <timer/timer.hpp>
#include "../examples/fake.hpp"

#include <cassert>

using namespace mhaa::timer;
using namespace example;

class AdjustableTimer final : public ClockControl, public CompareControl, public InputCapture
{
public:
    uint8_t width_bits() const override { return counter_.width_bits(); }
    void start() override { counter_.start(); }
    void stop() override { counter_.stop(); }
    Count value() const override { return counter_.value(); }
    bool set_value(Count count) override { return counter_.set_value(count); }

    bool set_tick_frequency_hz(uint32_t rate_hz) override
    {
        if (rate_hz != 1000)
        {
            return false;
        }
        frequency_hz = rate_hz;
        return true;
    }

    bool set_compare(ChannelId channel, Count threshold) override
    {
        if (channel != ChannelId{} || threshold > UINT16_MAX)
        {
            return false;
        }
        threshold_ = threshold;
        return true;
    }

    bool try_capture(Count &count) override
    {
        if (!capture_ready_ || value() != threshold_)
        {
            return false;
        }
        count = value();
        capture_ready_ = false;
        return true;
    }

    uint32_t frequency_hz = 0;

private:
    Fake counter_{16};
    Count threshold_ = 0;
    bool capture_ready_ = true;
};

int main()
{
    Fake small(8);
    Fake large(32);
    Timer narrow(small);
    Timer wide(large);
    narrow.start();
    assert(small.running && !large.running);
    assert(!small.set_value(256));
    assert(small.set_value(3) && narrow.elapsed_since(255) == 4);
    assert(large.set_value(3) && wide.elapsed_since(UINT32_MAX) == 4);
    narrow.stop();
    assert(!small.running && narrow.ticks() == 3);

    Count captured = 50;
    assert(!narrow.try_capture(captured) && captured == 50);
    assert(!narrow.set_compare(ChannelId{}, 20));
    assert(!narrow.set_tick_frequency_hz(1000));
    AdjustableTimer adjustable;
    Timer timer(adjustable, &adjustable, &adjustable);
    assert(timer.width_bits() == 16);
    assert(!timer.set_tick_frequency_hz(0) && timer.set_tick_frequency_hz(1000));
    assert(adjustable.frequency_hz == 1000);
    assert(!timer.set_compare(static_cast<ChannelId>(1), 20));
    assert(timer.set_compare(ChannelId{}, 20));
    assert(timer.set_ticks(20) && timer.ticks() == 20);
    assert(timer.try_capture(captured) && captured == 20);
    assert(!timer.try_capture(captured) && captured == 20);
}
