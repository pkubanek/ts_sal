package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALResponseDataReaderHelper
{

    public static SALData.SALResponseDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALResponseDataReader) {
            return (SALData.SALResponseDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALResponseDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALResponseDataReader) {
            return (SALData.SALResponseDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
