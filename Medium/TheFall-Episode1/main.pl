use strict;
use warnings;
#use diagnostics;
use 5.20.1;

select(STDOUT); $| = 1; # DO NOT REMOVE

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

my @types;
$types[1]={LEFT=>'DOWN', TOP=>'DOWN', RIGHT=>'DOWN'};
$types[2]={LEFT=>'RIGHT', RIGHT=>'LEFT'};
$types[3]={TOP=>'DOWN'};
$types[4]={TOP=>'LEFT', RIGHT=>'DOWN'};
$types[5]={LEFT=>'DOWN', TOP=>'RIGHT'};
$types[6]={LEFT=>'RIGHT', RIGHT=>'LEFT'};
$types[7]={TOP=>'DOWN', RIGHT=>'DOWN'};
$types[8]={LEFT=>'DOWN', RIGHT=>'DOWN'};
$types[9]={LEFT=>'DOWN', TOP=>'DOWN'};
$types[10]={TOP=>'LEFT'};
$types[11]={TOP=>'RIGHT'};
$types[12]={RIGHT => 'DOWN'};
$types[13]={LEFT => 'DOWN'};

my $tokens;

# w: number of columns.
# h: number of rows.
chomp($tokens=<STDIN>);
my ($w, $h) = split(/ /,$tokens);
my @map;
for my $i (0..$h-1) {
    chomp(my $lne = <STDIN>); # represents a line in the grid and contains W integers. Each integer represents one room of a given type.
    my @line = split(/ /, $lne);
    push @map, \@line;
}
chomp(my $ex = <STDIN>); # the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
# game loop
while (1) {
    chomp($tokens=<STDIN>);
    my ($yi, $xi, $pos) = split(/ /,$tokens);
    my ($x, $y) = ($xi, $yi);
    print STDERR "$xi $yi $pos\n";
    my $type = $map[$xi]->[$yi];
    my $response = $types[$type]->{$pos};
    print STDERR $response;
    if ($response eq 'DOWN'){
        $x++;
    } elsif($response eq 'LEFT' ) {
        $y--;
    } elsif ($response eq 'RIGHT') {
        $y++;
    }
    # Write an action using print
    # To debug: print STDERR "Debug messages...\n";

    print "$y $x\n"; # One line containing the X Y coordinates of the room in which you believe Indy will be on the next turn.
}