use strict;
use warnings;
#use diagnostics;
use 5.20.1;

select(STDOUT); $| = 1; # DO NOT REMOVE

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

my $tokens;

# nb_floors: number of floors
# width: width of the area
# nb_rounds: maximum number of rounds
# exit_floor: floor on which the exit is found
# exit_pos: position of the exit on its floor
# nb_total_clones: number of generated clones
# nb_additional_elevators: ignore (always zero)
# nb_elevators: number of elevators
my @floors;
my $exit;
chomp($tokens=<STDIN>);
my ($nb_floors, $width, $nb_rounds, $exit_floor, $exit_pos, $nb_total_clones, $nb_additional_elevators, $nb_elevators) = split(/ /,$tokens);
for my $i (0..$nb_elevators-1) {
    # elevator_floor: floor on which this elevator is found
    # elevator_pos: position of the elevator on its floor
    chomp($tokens=<STDIN>);
    my ($elevator_floor, $elevator_pos) = split(/ /,$tokens);
    my $enter = $i == 0? undef : $floors[$elevator_floor-1]->{exit};
    my $exit = $i == $exit_floor ? $exit_pos : $elevator_pos;
    $floors[$elevator_floor] = {
        enter => $enter,
        ext => $exit,
        do_nothing => 0,
    }
}
my $temp = {
        ext => $exit_pos,
        do_nothing => 0
    };
push @floors, $temp;

for my $i (0..$#floors){
print STDERR "floor:$i elew:$floors[$i]->{ext}\n";
}
# game loop
while (1) {
    # clone_floor: floor of the leading clone
    # clone_pos: position of the leading clone on its floor
    # direction: direction of the leading clone: LEFT or RIGHT
    chomp($tokens=<STDIN>);
    my ($clone_floor, $clone_pos, $clone_dir) = split(/ /,$tokens);
    print STDERR "clone_floor: $clone_floor\n";
    if ($clone_floor == -1){
        print "WAIT\n";
    }
    elsif ( $floors[$clone_floor]->{do_nothing} ) {
        print "WAIT\n";
    } else {
        my $exit_dir = ($floors[$clone_floor]->{ext} - $clone_pos) < 0 ? 'LEFT' : 'RIGHT';
        if ($exit_dir eq $clone_dir) {
            print "WAIT\n";
            $floors[$clone_floor]->{do_nothing} = 1;
        }
        else{
            print "BLOCK\n";
            $floors[$clone_floor]->{do_nothing} = 1;
        }
    }
    # Write an action using print
    # To debug: print STDERR "Debug messages...\n";

    #print "WAIT\n"; # action: WAIT or BLOCK
}