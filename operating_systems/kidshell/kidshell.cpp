#include<iostream>
#include<cstring>
#include<sstream>
#include<iterator>
#include<vector>
#include<map>
#include<string>
#include<algorithm>

#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

using std::vector;
using std::map;
using std::string;
using std::pair;

static const int MAXDIR = 128;

extern char **environ;

static map<string, string> environment;


void add_environment(char const * new_env) {
	std::string env(new_env);
	string::size_type ind = env.find('=');
	if (ind == string::npos) {
		printf("Can't add %s: \"=\" not found.\n", env.c_str());
		return;
	}
	environment[env.substr(0, ind)] = env.substr(ind + 1); 
}

vector<char*> vector_c_str(vector<string> const &cur) {
	vector<char*> out;
	for (auto str : cur) {
		char *buff = new char[str.size() + 1];
		strcpy(buff, str.data());
		out.push_back(buff);
	}
	out.push_back(nullptr);
	return out;
}

vector<string> parse_arguments(string const &command) {
	std::istringstream iss(command);
	vector<string> tmp {std::istream_iterator<string>(iss), std::istream_iterator<string>()};
	return tmp;	
}

void change_directory(string dir) {
	if (chdir(dir.c_str()) != 0) {
		perror(dir.c_str());
		printf("Usage: man unset\n");
	}
}

void show_environment() {
	for (const auto& out :  environment) {
		printf("%s=%s\n", out.first.c_str(), out.second.c_str());
	}
}

vector<string> get_environment() {
	vector<string> out;
	std::transform(environment.begin(), environment.end(), std::back_inserter(out),
					[](const pair<string, string>& p) {
						return p.first + "=" + p.second;
					});
	return out;
}

void execute_command(char *_args[], char *_envp[]) {
	pid_t pid = fork();
	if (pid < 0) {
		perror("ERROR: can't create a child process.");
	} else if (pid == 0) {
		if (execve(_args[0], _args, _envp) == -1) {
			perror("ERROR: execution failed.");
			exit(-1);
		}
		exit(0);
	} else {
		int res;
		if (waitpid(pid, &res, 0) == -1) {
			perror("ERROR: waiting failed.");
		} else {
			printf("Return code: %d.\n", res);
		}
	}
}

void parse_command(string const &command) {
	vector<string> args = parse_arguments(command);
	std::cout << args[0] << "\n";
	if (args.size() == 2 && args[0] == "cd") {
		change_directory(args[1]);
	} else if (args[0] == "export") {
		if (args.size() == 1 || (args.size() == 2 && args[1] == "-p")) {
			show_environment();
		} else if (args.size() >= 2) {
			for (size_t i = 1; i < args.size(); ++i) {
				add_environment(args[i].c_str());
			}
		} else {
			perror("ERROR: can't parse input command.");		
			printf("Usage: man export\n");	
		}
	} else if (args[0] == "unset") {
		if (args.size() >= 2) {
			for (size_t i = 1; i < args.size(); ++i) {
				environment.erase(args[i]);
			}
		} else {
			perror("ERROR: can't parse input command.");
			printf("Usage: man unset\n");
		}
	} else {
		vector<char*> _args = vector_c_str(args);
		vector<char*> _envp = vector_c_str(get_environment());
		execute_command(_args.data(), _envp.data());
	}
}

int main(int argc, char *argv[]) {
	for (char ** new_env = environ; *new_env != nullptr; ++new_env) {
		add_environment(*new_env);	
	}
	while (true) {
		char dir[MAXDIR];
		if (getcwd(dir, MAXDIR) == NULL) {
			perror("ERROR: can't get current dirrectory.");
		} else {
			printf("%s:%s", getlogin(), dir);
		}

		printf("$");

		string command;
		std::getline(std::cin, command);
	        if (std::cin.eof() || command == "exit") {
			printf("Good bye...\n"); 
			break;
		}	

		parse_command(command);
	}
	return 0;
}