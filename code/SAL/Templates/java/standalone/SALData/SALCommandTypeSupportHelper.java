package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALCommandTypeSupportHelper
{

    public static SALData.SALCommandTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALCommandTypeSupport) {
            return (SALData.SALCommandTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALCommandTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALCommandTypeSupport) {
            return (SALData.SALCommandTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
