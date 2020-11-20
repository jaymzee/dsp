wave - read and write wav files
----------------------------------
For writing filters, it's most efficient to stream the data itself on the fly,
instead of allocating memory buffers for it.

Note: to simplify the implementation, this assumes a little endian machine
which is pretty much any of the major platforms anyone would probably use
with this anyway.

filters - signal processing
---------------------------
    canfltr             canonical filter (c module)
    directForm2         canonical filter (c++ class)
    cirfltr             circular buffer filter (c module)
    circular            circular buffer filter (c++ class)
    delayline           fractional delay line (c module)
    delay               fractional delay line (c++ class)
