# Service Access Layer

Provides tools to generate from XML description language and database bindings
for LSST commands, events and telemetry. Depends on ts\_openslice.

# Usage

To get needed github projects and setup environment variables, do:

```bash
git clone https://github.com/lsst-ts/ts_opensplice
git clone https://github.com/lsst-ts/ts_sal
source ts_sal/setup.env
```

After that, you shall be able to call salgenerator and see it producing a help
text. Please see [test README](test/README.md) for details.
