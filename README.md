# Analogic Circuit Simulator
Implementation of a library for designing an analogical circuit and solving its functioning point.


## Membrers
Aurélie, Enzo, Miléna

## Documents
The rapport is available on the following link :


The presentation is available by clicking on this link :
https://github.com/milenacdg/analogic_circuit_simulator/blob/main/livrables/presentation/main.pdf


## Context

An analogical circuit is made of components and wires. Components have pins that are connected to wires. The number of pins depend on the type of components. A resistor has two pins, a transistor has three pins… etc.


## Our work
Our goal is to implement a library for designing a circuit and solving its functioning point.
    First on a linear circuit (only resistors and voltage source),
    Then on a simple non-linear circuit including a diode (use the Shockley diode model),
    Finally on a small circuit including transistors (use the unapproximated Ebers Moll model),

Then we tried to :

    - Improve the resolution scheme, using gradient descent.
    - Provide viewers a way to visualize the circuit using graphviz.





