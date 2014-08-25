package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALCommandDataReaderViewHelper
{

    public static SALData.SALCommandDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALCommandDataReaderView) {
            return (SALData.SALCommandDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALCommandDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALCommandDataReaderView) {
            return (SALData.SALCommandDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
