package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALTopicDataWriterHelper
{

    public static SALData.SALTopicDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALTopicDataWriter) {
            return (SALData.SALTopicDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALTopicDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALTopicDataWriter) {
            return (SALData.SALTopicDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
