#!/usr/bin/perl

#
# convert an Oracle Calendar export into an ICS file with meeting reminders.
#
# usage: ./parse.pl < oracle_export.ics > /path/to/public_html/calendar.ics
#
#        ./parse.pl --config-file=/path/to/oracle_authn_params \
#                   /path/to/public_html/calendar.ics
# 
#        see usage() for details
#
# The Oracle Calendar SDK can output ICS formatted events, but this comes
# with a few caveats: 
#
# 1. the output is MIME encoded
# 2. iCal doesn't recognize the alarm triggers
#
# This script fixes those issues. By default, all meetings sound an 
# audible alert at time-minute-five minutes; day-events have their 
# alarms removed. To repress alarms all, set the CONVERT_ALARMS
# constant to 0; to keep alarms but change their behavior, change 
# the ACTION, TRIGGER and ATTACH constants.
#
#
# $Author$
# $Revision$
# $Date$
#


# convert alarms (1) or remove them (0)
use constant CONVERT_ALARMS  => 1;

# alarm type; AUDIO, DISPLAY
use constant ACTION  => "ACTION:AUDIO";

# alarm time; -PT5M is time-minus-five-minutes
use constant TRIGGER => "TRIGGER:-PT5M";

# alarm value; only used when there is AUDIO to play
use constant ATTACH  => "ATTACH;VALUE=URI:Basso";

# default start date, in days - now-less-14-days
use constant DATE_BEGIN => 14;

# default end date, in days - now-plus-31-days
use constant DATE_END => 31;

# seconds per day
use constant SECONDS_PER_DAY => 60 * 60 * 24;

# if fetching fails, how many times to retry?
use constant FETCH_RETRY => 3;

# where to store temp files
use constant TMP_DIR => '/tmp';


# --
# -- NOTHING TO CONFIGURE BELOW
# --



use MIME::Parser;
use Getopt::Long;
use strict;

main();

sub main 
{
	# name of config file
	my $filename;
	
	# MIME-encoded content from Oracle
	my $message = "";

	
	my $result = GetOptions("config-file:s" => \$filename); 
	if ($filename) {

		$message = exec_ocal($filename);

	} else {
		while (<>) { 
			$message .= "$_"; 
		}

	}
	
	# must execute the MIME conversion from where its parser
	# writes the tmp file. really, what's the point of setting
	# tmp_dir param if we have to chdir to that directory? 
	# really, the MIME::Parser devs kill me. 
	chdir TMP_DIR;

	# clean up wrapped lines and CRs
	$message =~ s/\n //g;
	$message =~ s/\r//g;

	print convert_alarms(parse_raw($message)->parts(0));

}



# --

#
# exec_ocal
# run the Oracle Calendar export utility and collect
# its output. the Oracle shared libraries some times 
# explode (segfault) on certain date ranges, which 
# means, of course, that nothing is returned and stored
# in $message. to combat this, if message is empty, 
# the date range is shifted forward one day at a time, 
# up to FETCH_RETRY times, to try to get a working 
# export. 
sub exec_ocal {
	my ($filename) = @_; 

	my $message = ""; 

	for (0..FETCH_RETRY) {	
		my $params = read_config($filename, $_); 
	
		my $command = <<EOT;
$params->{'ocal-export'} \\
	--hostname '$params->{'hostname'}' \\
	--username '$params->{'username'}' \\
	--password '$params->{'password'}' \\
	--begin '$params->{'begin'}' \\
	--end '$params->{'end'}'
EOT
		
		# must exec the exporter from its directory in order
		# to find its shared libs. god, the Oracle devs kill me.
		chdir $params->{'bundle-path'};
		$message = `$command`;
		last if $message; 
	}

	return $message; 
}



# --

#
# parse_raw
# parse the given MIME-encoded string
#
# arguments: 
#     $message - a MIME-encoded string with embedded newlines
#
# return: 
#     $entity - a MIME::Entity
#
sub parse_raw {
	my $message = shift; 
	
	my $parser = new MIME::Parser();
	$parser->tmp_dir(TMP_DIR); 
	my $entity = $parser->parse_data($message) or die "parse failed!";
	
	return $entity;
}



# --

#
# convert_alarms
# replaced embedded alarms with time-minus-five-minute
# alarms because the Oracle alarms format isn't 
# compatible with what Apple's iCal expects.  
#
# arugments: 
#     $entity - a MIME::Entity
#
# return
#     $text - $entity converted to a string
#
sub convert_alarms {
	my $entity = shift;
		
	my $in_alarm = 0; 
	my $has_alarm = 0;

	if (! $entity) {
		die("parse failed!"); 
	}


	my $text = ""; 
	if (my $io = $entity->open("r")) {
		while (defined($_ = $io->getline)) {
			if ($_ =~ /END:VALARM/) { 
				$in_alarm = 0;
				next;
			}
			next if $in_alarm; 
			if ($_ =~ /BEGIN:VALARM/) {
				$in_alarm = 1; 
				$has_alarm = 1;
				next;
			}
			
			if (CONVERT_ALARMS && $has_alarm && $_ =~ /END:VEVENT/) {
				$text .= "BEGIN:VALARM\n";
				$text .= ACTION  . "\n";
				$text .= TRIGGER . "\n";
				$text .= ATTACH  . "\n";
				$text .= "END:VALARM\n";
				
				# reset the event-has-alarm flag
				$has_alarm = 0; 
			}

			$text .= $_; 
		}
		$io->close;
	}

	# zap temp files created by MIME parsing
	$entity->purge;

	return $text;
}



# --

#
# read_config
# read the config file, returning the params
#
# arguments 
#     $filename - name of file to read from
#     $day_shift - days to shift default timestamp by
#
# return
#     \%params - key/value params, as read from config file
#
sub read_config {
	my ($filename, $day_shift) = @_; 

	if (! defined $day_shift) {
		$day_shift = 0; 
	}

	my $params;

	my $fh = IO::File->new($filename, "r");
	if (defined $fh) {
		while (<$fh>) {
			chomp;
			my ($key, $value) = ($_ =~ /([^\s=]*)\s*=\s*(.*)/); 
			my $key = $1;
			my $value = $2;
			$params->{$key} = $value; 		
		}
	
		$fh->close;
	}
	
	if (! $params->{'begin'} ) {
		my $date_begin = time() - (DATE_BEGIN * SECONDS_PER_DAY) + ($day_shift * SECONDS_PER_DAY);
		$params->{'begin'} = datestamp($date_begin); 
	}

	if (! $params->{'end'} ) {
		my $date_end = time() + (DATE_END * SECONDS_PER_DAY) + ($day_shift * SECONDS_PER_DAY);
		$params->{'end'} = datestamp($date_end);
	}

	die("missing required parameters") unless (
	       $params->{'ocal-export'}
		&& $params->{'bundle-path'}
		&& $params->{'hostname'}
		&& $params->{'username'}
		&& $params->{'password'}
		&& $params->{'begin'}
		&& $params->{'end'}
		); 
	
	
	return $params;

}



# --

#
# timestamp
# convert seconds-since-unix-epoch to a YYYYMMDD timestamp
#
# arguments
#     $seconds - number of seconds since Jan 1, 1970
#
# return
#     YYYYMMDD formatted datestamp
#
sub datestamp {
	my $seconds = shift;

	my $stamp = ""; 
	my @list = localtime $seconds;
	
	# fix the year	
	$list[5] += 1900;
	
	# fix the month, and convert to MM
	$list[4] += 1;
	$list[4] = ($list[4] < 10 ? "0$list[4]" : "$list[4]");

	# convert the day to DD
	$list[3] = ($list[3] < 10 ? "0$list[3]" : "$list[3]");
	
	return $list[5] . $list[4] . $list[3];
}


# --

#
# usage
# show how to use this script, then EXIT
#
sub usage {
	print <<EOT;

NAME
    $0 - transform MIME-wrapped Oracle Calendar export into a .ics file

SYNOPSIS
    $0 < oracle_export.ics > \$HOME/Sites/ocal.ics
    - or -
    $0 --config-file=/path/to/configfile > \$HOME/Sites/ocal.ics

DESCRIPTION

This script transforms the MIME-encoded data provided by Oracle 
Calendar into a regular .ics file suitable for importing/subscribing
with a tool like Apple's iCal or Google Calendar. Alarms on meetings
are converted to audible alerts at time-minus-five-minutes; alarms 
on day-events are removed. 

This script can be used in two ways: 

1. Data provided to STDIN is processed and printed to STDOUT. 

2. Given a config-file, this script can call an Oracle Calendar 
   export tool, collect and process its output and print the 
   results to STDOUT. The config file has the following format:
   
     ocal-export = /path/to/ocal_exporter
     bundle-path = /path/containing/OracleCalendarSDK.bundle
     hostname = ocs.host.edu
     username = ?/S=Wheelock/G=Eleazer/
     password = secretW0rds
     begin = 20080229
     end = 20080331
   
   The parameters 'begin' and 'end' are optional; if not omitted
   they will calculated automatically based on the DATE_BEGIN 
   and DATE_END constants. This makes it trivial to use this 
   script in a cronjob that publishes a current calendar, e.g.
   
   15 8-18 * * 1-5 $0 --config-file /path/to/ocal_config > \$HOME/Sites/oracle_calendar.ics

BUGS


EOT
	exit;

}
