package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALEventDataReaderHelper
{

    public static SALData.SALEventDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALEventDataReader) {
            return (SALData.SALEventDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALEventDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALEventDataReader) {
            return (SALData.SALEventDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
