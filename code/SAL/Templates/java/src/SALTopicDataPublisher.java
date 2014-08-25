/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to 2013 PrismTech
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $OSPL_HOME/LICENSE 
 *
 *   for full copyright notice and license terms. 
 *
 */


import SALData.SALTopic;
import SALData.SALTopicDataWriter;
import SALData.SALTopicDataWriterHelper;
import SALData.SALTopicTypeSupport;
import org.lsst.sal.SALDDS;

public class SALTopicDataPublisher {

	public static void main(String[] args) {
		SALDDS mgr = new SALDDS();
                mgr.salInitialize();

		// Publish Telemetry
		int count=0;
		mgr.salTelemetryPub("SALData_SALTopic");
		SALTopic SALTopicInstance = new SALTopic();
		while (true) {
			mgr.putSample(SALTopicInstance);
			System.out.println("=== [SALTopic Publisher] message sent" + count);
			try {
				Thread.sleep(4000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			++count;
		}
		// clean up
		//mgr.salShutdown();
	}
}

