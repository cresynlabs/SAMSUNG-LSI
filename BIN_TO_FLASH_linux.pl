#!/usr/bin/perl
use File::Copy qw(copy);

$FW_VERSION             = 0x00000000;
$FLASH_CODE_RESERVED    = 0x00000000;
$FLASH_CODE_SIZE        = 0x00000000;
$FLASH_CODE_CHECK_SUM   = 0x00000000;

$TN_VER = "";

$CHECK_SUM = 0x00;
$CHECK_SUM_START = 0x1000;

$bNUM = 0;

$buffer = "";
$chrBuf = "";
$inputfile = $ARGV[0];
#$tempfile = "tempfile.bin";

$fCnt = 0;
$fNum = 1;
$fMod = 0;

$bCnt = 0;

$bModVal = 0;
$bMCnt = 0;

@HEADER_ARY = ();

$Header_Infile = 0;
$Header_Outfile = 0;
$Header_Size = 0;

$Header_Outfile = "./Output/Bin/S2MUA01_FLASH.h";
$bufFile = "./Output/Bin/bufFile.bin";

$VESION_DEV_file = "./../../../Drivers/Drivers/System.h";
#$VESION_DEV_file2 = "./../../../Drivers/UTCom/uart_cmd.h";


#   $test = fnVersionRead($VESION_DEV_file);
$FW_VERSION = fnVersionRead($VESION_DEV_file);
#$TN_VER = fnVersionRead2($VESION_DEV_file2);

printf( " SW_VERSION 0x%08X\n", $FW_VERSION);
#printf( " TN_VERSION %s\n", $TN_VER);

$file_len = fnFileSize($inputfile);
print "BIN FILE size : $file_len \n";
printf ("BIN FILE size : 0x%08x\r\n", $file_len);


#if (-d "SplitBin") {
#    print "ReMove SplitBin \n";
#    rmdir  "./SplitBin" or die "Remove Dir Error \n";
     #system "rm -rf SplitBin" ;
#    unlink <SplitBin/*>;
#    rmdir  "./SplitBin" or die "Remove Dir Error \n";
#}

#mkdir "SplitBin" or die "Make Dir Error \n";

$FLASH_CODE_SIZE = $file_len;

$fMod = $file_len % 16;
if( $fMod > 0 ) {
    $FLASH_CODE_SIZE = $FLASH_CODE_SIZE + (16 - $fMod);
}

#   @TestAry = (0x77,0x66,0x55,0x44,0x33);
#   my $TestCRCCode = 0;
#   $TestCRCCode = fn_GenCRCCODE(\@TestAry );
#   printf("TX packet after decode= 0x%X\n",$TestCRCCode);

#$fcnt = $fcnt + 1;
print "BIN FILE Number : $fNum \n";
print "BIN FILE Mod : $fMod \n";

open (INFILE, "<", $inputfile) or die "Not 3 able to open the file for writing. \n";

binmode (INFILE);


$START_ADDR = 0x00000000;
$END_ADDR = $START_ADDR + $file_len;
#   for ( $fCnt = 1; $fCnt < 2 ; $fCnt++)
for ( $fCnt = 1; $fCnt < ($fNum + 1) ; $fCnt++)
{
    $CHECK_SUM = 0x00;

    #   $bufFile = "./SplitBin/bufFile.bin";
    # print "$bufFile\n";
    open (OUTFILE, ">", $bufFile) or die "Not able to open the $bufFile for writing. \n";
    binmode (OUTFILE);

    @HEADER_ARY = fnHeaderInit($FW_VERSION, $FLASH_CODE_RESERVED, $file_len);

    for($bCnt = 0 ; $bCnt < $file_len ; $bCnt++)
    {
        $brk = read (INFILE, $buffer, 1);
        if($brk == 0)
        {
            last;
        }
        $chrBuf = ord($buffer);

        print( OUTFILE chr($chrBuf) );
        if($bCnt > ($CHECK_SUM_START - 1))
        {
            $CHECK_SUM = fn_CheckSum($CHECK_SUM, $chrBuf);
        }

    }

    printf("CheckSum = 0x%X\n",$CHECK_SUM);
    $FLASH_CODE_CHECK_SUM = fn_GetCheckSum($CHECK_SUM);
    printf("FLASH_CODE_CHECK_SUM = 0x%08X\n",$FLASH_CODE_CHECK_SUM);

    close (OUTFILE) or die "Not able to close the file: $outFile \n";

}

close (INFILE) or die "Not able to close the file: $inputfile \n";



$Header_Infile = $bufFile;


$Header_Size = fnFileSize($Header_Infile);
print "$Header_Infile Length : $Header_Size \n";

open (INFILE, "<", $Header_Infile) or die "Not 3 able to open the file for writing. \n";
binmode (INFILE);

open (OUTFILE, ">", $Header_Outfile) or die "Not able to open the $bufFile for writing. \n";

    printf( OUTFILE  "uint8_t MUA01_FW[] =\n" );
    printf( OUTFILE  "{\n" );
    $fCnt = 0;
    for($bCnt = 0 ; $bCnt < $Header_Size ; $bCnt++)
    {

        $brk = read (INFILE, $buffer, 1);
        if($brk == 0)
        {
            print( OUTFILE "\n" );
            last;
        }
        $chrBuf = ord($buffer);

        if($fCnt == 0)
        {
        }
        else
        {
            if($fCnt >= 12)
            {
                print( OUTFILE ",\n" );
                $fCnt = 0;
            }
            else
            {
                print( OUTFILE ", " );
            }
        }

        printf( OUTFILE  "0x%02X",$chrBuf);

        $fCnt = $fCnt + 1;
     }
    printf( OUTFILE  "\n};\n" );

close (OUTFILE) or die "Not able to close the file: $Header_Outfile \n";

close (INFILE) or die "Not able to close the file: $Header_Infile \n";

my $newfilename = join ".", $TN_VER, "bin";

#copy $inputfile, $newfilename;



# ----------------------------------------------------------------------
# For Generate Header Data
# ----------------------------------------------------------------------
# $_[0] = $FW_VERSION
# $_[1] = $START_ADDR
# $_[2] = $END_ADDR
# $_[3] = $CRC_INIT
sub fnHeaderInit {

    my $fw_ver = $_[0];
    my $st_adr = $_[1];
    my $end_adr = $_[2];
    #   my $crcVal = $_[3];

    my @MyAry = ();

    $MyAry[0]  = ($fw_ver) & 0xFF;
    $MyAry[1]  = ($fw_ver>>8) & 0xFF;
    $MyAry[2]  = ($fw_ver>>16) & 0xFF;
    $MyAry[3]  = ($fw_ver>>24) & 0xFF;
    $MyAry[4]  = ($st_adr) & 0xFF;
    $MyAry[5]  = ($st_adr>>8) & 0xFF;
    $MyAry[6]  = ($st_adr>>16) & 0xFF;
    $MyAry[7]  = ($st_adr>>24) & 0xFF;
    $MyAry[8]  = ($end_adr) & 0xFF;
    $MyAry[9]  = ($end_adr>>8) & 0xFF;
    $MyAry[10] = ($end_adr>>16) & 0xFF;
    $MyAry[11] = ($end_adr>>24) & 0xFF;
    #   $MyAry[12] = ($crcVal) & 0xFF;
    #   $MyAry[13] = ($crcVal>>8) & 0xFF;
    #   $MyAry[14] = ($crcVal>>16) & 0xFF;
    #   $MyAry[15] = ($crcVal>>24) & 0xFF;

    #   printf(" FW Version = 0x%8X\n",$fw_ver);
    #   printf(" Start Addr = 0x%8X\n",$st_adr);
    #   printf(" End Addr = 0x%8X\n",$end_adr);
    #   printf(" CRC Data = 0x%8X\n",$crcVal);

    return @MyAry;

}


# ----------------------------------------------------------------------
# For Get file size(length)
# ----------------------------------------------------------------------
# $_[0] = $Infile
sub fnFileSize {

    my $Infile = $_[0];


    open (INFILE, "<", $Infile) or die "Not 1 able to open the file for writing. \n";

    $file_size = 0;

    binmode (INFILE);

    while ( (read (INFILE, $buffer, 1)) != 0 ) {
        $file_size = $file_size + 1;
    }

    #print "BIN FILE size : $file_size \n";

    close (INFILE) or die "Not able to close the file: $inputfile \n";

    return $file_size;
}


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
    #printf("%X\n",$Version_String);

    return $Version_Info;
}
# ----------------------------------------------------------------------
# For  Get TN version
# ----------------------------------------------------------------------
sub fnVersionRead2 {

    my $Versionfile = $_[0];

    #my $line_string;

    my $Search_Minor_Ver = "FW_TN_VERSION";
    my $Version_String;

    my $where ;

    open (TEXT, "<", $Versionfile) or die "Not able to open the $Versionfile file\n";

    while(<TEXT>){
        $line_string = $_;
            if( $line_string =~ /$Search_Minor_Ver/ )
            {
		$where = index($line_string,"\"");
		$Version_String = substr($line_string, $where+1,14);


            }
    }

    close (TEXT) or die "Not able to close the file: $Versionfile \n";

    return $Version_String;
}

# ----------------------------------------------------------------------
# For Generate CHECK_SUM
# ----------------------------------------------------------------------
# $_[0] : CHECK_SUM
# $_[1] : Data
sub fn_CheckSum {

    my $RetVal = 0x00;

    $RetVal = ($_[0] + $_[1]) & 0xFF;

    return $RetVal;
}

# $_[0] : CHECK_SUM
sub fn_GetCheckSum {

    my $RetVal = 0x00;

    $RetVal = ((~$_[0]) + 1) & 0xFF;

    return $RetVal;
}


# ----------------------------------------------------------------------
# For Generate CRC Code
# ----------------------------------------------------------------------
# $_[0] : CRC_INIT
# $_[1] : Data
# $_[2] : Data_Length
sub fn_crcBits {

    # spec 04C1 1DB7h
    my $poly = 0x04C11DB6;
    my $newbit = 0;
    my $newword = 0;
    my $rl_crc = 0;

    my $i = 0;

    #  printf("Init = 0x%8X    Data = 0x%X  Len = %d\n",$_[0] ,$_[1] ,$_[2]);

    for( $i=0 ; $i<$_[2] ; $i++)
    {
        $newbit = (($_[0]>>31) ^ (($_[1]>>$i)&1)) & 1;
        if($newbit) {
            $newword=$poly;
        } else {
            $newword=0;
        }
        $rl_crc = ($_[0]<<1) | $newbit;
        $_[0] = ($rl_crc ^ $newword) & (0xFFFFFFFF);

        #  printf("%2d newbit=%d, x>>i=0x%x, crc=0x%x\n\r",$i,$newbit,($_[1]>>$i),$_[0]);
    }

}

# $_[0] : CRC_INIT
sub fn_crcWrap {

    my $ret = 0;
    my $i = 0;
    my $j = 0;
    my $bit = 0;

    $_[0] = (~($_[0])) & 0xFFFFFFFF;

    for($i = 0; $i < 32 ; $i++)
    {
        $j = 31-$i;
        $bit = ($_[0] >> $i) & 1;
        $ret = $ret | ($bit<<$j);
    }

    return $ret;
}

# $_[0] : Array Argument
sub fn_GenCRCCODE {

    my $ret = 0;

#   $crc_mon = sprintf("%08X", $crc);
#   print "CRC Seed = $crc_mon\n";

    my @MyAry = @{$_[0]};
    my $MyArySize = ($#MyAry + 1);

    my $crc = 0xffffffff;
    my $lenCnt = 0;

    # print "@MyAry\n";
    # print "$MyAry[0] $#MyAry \n";

    #   printf("CRC = 0x%8X\n",$crc);
    for($lenCnt = 0;$lenCnt < $MyArySize;$lenCnt++)
    {
        #   printf(" cnt %d    0x%8X    0x%X\n",$lenCnt,$crc, $TestAry[$lenCnt]);
        #   printf(" TestAry = %X\n",$TestAry[0]);
        fn_crcBits($crc, $TestAry[$lenCnt], 8);
    }
    $ret = fn_crcWrap($crc);

    #   printf("TX packet after decode= 0x%X\n",$ret);
    return $ret;
}
