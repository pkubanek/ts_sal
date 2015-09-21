package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALTopicDataReaderHelper
{

    public static SALData.SALTopicDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALTopicDataReader) {
            return (SALData.SALTopicDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALTopicDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALTopicDataReader) {
            return (SALData.SALTopicDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
