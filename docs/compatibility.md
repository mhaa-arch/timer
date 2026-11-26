# Using Timer across targets

The only project dependency is the matching `timer-contract`. Keep its API revision aligned with this Core.

Elapsed arithmetic works the same way for compatible 8-bit and 32-bit counters, but the full period before ambiguity differs. Converting ticks into time depends on a separately known tick rate. Reading and modifying a hardware timer concurrently requires the guarantees of its Adapter.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
