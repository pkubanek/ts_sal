package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALCommandDataWriterHelper
{

    public static SALData.SALCommandDataWriter narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALCommandDataWriter) {
            return (SALData.SALCommandDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALCommandDataWriter unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALCommandDataWriter) {
            return (SALData.SALCommandDataWriter)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
