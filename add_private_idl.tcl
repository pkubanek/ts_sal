

proc add_private_idl { fidl {spc "   "} } {
  puts $fidl "[set spc]string<32> private_revCode; //private
[set spc]double private_sndStamp;    //private
[set spc]double private_rcvStamp;    //private
[set spc]long private_seqNum;        //private
[set spc]long private_origin;        //private
[set spc]long private_host;          //private"
}

