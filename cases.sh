echo hello > outfile > outfile2
	#creates 2 files, outfile (empty), outfile2 ("hello")

"echo hello"
	# bash: echo hello: command not found
		##----->>> 	NB, everything between single our double quotes is one 
		##			token.

'echo hello'
	# bash: echo hello: command not found

echo $home
	#empty line

echo $HOME
	# /Users/hoomen

echo hello $home hello
	# hello hello

echo hello$HOME
	# hello/Users/hoomen

echo $HOMEhello
	# empty line
