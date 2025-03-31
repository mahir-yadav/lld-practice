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
class Vote;
class Tag
{
private:
    int id;
    string name;

public:
    Tag(int id, string name)
    {
        this->id = id;
        this->name = name;
    }
    string getName()
    {
        return name;
    }
};
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
    vector<Tag *> tags;
    vector<Vote *> votes;

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
    void addVote(Vote *vote)
    {
        votes.push_back(vote);
    }
    void addTag(string name)
    {
        tags.push_back(new Tag(tags.size() + 1, name));
    }
    vector<Tag *> getTags()
    {
        return tags;
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
    vector<Vote *> votes;

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
    void addVote(Vote *vote)
    {
        votes.push_back(vote);
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
class Vote
{
private:
    User *voter;
    bool isUpvote;

public:
    Vote(User *voter, bool isUpvote)
    {
        this->voter = voter;
        this->isUpvote = isUpvote;
    }
    User *getVoter()
    {
        return voter;
    }
    bool getIsUpVote()
    {
        return isUpvote;
    }
};

class Stackoverflow
{
private:
    vector<Question *> questions;

public:
    void postQuestion(User *author, string title, string content, vector<string> tags)
    {
        Question *new_question = new Question(questions.size() + 1, author, title, content);
        questions.push_back(new_question);
        for (auto name : tags)
        {
            new_question->addTag(name);
        }

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
        cout << "No Answer found with id: " << answerId << " in " << questionId << endl;
    }
    void upVoteOnQuestion(int questionId, User *voter, bool isupvote)
    {
        for (auto &question : questions)
        {
            if (question->getId() == questionId)
            {
                Vote *new_vote = new Vote(voter, isupvote);
                question->addVote(new_vote);
                if (isupvote)
                    cout << voter->getName() << " upvoted on " << question->getTitle() << endl;
                else
                    cout << voter->getName() << " downvoted on " << question->getTitle() << endl;
                return;
            }
        }
        cout << "No Question found with id: " << questionId << endl;
    }
    void upVoteOnAnswer(int questionId, int answerId, User *voter, bool isupvote)
    {
        for (auto &question : questions)
        {
            if (question->getId() == questionId)
            {
                for (auto &answer : question->getAnswers())
                {
                    if (answer->getId() == answerId)
                    {
                        Vote *new_vote = new Vote(voter, isupvote);
                        answer->addVote(new_vote);
                        if (isupvote)
                            cout << voter->getName() << " upvoted on " << answer->getContent() << endl;
                        else
                            cout << voter->getName() << " downvoted on " << answer->getContent() << endl;
                        return;
                    }
                }
            }
        }
        cout << "No Answer found with id: " << answerId << " in " << questionId << endl;
    }
    void searchQuestionBasedOnTag(string name)
    {
        bool flag = false;
        int count = 1;
        for (auto &question : questions)
        {
            vector<Tag *> tags = question->getTags();
            for (auto &tag : tags)
            {
                if (tag->getName() == name)
                {
                    cout << count << ". " << question->getTitle() << " by " << question->getAuthor()->getName() << endl;
                    flag = true;
                    count += 1;
                }
            }
        }
        if (!flag)
        {
            cout << "No question found with such tag" << endl;
        }
    }
    void searchQuestionBasedOnUser(string author)
    {
        bool flag = false;
        int count = 1;
        for (auto &question : questions)
        {
            if (question->getAuthor()->getName() == author)
            {
                cout << count << ". " << question->getTitle() << " by " << question->getAuthor()->getName() << endl;
                flag = true;
                count += 1;
            }
        }
        if (!flag)
        {
            cout << "No question found with such tag" << endl;
        }
    }
};
int main()
{
    Stackoverflow st;
    User *user1 = new User(1, "luffy");
    User *user2 = new User(2, "hyogoro");
    User *user3 = new User(3, "Captain kid");
    User *user4 = new User(4, "Nami");
    User *user5 = new User(5, "Zoro");
    User *user6 = new User(6, "killer");

    st.postQuestion(user1, "Advanced armament haki", "how to use it , i have seen rayleigh using it.", {"One Piece", "Haki"});
    cout << "Show All Questions: " << endl;
    st.showAllQuestions();
    st.postAnswer(user2, 1, "just let your haki flow in your fist.");
    st.showAnswers(1);
    st.addCommentOnQuestion(user3, 1, "Shut up you stupid monkey!");
    st.addCommentOnAnswer(user1, 1, 1, "Thanks hyogoro!");
    st.upVoteOnQuestion(1, user4, 1);
    st.upVoteOnQuestion(1, user5, 1);
    st.upVoteOnAnswer(1, 1, user6, 1);
    st.searchQuestionBasedOnTag("One Piece");
    st.searchQuestionBasedOnUser("luffy");
}