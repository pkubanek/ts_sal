package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALTopicDataReaderViewHelper
{

    public static SALData.SALTopicDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALTopicDataReaderView) {
            return (SALData.SALTopicDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALTopicDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALTopicDataReaderView) {
            return (SALData.SALTopicDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
