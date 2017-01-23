#- Bin2Hex.pl
#- Copyright (c) 1995 by Dr. Herong Yang
#
($in, $out) = @ARGV;
die "Missing input file name.\n" unless $in;
die "Missing output file name.\n" unless $out;
$byteCount = 0;
open(IN, "< $in");
binmode(IN);
open(OUT, "> $out");
while (read(IN,$b0,1)) {
    $n = length($b0);
    $s = 2*$n;
    $p1end = 1; $p2end =1; $p3end =1;

    if (read(IN,$b1,1)) { $p1 = $b1; }
    else {$p1end = 0;}
    if (read(IN,$b2,1) && $p1end) { $p2 = $b2; }
    else {$p2end = 0;}
    if (read(IN,$b3,1) && $p2end) { $p3 = $b3; }
    else {$p3end = 0;}

    print (OUT $byteCount);
    print (OUT " => X\"");
    if ($p3end) {print (OUT unpack("H$s", $p3));}
    else  { print (OUT "00"); }
    if ($p2end) {print (OUT unpack("H$s", $p2));}
    else  { print (OUT "00"); }
    if ($p1end) {print (OUT unpack("H$s", $p1));}
    else  { print (OUT "00"); }
    print (OUT unpack("H$s", $b0), "\",\n");
    $byteCount += $n;
}
close(IN);
close(OUT);
exit;
