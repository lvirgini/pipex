if [$# != 3]; then
	echo "utilisation du tester :\n il faut 3 arguments:\n ./test.sh infile cmd1 cmd2\n"
	exit
fi

./pipex $1 $2 $3 outfile;
< $1 $2 | $3 > outfile2;

diff outfile