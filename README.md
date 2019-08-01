# BotWarz
Eset BotWarz Challenge

My solution of ESET BotWarz challenge. The competition of algorithms fighting against each other with a bot controlled over the TCP connection.

Implemented in C++ (Visual Studio). Speed of the answer was proven to be one of the deciding factors (besides the network speed to the ESET server). 

Unit tests are written in CppUnit.

Solution contains simple 2D geometry, simple trajectory planning and few simple heuristics how to choose the movement direction in order to attack the closest enemy bot considering also the speed of rotation and acceleration.

Unfortunately the challenge does not run anymore. Most of the time this algorithm was ranked #1 - #3.
