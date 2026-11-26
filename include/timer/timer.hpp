#ifndef MHAA_TIMER_HPP
#define MHAA_TIMER_HPP

#include <stdint.h>
#include <timer/counter.hpp>
#include <timer/clock_control.hpp>
#include <timer/compare_control.hpp>
#include <timer/input_capture.hpp>
#include <timer/types.hpp>

namespace mhaa
{
    namespace timer
    {
        /** @brief Operates a borrowed up counter and computes elapsed ticks across a wrap. */
        class Timer
        {
        public:
            explicit Timer(Counter &counter, CompareControl *compare = nullptr,
                           InputCapture *capture = nullptr)
                : counter_(counter), clock_(nullptr), compare_(compare), capture_(capture) {}

            explicit Timer(ClockControl &counter, CompareControl *compare = nullptr,
                           InputCapture *capture = nullptr)
                : counter_(counter), clock_(&counter), compare_(compare), capture_(capture) {}

            void start() { counter_.start(); }
            void stop() { counter_.stop(); }
            Count ticks() const { return counter_.value(); }

            uint8_t width_bits() const { return counter_.width_bits(); }
            bool set_ticks(Count count) { return counter_.set_value(count); }

            bool set_tick_frequency_hz(uint32_t frequency_hz)
            {
                return clock_ && frequency_hz != 0 && clock_->set_tick_frequency_hz(frequency_hz);
            }

            bool set_compare(ChannelId channel, Count threshold)
            {
                return compare_ && compare_->set_compare(channel, threshold);
            }

            /** @brief Preserves count if capture is unavailable or no event is ready. */
            bool try_capture(Count &count) { return capture_ && capture_->try_capture(count); }

            /** @brief Computes elapsed ticks modulo the counter width. */
            Count elapsed_since(Count previous) const
            {
                const uint8_t width = width_bits();
                const Count elapsed = ticks() - previous;
                return width == 32 ? elapsed : elapsed & ((Count{1} << width) - 1);
            }

        private:
            Counter &counter_;
            ClockControl *clock_;
            CompareControl *compare_;
            InputCapture *capture_;
        };
    }
}

#endif
