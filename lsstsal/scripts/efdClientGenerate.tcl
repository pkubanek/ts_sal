proc efdClientGenerate { subsys } {
global SAL_WORK_DIR SQL_INSERT
   set fout [open $SAL_WORK_DIR/[set subsys]/cpp/src/efdClient_[set subsys].cpp w]
   puts $fout "
"
   puts $fout "
	sql::Connection *con;
	sql::PreparedStatement *prep_stmt;
	prep_stmt = con->prepareStatement($SQL_INSERT([set subsys]_[set topic]);"
        foreach i $SQL_PREPSTMT([set subsys]_[set topic]) {
            puts $fout "	$SQL_PREPSTMT([set subsys]_[set topic])"
        }
        puts $fout "	prep_stmt->execute();"
   close $fout
}


