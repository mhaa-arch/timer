#include <timer/timer.hpp>
#include "fake.hpp"

using namespace mhaa::timer;
using namespace example;

int main()
{
    Fake counter(16);
    Timer timer(counter);
    const Count start = timer.ticks();
    timer.start();
    const Count elapsed = timer.elapsed_since(start);
    timer.stop();
    return elapsed == 0 ? 0 : 1;
}
