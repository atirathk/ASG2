// $Id: file_sys.cpp,v 1.6 2018-06-27 14:44:57-07 - - $

#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include<string>
using namespace std;

#include "debug.h"
#include "file_sys.h"

size_t inode::next_inode_nr{ 1 };

struct file_type_hash {
     size_t operator() (file_type type) const {
          return static_cast<size_t> (type);
     }
};

ostream& operator<< (ostream& out, file_type type) {
     static unordered_map<file_type, string, file_type_hash> hash{
        {file_type::PLAIN_TYPE, "PLAIN_TYPE"},
        {file_type::DIRECTORY_TYPE, "DIRECTORY_TYPE"},
     };
     return out << hash[type];
}

inode_state::inode_state() {
     root = inode_ptr(new inode(file_type::DIRECTORY_TYPE));
     root->contents->mkdir("/");
     cwd = inode_ptr(root);
}

const string& inode_state::prompt() const { return static_cast<const string&>(prompt_); }

void inode_state::setPrompt(const wordvec& newPrompt) {
     for (auto i = newPrompt.begin(); i != newPrompt.end(); i++) {
          prompt_.append(*i);
     }
}

ostream& operator<< (ostream& out, const inode_state& state) {
     out << "inode_state: root = " << state.root
          << ", cwd = " << state.cwd;
     return out;
}

inode::inode(file_type type) : inode_nr(next_inode_nr++) {
     switch (type) {
     case file_type::PLAIN_TYPE:
          contents = make_shared<plain_file>();
          break;
     case file_type::DIRECTORY_TYPE:
          contents = make_shared<directory>();
          break;
     }
}

bool inode_state::setCwd(const string& dir) {
     auto map = cwd->contents->getDirents();
     auto i = map.find(dir);
     if (i == map.end()) {
          return false;
     }
     cwd = i->second;
     return true;
}
void inode_state::setCwd(const inode_ptr& dir) {
     cwd = dir;
}
inode_ptr inode_state::getcwd() {
     return cwd;
}

size_t inode::get_inode_nr() const {
     return inode_nr;
}

base_file_ptr inode::getContents() {
     return contents;
}

file_error::file_error(const string& what) :
     runtime_error(what) {
}

//plain_file::~plain_file() {
//     data.clear();
//}

plain_file::plain_file() {

}

plain_file::plain_file(wordvec d) {
     data = d;
}

size_t plain_file::size() const {
     size_t size{ 0 };
     for (auto i = data.begin(); i < data.end(); i++) {
          size += i->length();
     }
     DEBUGF('i', "size = " << size);
     return size;
}

const wordvec& plain_file::readfile() const {
     //DEBUGF('i', data);
     return data;
}

void plain_file::writefile(const wordvec& words) {
     //DEBUGF('i', words);
     data = words;
}

void plain_file::remove(const string&) {
     throw file_error("is a plain file");
}

inode_ptr plain_file::mkdir(const string&) {
     throw file_error("is a plain file");
}

inode_ptr plain_file::mkfile(const string&) {
     throw file_error("is a plain file");
}

map<string, inode_ptr> plain_file::getDirents() {
     throw file_error("is a plain file");
}

void plain_file::init_dir(inode_ptr current, inode_ptr parent) {
     throw file_error("is a plain file");
}

//directory::~directory() {
//     dirents.~map();
//}

directory::directory(map<string, inode_ptr> d) {
     dirents = d;
}
directory::directory() {

}
size_t directory::size() const {
     size_t size{ 0 };
     //DEBUGF('i', "size = " << size);
     size = dirents.size();
     return size;
}

const wordvec& directory::readfile() const {
     throw file_error("is a directory");
}

void directory::writefile(const wordvec&) {
     throw file_error("is a directory");
}

void directory::remove(const string& filename) {
     //DEBUGF('i', filename);
     dirents.erase(filename);
}

inode_ptr directory::mkdir(const string& dirname) {
     inode_ptr newPtr(new inode(file_type::DIRECTORY_TYPE));
     if (dirname.compare( "/") == 0) {
          dirents["."] = newPtr;
          dirents[".."] = nullptr;
          return newPtr;
     }
     auto j = dirents.emplace(dirname, newPtr);
     if (j.second == false) {
          dirents.erase(j.first);
          //j = dirents.emplace(dirname, newPtr);
          dirents[dirname] = newPtr;
     }
     map<string, inode_ptr> newDirents;
     newDirents["."] = newPtr;
     newDirents[".."] = dirents["."];
     newPtr->getContents()->setDirents(newDirents);
}

inode_ptr directory::mkfile(const string& filename) {
     //DEBUGF('i', filename);
     //auto j = dirents.emplace(filename);
     //if(j.second == false) {
     //     dirents.erase(j.first);
     //     dirents[filename] = inode_ptr();
     //}
}

map<string, inode_ptr> directory::getDirents() {
     return dirents;
}

void inode_state::rootDir(inode_ptr ptr) {
     //ptr = shared_ptr<inode>;
     malloc(sizeof(size_t) * 2 + sizeof(base_file_ptr));
}

void directory::init_dir(inode_ptr current, inode_ptr parent) {
     //mkdir(".");
     dirents["."] = current;
     dirents[".."] = parent;
}

//inode &inode::operator= (const inode& that) {
//     if (this == nullptr) {
//     }
//     size_t next_inode_nr;
//     size_t inode_nr;
//     base_file_ptr contents;
//
//     this->next_inode_nr = that.next_inode_nr;
//     this->inode_nr = that.inode_nr;
//     this->contents = that.contents;
//}

//inode_ptr inode::operator= (const inode& that) {
//     //size_t inode_nr;
//     //size_t next_inode_nr;
//     //base_file_ptr contents;
//
//     inode_nr = that->inode_nr;
//     next_inode_nr = that->next_inode_nr;
//     contents = that->contents;
//}

//base_file_ptr& inode::operator= (const directory* that) {
//     this->contents = make_shared<directory>();
//     this->contents = that;
//}

void plain_file::setDirents(map<string, inode_ptr> newDirents) {
     throw file_error("is a plain file");
}

void directory::setDirents(map<string, inode_ptr> newDirents) {
     dirents = newDirents;
}