#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include <stdexcept>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include<sys/wait.h>

enum comparison_mark {NO, LOWER, EQUAL, GREATER};

using std::string;
using std::vector;
using std::queue;
using std::pair;

struct find_helper {
    string file_path;

    ino_t inum; 
    string name;
    nlink_t nlinks;
    string exec_path;
    off_t size;
    string error;

    bool inum_need            = false;
    bool name_need            = false;
    bool nlinks_need          = false;
    bool exec_need            = false;
    comparison_mark size_need = NO;
    bool is_error             = false;
};

void arg_error(find_helper &cur, string const &error, string const &flag = "") {
    cur.is_error = true;
    cur.error    = error + (flag.empty() ? flag : " (in flag " + flag + ")");
}

pair<size_t, string> str_to_int(string const& str) {
    size_t out           = 0;
    string error_message = "convert without error";
    
    try {
        return {std::stoul(str), error_message};
    } catch (const std::invalid_argument &e) {
        error_message = "Invalid value: is not a number";
        return {out, error_message};
    } catch (const std::out_of_range &e) {
        error_message = "Invalid value: is too big number";
        return {out, error_message};
    }

}

short set_number_value(find_helper &cur, pair<size_t, string> const &value, string const &field) {
    string error_message = value.second;
    // std::cout << "ERROR: " << error_message << "\n";
    if (error_message != "convert without error") {
        arg_error(cur, error_message, field);
        return -1;
    } else {
        size_t number_value = value.first;
        if (field == "-size") {
            cur.size = number_value;
        } else if (field == "-inum") {
            cur.inum = number_value;
        } else if (field == "-nlinks") {
            cur.nlinks = number_value;
        }
        return 0;
    }
}

find_helper parse_args(int argc, char *argv[]) {
    find_helper out;
    if (argc <= 1 || (argc - 2) % 2 == 1) {
        arg_error(out, "Incorrect value of arguments");
        return out;    
    }
    
    for (int i = 2; i < argc; i += 2) {
        string flag  = argv[i];
        string value = argv[i + 1];
        if (flag == "-inum") {
            out.inum_need = true;
        } else if (flag == "-name") {
            out.name_need = true;
            out.name = value;
            continue;
        } else if (flag == "-size") {
            if (value.length() <= 1) {
                arg_error(out, "Incorrect value: " + value, flag);
                return out;
            } else {
                switch (value[0]) {
                    case '-' :
                        out.size_need = LOWER;
                        break;
                    case '=' :
                        out.size_need = EQUAL;
                        break;
                    case '+' :
                        out.size_need = GREATER;
                        break;
                    default :
                        arg_error(out, "Incorrect value: " + value, flag);
                        return out;
                }
                value = value.substr(1);
            }
        } else if (flag == "-nlinks") {
            out.nlinks_need = true;
        } else if (flag == "-exec") {
            out.exec_need = true;
            out.exec_path = value;
            continue;
        } else {
            arg_error(out, "Unknown parameter: " + flag);
            return out;
        }

        if (set_number_value(out, str_to_int(value), flag) == -1) {
            return out;            
        }
    }

    out.file_path = argv[1];
    return out;
}

bool is_check(struct stat const &stat, find_helper &cur, string const &name) {
    bool out = true;
    if (cur.inum_need) {
        // std::cout << "DEBUG: cur.inum == " << cur.inum << "; st_ino == " << stat.st_ino << std::endl;  
        out &= stat.st_ino == cur.inum;
    }
    if (cur.name_need) {
        // std::cout << "DEBUG: cur.name == " << cur.name << "; name == " << name << std::endl;  
        out &= name == cur.name;
    }
    if (cur.nlinks_need) {
        // std::cout << "DEBUG: cur.nlinks == " << cur.nlinks << "; st_nlink == " << stat.st_nlink << std::endl;  
        out &= stat.st_nlink == cur.nlinks;
    }

    // std::cout << "DEBUG: cur.size == " << cur.size << "; st_size == " << stat.st_size << std::endl;  
    switch (cur.size_need) {
        case LOWER:
            out &= (stat.st_size < cur.size);
            break;
        case EQUAL:
            out &= (stat.st_size == cur.size);
            break;
        case GREATER:
            out &= (stat.st_size > cur.size);
            break;
        default:
            break;
    }
    return out;
}

void fill_queue(std::queue<std::pair<string, string>> &q, string absolute_path) {
    if (absolute_path.back() != '/') {
        absolute_path +='/';
    }
    //auto data = d.data();
    DIR* dir = opendir(absolute_path.data());
    if (dir == NULL) {
        string error_message = "Unable to access file " +  absolute_path;
        perror(error_message.data());
        return;
    }
    while (true) {
        dirent* next = readdir(dir);
        if (next == NULL) {
            break;
        }
        string name(next->d_name);
        if (name == "." || name == "..") {
            continue;
        }
        q.push({absolute_path + name, name});
    }
    if (closedir(dir) != 0) {
        perror("ERROR");
    }
}

vector<string> bfs(find_helper &cur) {
    vector<string> out;
    queue<pair<string, string>> q;
    q.push({cur.file_path, cur.file_path});
    struct stat stat;
    while (!q.empty()) {
        pair<string, string> q_cur = q.front(); q.pop();
        string absolute_path = q_cur.first;
        string relative_path = q_cur.second;

        //set stat
        if (lstat(absolute_path.data(), &stat) == -1) {
            string error_message = "Unable to access file " +  absolute_path;
            perror(error_message.data());
            continue;
        }
        
        //check stat by find_helper
        if (is_check(stat, cur, relative_path)) {
            out.push_back(absolute_path);
        }


        //if dir next bfs step
        if ((stat.st_mode & S_IFMT) == S_IFDIR) {
            fill_queue(q, absolute_path);
        }
    }
    return out;
}

void show_help() {
    printf("Find utility. Created by Dmitry Janchenkov\n\n");
    printf("Usage: find [path] [parameters]\n");
    printf("Description: finds list of files, which satisfy predicate\n");
    printf("Parameters :\n");
    printf("\t-size <[-=+]number>  set size in bytes lower [-], equal [=], greater [+] than <nubmer> \n");
    printf("\t-nlinks <number>     set <number> of links allowed\n");
    printf("\t-inum <number>       set <number> of inode\n");
    printf("\t-name <string>       set <name> of file\n");
    printf("\t-exec <path>         set <path> of executable, which will get output\n");
}


void execute(string const &exec_path, string const &arg) {
    pid_t pid = fork();
	if (pid < 0) {
		perror("ERROR: can't create a child process.");
	} else if (pid == 0) {
        char** c_args = new char*[3];
        c_args[0] = const_cast<char*>(exec_path.data());
        c_args[1] = const_cast<char*>(arg.data());
        c_args[2] = nullptr;
		if (execve(c_args[0], c_args, environ) == -1) {
            delete[] c_args;
			perror("ERROR: execution failed.");
			exit(EXIT_FAILURE);
		}
        delete[] c_args;        
		exit(EXIT_SUCCESS);
	} else {
		int res;
		if (waitpid(pid, &res, 0) == -1) {
			perror("ERROR: waiting failed.");
		} else {
			printf("Return code: %d.\n", res);
		}
	}
}

int main(int argc, char *argv[], char *envp[]) {
    find_helper helper = parse_args(argc, argv);
    // std::cout << helper.inum << std::endl << helper.is_error << std::endl;
    if (helper.is_error) {
        printf("ERROR: %s\n\n", helper.error.data());
        show_help();
        exit(EXIT_FAILURE);
    }
    vector<string> list = bfs(helper);
    if (helper.exec_need) {
        for (string const& file : list) {
            execute(helper.exec_path, file);
        }
    } else {
        for (auto out : list) {
            printf("%s\n", out.data());
        }
    }

    return 0;
}