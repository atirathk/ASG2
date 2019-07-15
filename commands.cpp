// $Id: commands.cpp,v 1.17 2018-01-25 14:02:55-08 - - $

#include "commands.h"
#include "debug.h"

command_hash cmd_hash{
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
};

command_fn find_command_fn(const string& cmd) {
     // Note: value_type is pair<const key_type, mapped_type>
     // So: iterator->first is key_type (string)
     // So: iterator->second is mapped_type (command_fn)
     //DEBUGF('c', "[" << cmd << "]");
     const auto result = cmd_hash.find(cmd);
     if (result == cmd_hash.end()) {
          throw command_error(cmd + ": no such function");
     }
     return result->second;
}

command_error::command_error(const string& what) :
     runtime_error(what) {
}

int exit_status_message() {
     int exit_status = exit_status::get();
     cout << execname() << ": exit(" << exit_status << ")" << endl;
     return exit_status;
}

void fn_cat(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
     for (auto i = words.begin(); i < words.end(); i++) {
          cout << *i;
     }
     state.prompt();
}

void fn_cd(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
     inode_ptr cwd = state.getcwd();
     for (auto i = words.begin(); i < words.end(); i++) {
          if (state.setCwd(*i) == false) {
               return;
          }
     }
}

void fn_echo(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
     cout << word_range(words.cbegin() + 1, words.cend()) << endl;
}

void fn_exit(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
     throw ysh_exit();
}

void fn_ls(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
     fn_cd(state, words);
     inode_ptr realcwd = state.getcwd();
     fn_cd(state, words);
     auto map = state.getcwd()->getContents()->getDirents();
     for (auto i = map.begin(); i != map.end(); i++) {
          inode_ptr current = i->second;
          string currentName = i->first;
          cout << current->get_inode_nr() << "	" << current->getContents()->size() << " " << currentName << '\n';
     }
     state.setCwd(realcwd);
}

void fn_lsr(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
}

void fn_make(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
}

void fn_mkdir(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
}

void fn_prompt(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
     state.setPrompt(words);
}

void fn_pwd(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
     if (state.getcwd()->getContents()->getDirents()[".."] == nullptr) {
          cout << "/\n";
     }
     //state.getcwd()->getContents()->getDirents()[];
}

void fn_rm(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
     fn_cd(state, words);
     inode_ptr realcwd = state.getcwd();
     fn_cd(state, words);
     auto map = state.getcwd()->getContents()->getDirents();
     map.erase(*words.cend());
     state.setCwd(realcwd);
}

void fn_rmr(inode_state& state, const wordvec& words) {
     //DEBUGF('c', state);
     //DEBUGF('c', words);
}

