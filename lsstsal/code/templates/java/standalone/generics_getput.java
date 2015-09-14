package org.lsst.sal;

import org.opensplice.dds.dcps.TypeSupportImpl;
import DDS.*;
import SALData.*;

public class SALDDS {
    private T data;

    public SALDDS() {}

    public SALDDS(T t) {
        this.data = t;
    }


 	public int putSample(T data)
	{
          int status = SAL__OK;
          this.data = data
	  DataWriter dwriter = getWriter();
	  SALTopicDataWriter SALWriter = SALTopicDataWriterHelper.narrow(dwriter);
	  data.private_revCode = "LSST TEST REVCODE";
	  if (debugLevel > 0) {
	    System.out.println("=== [putSample] writing a message containing :");
	    System.out.println("    revCode  : " + this.data.private_revCode);
	  }
	  SALWriter.register_instance(this.data);
	  status = SALWriter.write(this.data, HANDLE_NIL.value);
	  checkStatus(status, "SALCommandDataWriter.write");
	  return status;
	}


	public T getSample()
	{
	  int status =  -1;
          int last = 0;
          T SALInstance = new T();
	  DataReader dreader = getReader();
	  SALTopicDataReader SALReader = SALTopicDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, LENGTH_UNLIMITED.value,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (debugLevel > 0) {
		for (int i = 0; i < SALInstance.value.length; i++) {
				System.out.println("=== [getSample] message received :");
				System.out.println("    revCode  : "
						+ SALInstance.value[i].private_revCode);
                   last = i;
		}
	  }
          if (last > 0) {
            data = SALInstance.value[last];
          }
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return data;
	}


}


