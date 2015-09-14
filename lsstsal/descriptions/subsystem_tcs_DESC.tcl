set SUBSYSTEM_DESC(tcs) "The main purpose of the Telescope Control System (TCS) software is to accept the target position of a celestial object, which can be given in a variety of coordinate systems, and calculate mount, rotator and optical surface positions, so that the target is imaged perfectly at a given point in the focal plane. Furthermore, the TCS is characterized by the need to integrate a number of heterogeneous subsystems, which exhibit complex interactions. These interactions, although not hard realtime bounded, need a high level of synchronization.
<P>
The Telescope Control System (TCS) is the central coordination facility for the delivery of high quality field images to the camera. It is responsible for the precise pointing and tracking calculations necessary to observe a certain field. The TCS does not itself operate any mechanical component; rather it delegates this responsibility to the various telescope subsystems and manages them according to the observation requests.
<P>
The TCS design is based on a distributed system model. Under this model, the components
interact through well defined interfaces, to accomplish the desired system behavior. The maincomponents in the proposed implementation, are tied together by the use of an Ethernet Bus, thus permitting the efficient exchange of commands and status among them.
<P>
The distributed nature of the TCS is complemented by the control model based on a
supervisory control strategy. Under this model, a supervisor agent computes the “setpoint” to be applied to a controllable device. The time critical loops are closed locally at the device level, and the device makes status information available for monitoring purposes.
<P>
The TCS itself will be controlled either directly by a telescope operator, or by commands
initiated by the Observatory Control System (OCS). Its role therefore, is to act as intermediary between the observer(s) and the telescope hardware, translating high level user commands into low level subsystem commands. Consistent with our control model, the TCS will return status information to be distributed system wide."
