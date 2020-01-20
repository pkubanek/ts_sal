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
When programming with SAL it is important to use proper acknowledgments. With consistent acknowledgements project wide we can reduce confusion and need for looking at acknowldgment definitons. Below are the list of acknowledgements you can use.

**CMD_ACK = 300**
   Sent by the commanded application. The application has accepted the command.

**CMD_INPROGRESS = 301**
   Sent by the commanded application. The application has accepted the command and is processing the command.

**CMD_STALLED = 302**
   Sent by the commanded application. The application has accepted the command and is expected to process for a *long* time. Useful when an application needs to cool down or warm up before it can continue. Can also send the average time expected to execute the command.

**CMD_COMPLETE = 303**
   Sent by the commanded application. The application has completed the command. 

**CMD_NOPERM = -300**
   Sent by the whitelister. This Ack is returned to the commanding application when the application tries to send a command to a CSC is it not allowed to.

**CMD_NOACK = -301**
   Sent by SAL. This Ack is returned to the commanding application when application asks for an ack and there is nothing to send a response. 

**CMD_FAILED = -302**
   Sent by the commanded application. Can (hopefully) also send details on why the command has failed.

**CMD_ABORTED = -303**
   Sent by the commanded application. This ack is returned to the commanding application when the commanded application has abborted. 

**CMD_TIMEOUT = -304**
   Sent by the commanded application. This ack is returned to the commanding application when the commanded application has timed out. Useful when you have a lower level software that is not responsive and unable to perform the command.
 
Failures
	The following Ack's are considered failures. 
	CMD_STALLED = 302
	CMD_NOPERM = -300
	CMD_FAILED = -302
	CMD_ABORTED = -303
	CMD_TIMEOUT = -304


.. toctree::
   :maxdepth: 2

Project information
===================

.. toctree::
   :maxdepth: 2

   revision_history
