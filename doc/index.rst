.. py:currentmodule:: lsst.ts.sal

.. _lsst.ts.salobj:

###########
lsst.ts.sal
###########

`Service Abstraction Layer`_ (SAL) is LSST's communications middleware. Built on top of Object Management Group's Data Distribution Service (OMG DDS) standard. Developed by ADLINK's product called Vortex Opensplice. 

.. _Service Abstraction Layer: https://docushare.lsstcorp.org/docushare/dsweb/Get/Document-21527

.. _lsst.ts.sal-acknowledgments:

Acknowledgments
===============
When programming with SAL it is important to use proper acknowledgments. With consistent acknowledgements project wide we can reduce confusion and need for looking at acknowldgment definitons. Below are the list of acknowledgements you can use. *Client* in this context refers to the commanding CSC, or the Commander, or the Controller. *Server* in this context refers to the receiving CSC, or the Processor, or the Remote. 

**CMD_ACK = 300**
   Sent by the Server. The Server has accepted the command.

**CMD_INPROGRESS = 301**
   Sent by the Server. The Server has accepted the command and is processing the command.

**CMD_STALLED = 302**
   Sent by the Server. The Server has accepted the command and is expected to process for a *long* time. Useful when an application needs to cool down or warm up before it can continue. Can also send the average time expected to execute the command.

**CMD_COMPLETE = 303**
   Sent by the Server. The Server has completed the command. 

**CMD_NOPERM = -300**
   Sent by the whitelister. This Ack is returned to the Client when the Client tries to send a command to a Server it is not allowed to.

**CMD_NOACK = -301**
   Sent by SAL. This Ack is returned to the Client when the Client asks for an ack and there is nothing to send a response. This Ack is returned if there is no response from the commanded application.

.. note:: There are two ways for the Client to ask the Server for an Ack. One way is waitForCompletion that accepts a timeout. The other way is getResponse which will immedietly ask for an Ack and return CMD_NOACK.

**CMD_FAILED = -302**
   Sent by the Server. Can (hopefully) also send details on why the command has failed.
   
**CMD_ABORTED = -303**
   Sent by the Server. This ack is returned to the Client when the Server has aborted. 

**CMD_TIMEOUT = -304**
   Sent by the Server. This ack is returned to the Client when the Server has timed out. Useful when you have a lower level software that is not responsive and unable to perform the command.
 
CMD_ACK, CMD_INPROGRESS and CMD_STALLED are not final: the caller can expect further acknowledgements for the command. All other codes are final, and all of those except CMD_COMPLETE and CMD_NOACK indicate failure.

.. note:: In ts_SALObj API CMD_NOACK is considered a failure


As Russell did not follow the ts_sal convention of salCommander / salProcessor in the salobj API I suggest you use the neutral convention of Client/Server BUT add clear examples of the use of both ts_sal and ts_salobj API’s ie for ts_sal  Commander/Processor, for ts_salobj Controller/Remote

.. toctree::
   :maxdepth: 2
