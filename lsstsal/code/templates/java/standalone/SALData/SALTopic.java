package SALData;

public final class SALTopic {

    public java.lang.String private_revCode = "";
    public double private_sndStamp;
    public double private_rcvStamp;
    public int private_seqNum;
    public int private_origin;
    public int private_host;
    public short test_i16;
    public int test_l32;
    public long test_i64;
    public short test_u16;
    public int test_u32;
    public long test_u64;
    public float test_r32;
    public double test_r64;
    public char test_u8;
    public boolean test_bool;
    public short[] test_i16_array = new short[16];
    public int[] test_l32_array = new int[16];
    public long[] test_i64_array = new long[16];
    public short[] test_u16_array = new short[16];
    public int[] test_u32_array = new int[16];
    public long[] test_u64_array = new long[16];
    public float[] test_r32_array = new float[16];
    public double[] test_r64_array = new double[16];
    public char[] test_u8_array = new char[16];
    public boolean[] test_bool_array = new boolean[16];
    public java.lang.String test_string = "";
    public java.lang.String test_string_option = "";
    public java.lang.String test_large_string = "";

    public SALTopic() {
    }

    public SALTopic(
        java.lang.String _private_revCode,
        double _private_sndStamp,
        double _private_rcvStamp,
        int _private_seqNum,
        int _private_origin,
        int _private_host,
        short _test_i16,
        int _test_l32,
        long _test_i64,
        short _test_u16,
        int _test_u32,
        long _test_u64,
        float _test_r32,
        double _test_r64,
        char _test_u8,
        boolean _test_bool,
        short[] _test_i16_array,
        int[] _test_l32_array,
        long[] _test_i64_array,
        short[] _test_u16_array,
        int[] _test_u32_array,
        long[] _test_u64_array,
        float[] _test_r32_array,
        double[] _test_r64_array,
        char[] _test_u8_array,
        boolean[] _test_bool_array,
        java.lang.String _test_string,
        java.lang.String _test_string_option,
        java.lang.String _test_large_string)
    {
        private_revCode = _private_revCode;
        private_sndStamp = _private_sndStamp;
        private_rcvStamp = _private_rcvStamp;
        private_seqNum = _private_seqNum;
        private_origin = _private_origin;
        private_host = _private_host;
        test_i16 = _test_i16;
        test_l32 = _test_l32;
        test_i64 = _test_i64;
        test_u16 = _test_u16;
        test_u32 = _test_u32;
        test_u64 = _test_u64;
        test_r32 = _test_r32;
        test_r64 = _test_r64;
        test_u8 = _test_u8;
        test_bool = _test_bool;
        test_i16_array = _test_i16_array;
        test_l32_array = _test_l32_array;
        test_i64_array = _test_i64_array;
        test_u16_array = _test_u16_array;
        test_u32_array = _test_u32_array;
        test_u64_array = _test_u64_array;
        test_r32_array = _test_r32_array;
        test_r64_array = _test_r64_array;
        test_u8_array = _test_u8_array;
        test_bool_array = _test_bool_array;
        test_string = _test_string;
        test_string_option = _test_string_option;
        test_large_string = _test_large_string;
    }

}
