package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALCommandDataReaderHelper
{

    public static SALData.SALCommandDataReader narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALCommandDataReader) {
            return (SALData.SALCommandDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALCommandDataReader unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALCommandDataReader) {
            return (SALData.SALCommandDataReader)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
