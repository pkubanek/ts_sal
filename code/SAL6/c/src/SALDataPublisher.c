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


#include <stdlib.h>
#include <stdio.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <string.h>
#include "dds_dcps.h"
#include "CheckStatus.h"
#include "SALDDS.h"

#include "example_main.h"

/* entry point exported so symbol can be found in shared library */
OS_API_EXPORT
int SALDataPublisher(int argc, const char *argv[])
{
   DDS_DomainParticipant domainParticipant;
   DDS_Publisher message_Publisher;
   DDS_DataWriter message_DataWriter;
   DDS_Topic messageTopic;
   DDS_TypeSupport messageTypeSupport;
   SALData_SALTopic* message_Sample;
   DDS_char SAL [] = "LSST TEST REVCODE";
   os_time delay_1s = { 1, 0 };
   char* messageTypeName;
   DDS_unsigned_long SALLength = sizeof(SAL) - 1;

   printf("=== SALPublisher");

   // Create DDS DomainParticipant
   // Removed to comply with expected results
   //printf("\n create Participant...");
   domainParticipant = createParticipant("SAL example");

   // Register the Topic's type in the DDS Domain.
   messageTypeSupport = SALData_SALTopicTypeSupport__alloc();
   checkHandle(messageTypeSupport, "SALData_SALTopicTypeSupport__alloc");
   registerMessageType(domainParticipant, messageTypeSupport);
   // Create the Topic's in the DDS Domain.
   messageTypeName = SALData_SALTopicTypeSupport_get_type_name(messageTypeSupport);
   messageTopic = createTopic(domainParticipant, "SALData_SALTopic", messageTypeName);
   DDS_free(messageTypeName);
   DDS_free(messageTypeSupport);

   // Create the Publisher's in the DDS Domain.
   message_Publisher = createPublisher(domainParticipant);

   // Request a Writer from the the Publisher.
   message_DataWriter = createDataWriter(message_Publisher, messageTopic);

   message_Sample = SALData_SALTopic__alloc();

   message_Sample->private_revCode = DDS_string_alloc(SALLength);
   strcpy(message_Sample->private_revCode, SAL);

   printf("\n=== [Publisher] writing a message containing :");
   printf("\n    revCode  : %d", message_Sample->private_revCode);
   fflush(stdout);

   g_status = SALData_SALTopicDataWriter_write(message_DataWriter, message_Sample, DDS_HANDLE_NIL);
   checkStatus(g_status, "SALData_SALTopicDataWriter_write");
   os_nanoSleep(delay_1s);
   // Removed to comply with expected results
   //printf("\n=== [SALDataPublisher] Exiting.\n\n");

   // Cleanup DDS
   deleteDataWriter(message_Publisher, message_DataWriter);
   deletePublisher(domainParticipant, message_Publisher);
   deleteTopic(domainParticipant, messageTopic);
   deleteParticipant(domainParticipant);

   // Cleanup C allocations
   // Recursively free the instances sequence using the OpenSplice API.
   DDS_free(message_Sample);

   return 0;
}

int OSPL_MAIN (int argc, const char *argv[])
{
   return SALDataPublisher (argc, argv);
}
