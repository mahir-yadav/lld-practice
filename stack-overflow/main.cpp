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
class Answer;
class Comment;
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
    string getName()
    {
        return name;
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
    // vector<Tag *> tags;
    // vector<Vote *> votes;

public:
    Question(int id, User *author, string title, string content)
    {
        this->id = id;
        this->author = author;
        this->title = title;
        this->content = content;
    }
    User *getAuthor()
    {
        return author;
    }
    string getTitle()
    {
        return title;
    }
    int getId()
    {
        return id;
    }
    vector<Answer *> getAnswers()
    {
        return answers;
    }
    void addAnswer(Answer *answer)
    {
        answers.push_back(answer);
    }
    vector<Comment *> getComments()
    {
        return comments;
    }
    void addComment(Comment *comment)
    {
        comments.push_back(comment);
    }
};
class Answer
{
private:
    int id;
    string content;
    User *author;
    Question *question;
    vector<Comment *> comments;
    // vector<int> votes;

public:
    Answer(int id, string content, User *author, Question *question)
    {
        this->id = id;
        this->content = content;
        this->author = author;
        this->question = question;
    }
    int getId()
    {
        return id;
    }
    User *getAuthor()
    {
        return author;
    }
    string getContent()
    {
        return content;
    }
    vector<Comment *> getComments()
    {
        return comments;
    }
    void addComment(Comment *comment)
    {
        comments.push_back(comment);
    }
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
    Comment(int id, string content, User *author)
    {
        this->id = id;
        this->content = content;
        this->author = author;
    }
};
// class Vote
// {
// private:
//     User *voter;
//     bool isUpvote;

// public:
// };
// class Tag
// {
// private:
//     int id;
//     string name;

// public:
// };
class Stackoverflow
{
private:
    vector<Question *> questions;

public:
    void postQuestion(User *author, string title, string content)
    {
        questions.push_back(new Question(questions.size() + 1, author, title, content));
        cout << "Question posted: " << title << " by " << author->getName() << endl;
    }
    void showAllQuestions()
    {
        for (auto &question : questions)
        {
            cout << question->getId() << ". " << question->getTitle() << " by " << question->getAuthor()->getName() << endl;
        }
    }
    void postAnswer(User *author, int questionId, string content)
    {
        for (auto &question : questions)
        {
            if (question->getId() == questionId)
            {
                Answer *newAns = new Answer(question->getAnswers().size() + 1, content, author, question);
                question->addAnswer(newAns);

                cout << "Answer Posted to question: " << question->getTitle() << " by " << author->getName() << endl;
                return;
            }
        }
        cout << "No Question found with id: " << questionId << endl;
    }
    void showAnswers(int questionId)
    {
        for (auto &question : questions)
        {
            if (question->getId() == questionId)
            {
                vector<Answer *> ans = question->getAnswers();
                if (ans.size() == 0)
                {
                    cout << "No answer for this question yet!" << endl;
                    return;
                }
                for (auto &answer : ans)
                {
                    cout << answer->getId() << ". " << answer->getContent() << " by " << answer->getAuthor()->getName() << endl;
                }
                return;
            }
        }
        cout << "No Question found with id: " << questionId << endl;
    }
    void addCommentOnQuestion(User *author, int questionId, string content)
    {
        for (auto &question : questions)
        {
            if (question->getId() == questionId)
            {
                Comment *new_comment = new Comment(question->getComments().size() + 1, content, author);
                question->addComment(new_comment);
                cout << author->getName() << " commented on question: " << question->getTitle() << endl;
                return;
            }
        }
        cout << "No Question found with id: " << questionId << endl;
    }
    void addCommentOnAnswer(User *author, int questionId, int answerId, string content)
    {
        for (auto &question : questions)
        {
            if (question->getId() == questionId)
            {
                for (auto &answer : question->getAnswers())
                {
                    if (answer->getId() == answerId)
                    {
                        Comment *new_comment = new Comment(answer->getComments().size() + 1, content, author);
                        answer->addComment(new_comment);
                        cout << author->getName() << " commented on " << answer->getContent() << endl;
                        return;
                    }
                }
            }
        }
        cout << "No Answer found with id: " << answerId << " in " << questionId <<endl;
    }
};
int main()
{
    Stackoverflow st;
    User *user1 = new User(1, "luffy");
    User *user2 = new User(2, "hyogoro");
    User *user3 = new User(3, "Captain kid");
    st.postQuestion(user1, "Advanced armament haki", "how to use it , i have seen rayleigh using it.");
    cout << "Show All Questions: " << endl;
    st.showAllQuestions();
    st.postAnswer(user2, 1, "just let your haki flow in your fist.");
    st.showAnswers(1);
    st.addCommentOnQuestion(user3, 1, "Shut up you stupid monkey!");
    st.addCommentOnAnswer(user1, 1, 1, "Thanks hyogoro!");

}