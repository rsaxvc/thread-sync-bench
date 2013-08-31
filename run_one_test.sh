#!/usr/bin/env bash

tempfile=`mktemp`
timepath=`which time`
output=`$timepath -v --output=$tempfile ./bench $1 $2 $3`

echo "Temp file located at:" . $tempfile

vcs=`grep "Voluntary\ context\ switches" $tempfile`
ics=`grep "Involuntary\ context\ switches" $tempfile`

echo $vcs
echo $ics

###just some notes after here
#print $output

#thing="once upon a time"

#set -- $thing

#foo=$1
#shift
#bar=$@

#echo "foo: $foo"
#echo "bar: $bar"

rm $tempfile
