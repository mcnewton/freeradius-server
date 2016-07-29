#! /usr/bin/perl

open IN, "<xlats.md.in";

$flag = 0;

while ($l=<IN>) {

	unless ($flag or $l =~ /^~~/) {
		print $l;
		next;
	}

	$flag = 1;
	chomp $l;

	if ($l =~ /^"?([^"\s]+)"?\s+"?([^"\s]+)"?/) {
		($mod, $name) = ($1, $2);

		$inst = 0;

		if ($name =~ /^inst(?:ance)?->/) {
			$inst = 1;
			if ($mod =~ /^rlm_(.*)$/) {
				$name = "$1";
			} else {
				$name = "$mod *";
			}
		}

		push @list, [$mod, $name, $inst];

	} else {
		print "$l\n";
	}
}


foreach $r (sort {$$a[1] cmp $$b[1]} @list) {
	($mod, $name, $inst) = @$r;
	
	$istar = " *" if $inst;
	print "### $name$istar\n\n";
	print "Provided by module `$mod`\n\n";
	print "-desc-\n\n";
	print "Example: \"%{$name:...}\"\n";
	print "Output: \"\"\n";
	print "\n\n";
}

