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


import DDS.DataWriter;
import DDS.HANDLE_NIL;
import SALData.SALTopic;
import SALData.SALTopicDataWriter;
import SALData.SALTopicDataWriterHelper;
import SALData.SALTopicTypeSupport;

public class NOSALDataPublisher {

	public static void main(String[] args) {
		SALDDS mgr = new SALDDS();
		String partitionName = "SAL LSST";

		// create Domain Participant
		mgr.createParticipant(partitionName);

		// create Type
		SALTopicTypeSupport SALTopicTS = new SALTopicTypeSupport();
		mgr.registerType(SALTopicTS);

		// create Topic
		mgr.createTopic("SALData_SALTopic");

		// create Publisher
		mgr.createPublisher();

		// create DataWriter
		mgr.createWriter();

		// Publish Events

		DataWriter dwriter = mgr.getWriter();
		SALTopicDataWriter SALWriter = SALTopicDataWriterHelper.narrow(dwriter);
		SALTopic SALTopicInstance = new SALTopic();
		SALTopicInstance.private_revCode = "LSST TEST REVCODE";
		System.out.println("=== [Publisher] writing a message containing :");
		System.out.println("    revCode : " + SALTopicInstance.private_revCode);
		SALWriter.register_instance(SALTopicInstance);
		int status = SALWriter.write(SALTopicInstance, HANDLE_NIL.value);
		ErrorHandler.checkStatus(status, "SALTopicDataWriter.write");
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		// clean up
		mgr.getPublisher().delete_datawriter(SALWriter);
		mgr.deletePublisher();
		mgr.deleteTopic();
		mgr.deleteParticipant();

	}
}
