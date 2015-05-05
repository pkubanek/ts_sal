#!/usr/bin/perl -wT

use strict;
use CGI;
use CGI::Carp qw ( fatalsToBrowser );
use File::Basename;
$ENV{PATH} = "/bin";

$CGI::POST_MAX = 1024 * 50000;
my $safe_filename_characters = "a-zA-Z0-9_.-";
my $upload_dir = "/opt/upload";

my $query = new CGI;
my $filename = $query->param("uploadfile");

if ( !$filename )
{
 print $query->header ( );
 print "There was a problem uploading your XML (try a smaller file).";
 exit;
}


my ( $name, $path, $extension ) = fileparse ( $filename, '\..*' );
$filename = $name . $extension;
$filename =~ tr/ /_/;
$filename =~ s/[^$safe_filename_characters]//g;

if ( $filename =~ /^([$safe_filename_characters]+)$/ )
{
 $filename = $1;
}
else
{
 die "Filename contains invalid characters";
}

my $upload_filehandle = $query->upload("uploadfile");

open ( UPLOADFILE, ">$upload_dir/$filename" ) or die "$!";
binmode UPLOADFILE;

while ( <$upload_filehandle> )
{
 print UPLOADFILE;
}

close UPLOADFILE;
my $result = `/var/www/cgi-bin/rungenerator $filename`;

print $query->header ( );
print <<END_HTML;
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
 <head>
   <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<TITLE>SAL VM workbench XML upload</TITLE></HEAD>
<BODY BGCOLOR=White>
<IMG SRC="/LSST_logo.gif" ALIGN=CENTER>
<IMG SRC="/salg.gif" ALIGN=CENTER><P><HR><P>
<H1>XML upload processor</H1><P>

<P><HR><P>   <H2>Transfer complete.</H2>
    The uploaded file was <EM>$filename</EM>
 </head>
 <body>
   <p>Thanks for uploading your XML</p>
  Processing .....
  <hr>
  $result
  <hr>
 </body>
</html>
END_HTML
