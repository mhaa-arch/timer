# Run the Timer Core example

The Core borrows a 16-bit fake, snapshots its initial ticks, starts it, asks for elapsed ticks and stops it. The simulated counter does not advance by itself, so elapsed ticks are zero. Use the behavior test to follow an eight-bit wrap, a 32-bit wrap and optional capture from a different implementation.

## Example program

The [program](../examples/example.cpp) uses the [local fake](../examples/fake.hpp) to demonstrate injection. A concrete Adapter implementing the same Contract can be supplied to the same facade.

```cpp
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
```

## Build and run

Build from this repository root. Set `contract_include` to the matching Contract's `include/` directory. The value below applies to the MHAA development workspace. Both programs exit with status 0 on success and print no output. On Windows execute `example.exe` and `behavior.exe`.

```sh
contract_include=../../contracts/timer-contract/include
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" examples/example.cpp -o example
./example
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" tests/behavior.cpp -o behavior
./behavior
```

See the [behavior test](../tests/behavior.cpp) for the additional cases described above.
