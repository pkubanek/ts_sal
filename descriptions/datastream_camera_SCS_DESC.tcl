set DATASTREAM_DESC(camera_SCS) "The Shutter Controller Unit (SCU) manager software controls and synchronizes shutter operation.
<P>This subsystem maintains shutter positioning and motion information<BR>as
well as lower level shutter mechanism parameters.Deliverables:
     Shutter with mechanisms, actuators, and power supply and controller
<LI>     Shutter life test unit/testbed
<LI>     Shutter storage/transport container
<LI>     Test gantry and sensor array<P>
<P>
A rectangular aperture that moves across the array controls the exposure time for all pixels. Equal exposure time requires the opening edge and the closing edge to have the same motion profile in time. This is achieved by using one long sheet with a central rectangular aperture of constant width. For compact storage, the sheet attaches to and wraps around two rollers to form a scroll. Tthere are two closed positions so the sheet advances in the same direction from closed to open to closed. The sheet reverses direction for the next cycle.  This would be of great benefit if the minimum exposure time were much shorter than currently required. 
<P>
Controlling the exposure time to millisecond precision is equivalent to controlling position of the aperture edges to several tenths of millimeters. Standard feedforward and feedback control techniques  maintain acceptable following error (i.e., the controller component of error) for this well defined motion profile. Placing sensors on the rollers is easy and reliable and the average of the two accounts for the effective roller radius changing as the sheet rolls up on itself. This effect is small for a thin metal sheet. In addition, a metal sheet is opaque, does not outgas, can be processed for high fatigue strength and low wear, and is stable and rigid in plane."
