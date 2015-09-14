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


import SALData.SALTopicDataReader;
import SALData.SALTopicDataReaderHelper;
import SALData.SALTopicSeqHolder;
import SALData.SALTopicTypeSupport;
import SALData.SALTopic;
import org.lsst.sal.SALDDS;

public class SALTopicDataSubscriber {

	public static void main(String[] args) {
		SALDDS mgr = new SALDDS();
                mgr.salInitialize();
		mgr.salTelemetrySub("SALData_SALTopic");

		SALTopic SALInstance = new SALTopic();
                System.out.println ("=== [SALTopic Subscriber] Ready ...");

		boolean terminate = false;
		int count = 0;
                int samples = 0;
		while (!terminate && count < 1500) { // We dont want the example to run indefinitely
                        samples = mgr.getSample(SALInstance);
                        if (samples > 0) {
  			   System.out.println("=== [SALTopic Subscriber] samples");
			   System.out.println("=== [SALTopic Subscriber] message received :" + count + "(" + samples + ")");
			   System.out.println("    revCode  : "+ SALInstance.private_revCode);
			}
			try
			{
				Thread.sleep(200);
			}
			catch(InterruptedException ie)
			{
				// nothing to do
			}
			++count;
			
		}
 		
		// clean up
		mgr.salShutdown();

	}
}


