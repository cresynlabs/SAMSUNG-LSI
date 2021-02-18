#!/usr/bin/perl

$FW_VERSION             = 0x00000000;

$inputfile = "./Drivers/Drivers/system.h";

$pDate = 0;
$pTime = 0;

$VESION_DEV_file = "./Drivers/Drivers/system.h";

@months = qw( Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec );

my ($sec, $min, $hour, $mday, $mon, $year) = localtime;
printf("%4s %02d %04d %02d:%02d:%02d\r\n", $months[$mon], $mday, $year+1900, $hour, $min, $sec);
$Datebuffer = sprintf("#define BuildDate\t\"%3s %02d %04d \"", $months[$mon], $mday, $year+1900);
$Timebuffer = sprintf("#define BuildTime\t\"%02d:%02d:%02d\"", $hour, $min, $sec);

#   $test = fnVersionRead($VESION_DEV_file);
$FW_VERSION = fnVersionRead($VESION_DEV_file);

printf( " SW_VERSION 0x%08X\n", $FW_VERSION);

fnWriteBuildTime($VESION_DEV_file);


# ----------------------------------------------------------------------
# For Get version
# ----------------------------------------------------------------------
# $_[0] = $Versionfile
sub fnVersionRead {

    my $Versionfile = $_[0];

    #my $line_string;

    my $Search_Minor_Ver = "FW_MINOR_VERSION";
    my $Search_Major_Ver = "FW_MAJOR_VERSION";

    my $Minor_String;
    my $Major_String;

    my $Version_String;
    my $Version_Info;

    open (TEXT, "<", $Versionfile) or die "Not able to open the $Versionfile file\n";

    while(<TEXT>){
        $line_string = $_;
            if( $line_string =~ /$Search_Minor_Ver/ )
            {
                #printf("%s\n",$line_string);
                s/.*0x//gi;
                s/\r\n//gi;
                s/\r//gi;
                $Minor_String = $_;
                #printf("%s\n",$Minor_String);
            }
            if( $line_string =~ /$Search_Major_Ver/ )
            {
                #printf("%s\n",$line_string);
                s/.*0x//gi;
                s/\r\n//gi;
                s/\r//gi;
                $Major_String = $_;
                #printf("%s\n",$Major_String);
            }
    }

    close (TEXT) or die "Not able to close the file: $Versionfile \n";

    $Version_Info = "";
    $Version_Info = (hex($Major_String)<<16) + (hex($Minor_String));

    return $Version_Info;
}


# ----------------------------------------------------------------------
# For write Build Time
# ----------------------------------------------------------------------
# $_[0] = $Versionfile
sub fnWriteBuildTime {

    my $Versionfile = $_[0];

    my $Search_Date = "#define BuildDate";
    my $Search_Time = "#define BuildTime";

    open (TEXT, "+<", $Versionfile) or die "Not able to open the $Versionfile file\n";

    while(<TEXT>){
        $line_string = $_;
            if( $line_string =~ /$Search_Date/ )
            {
                #printf("%s\n",$line_string);
                $pDate = tell TEXT;
                #printf("%d \r\n", $pDate);
                seek TEXT, $pDate - 34, 0;
				printf(TEXT $Datebuffer);
            }
            if( $line_string =~ /$Search_Time/ )
            {
                #printf("%s\n",$line_string);
                $pTime = tell TEXT;
                #printf("%d \r\n", $pTime);
                seek TEXT, $pTime - 30, 0;
				printf(TEXT $Timebuffer)
            }
    }

    close (TEXT) or die "Not able to close the file: $Versionfile \n";
}