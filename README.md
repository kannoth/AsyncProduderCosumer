# Asynchronous Produder Consumer
A small protocol for producer consumer thread synchronization. The producer state machine produces data and waits until
cosumer consumes it. This idea can be adopted to any platforms or especially for hardware circuits specified in vHDL or verilog two threads can even if operate on different clock domains, the protocol ensures there is not data lost. The soul
purpose if FIFOs can be avoided. The soul purpose of the prototype inthe repository was to send data from FPGA to an processor which were running on different clock domains.
