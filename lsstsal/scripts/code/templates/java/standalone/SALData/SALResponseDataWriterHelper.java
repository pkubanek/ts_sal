package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALResponseDataWriterHelper
{

    public static SALData.SALResponseDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALResponseDataWriter) {
            return (SALData.SALResponseDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALResponseDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALResponseDataWriter) {
            return (SALData.SALResponseDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
