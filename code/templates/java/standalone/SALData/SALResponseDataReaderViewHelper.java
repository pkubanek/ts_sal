package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALResponseDataReaderViewHelper
{

    public static SALData.SALResponseDataReaderView narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALResponseDataReaderView) {
            return (SALData.SALResponseDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALResponseDataReaderView unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALResponseDataReaderView) {
            return (SALData.SALResponseDataReaderView)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
