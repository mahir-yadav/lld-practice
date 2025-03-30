#include <bits/stdc++.h>
using namespace std;
// Users
// id,name,reputation

// question
// id,title,content,author,comments,answers,votes,tags

// answer
// id,content,author,which question,comments,votes

// vote
// which q/ans

// comment
// id,conent,author

// tag
// id,name,which question

// Stackoverflow
//
class User
{
private:
    int id, reputation;
    string name;

public:
    User(int id, string name)
    {
        this->name = name;
        this->id = id;
        this->reputation = 0;
    }
};
class Question
{
private:
    int id;
    string title, content;
    User *author;
    vector<Comment *> comments;
    vector<Answer *> answers;
    vector<Tag *> tags;
    vector<Vote *> votes;
public:
};
class Answer
{
private:
    int id;
    string content;
    User *author;
    Question *question;
    vector<Comment *> comments;
    vector<int> votes;
public:
};
class Comment
{
private:
    int id;
    string content;
    User *author;
    Question *question;
    Answer *answer;
public:
};
class Vote
{
private:
    User *voter;
    bool isUpvote;
public:
};
class Tag
{
private:
    int id;
    string name;
public:
};
