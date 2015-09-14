package SALData;

import org.opensplice.dds.dcps.Utilities;

public final class SALTopicTypeSupportHelper
{

    public static SALData.SALTopicTypeSupport narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALTopicTypeSupport) {
            return (SALData.SALTopicTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

    public static SALData.SALTopicTypeSupport unchecked_narrow(java.lang.Object obj)
    {
        if (obj == null) {
            return null;
        } else if (obj instanceof SALData.SALTopicTypeSupport) {
            return (SALData.SALTopicTypeSupport)obj;
        } else {
            throw Utilities.createException(Utilities.EXCEPTION_TYPE_BAD_PARAM, null);
        }
    }

}
