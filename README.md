The virtual sprayer receiver (VSRX) is part of the virtual sprayer project.  The following describes the interfaces for tshis module and how it operates.

Inputs
------
Button
Wireless receiver (serial input)

Outputs
-------
x3 - valve control
Board LED


Day in the Life
----------------
The following details the operation of the virtual sprayer receiver.  

1. The virtual sprayer receiver (VSRX) is tasked with turning on the sprayer when the told to do so.
2. The VSRX controls three different sprayers.  Any number of patterns can be created.
3. Due to flow restrictions on the valves, only two valves should be turned on at any time.
4. If the little black button is pressed, one of the pre-defined patters sprays.
5. If the wireless reciever receives the following 8 byte pattern (the trigger), that is equivalent to the little black button being pressed.
6. The pattern that is looked for is 'A5A5_9ACE_A5A5_1357'
7. A counter will record the number of times that the pattern is received.  The counter will have a maximum count of four.  While the counter is at four, any additional trigger receptions will be discarded. 
