Here is the instructions of how to use this repo in order to use engine, test against test cases, and play/test against a bot



For using main for more direct testing:
	command: make native
	directories and files: /src, /includes


For building the backend .so file,
	command: make
	directories and files: /src, /includes


For testing unit cases, we use the following:
	command: make test_solver
	directories and files: /tests

For the using the solve bot,
	command: ./cmd
	directories: /frontend
