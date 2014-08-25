package SALData;

public final class SALEvent {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_origin;
    public java.lang.String message = "";

    public SALEvent() {
    }

    public SALEvent(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_origin,
        java.lang.String _message)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_origin = _private_origin;
        message = _message;
    }

}
