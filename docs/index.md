# Timer Core guide

A timestamp is a position in a modulo counter. Elapsed arithmetic has a unique answer only within one full counter period.

Read the counter width and wrap semantics before comparing timestamps or applying optional clock controls.

- [Use the facade](api.md) for construction, results and optional capabilities.
- [Run the example](examples.md) to see the same API with a simulated resource.
- [Check portability](compatibility.md) for assumptions that belong to the target.
