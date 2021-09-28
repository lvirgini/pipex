if [ $# != 3 ]; then
	echo "utilisation du tester :\n il faut 3 arguments:\n ./test.sh infile cmd1 cmd2\n"
	exit
fi

rm outfile2 outfile

./pipex "$1" "$2" "$3" outfile 2> error

#bash -c "$2 < $1 '|' $3 > outfile2"
$($2 < $1 | $3 > outfile2)

diff outfile outfile2