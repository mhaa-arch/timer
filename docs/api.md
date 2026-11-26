# Use the Timer Core

Public entry headers are [timer/timer.hpp](../include/timer/timer.hpp).

## Use ticks and wrap arithmetic

Construct `Timer` from `Counter&`. Call `start` and `stop` to run or pause, and use `ticks` for a snapshot. `width_bits` reports the native range. After an accepted `set_ticks`, discard elapsed measurements that reference the previous count sequence.

`elapsed_since(previous)` subtracts modulo the counter width. Pass a snapshot of the same running sequence and measure less than one full counter period with a stable width. A complete wrap or more is ambiguous.

Construct with `ClockControl&` to set a nominal tick rate. Pass compare and capture pointers for the same timer. Missing or rejected options return false. A failed capture preserves the timestamp argument.

## Composition and lifetime

Application code calls the Timer Core. It borrows the matching Contract, which an Adapter implements using its Hardware Definitions. Future Devices will create or bind these objects and establish their lifetime. To use the examples today, construct the facade directly with the supplied fake. Keep each borrowed resource alive for its use by the facade and follow the Adapter's access and synchronization requirements.
