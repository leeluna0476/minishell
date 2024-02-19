# Pipeline
```
cmd1 | cmd2 | cmd3
```
![](./pics/example-18.jpg)

### Pseudocode
```
proc:
	open pipe1;
	fork();
	left:
		dup2(pipe1, STDOUT);
		open pipe2;
		fork();
		left:
			dup2(pipe2, STDOUT);
		fork();
		right:
			dup2(pipe2, STDIN);
	fork();
	right:
		dup2(pipe1, STDIN);
```
