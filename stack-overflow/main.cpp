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
class User;
class Comment;
class Vote;
class Tag;
class Question;
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
    void incReputation(int points)
    {
        this->reputation += points;
    }
    void decReputation(int points)
    {
        this->reputation -= points;
    }
    void displayInfo()
    {
        cout << id << ". " << name << " [" << reputation << "] " << endl;
    }
    int getId()
    {
        return id;
    }
    int getReputation()
    {
        return reputation;
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
    int getId()
    {
        return this->id;
    }
    string getContent()
    {
        return content;
    }
    User *getAuthor()
    {
        return author;
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
    unordered_map<User *, int> votesmap;

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
    bool addVote(Vote *vote)
    {
        if (votesmap.find(vote->getVoter()) != votesmap.end())
        {
            if (votesmap[vote->getVoter()] != vote->getIsUpVote())
            {
                votesmap[vote->getVoter()] = 1 - vote->getIsUpVote();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            votesmap[vote->getVoter()] = vote->getIsUpVote();
            votes.push_back(vote);
            return true;
        }
    }
    unordered_map<User *, int> getVotesMap()
    {
        return votesmap;
    }
    void showComments()
    {
        if (comments.size() != 0)
            cout << "Comments:- " << endl;
        for (auto &comment : comments)
        {
            cout << "          " << comment->getId() << ". " << comment->getContent() << " by " << comment->getAuthor()->getName() << endl;
        }
    }
};

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
    unordered_map<User *, int> votesmap;

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
    bool addVote(Vote *vote)
    {
        if (votesmap.find(vote->getVoter()) != votesmap.end())
        {
            if (votesmap[vote->getVoter()] != vote->getIsUpVote())
            {
                votesmap[vote->getVoter()] = 1 - vote->getIsUpVote();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            votesmap[vote->getVoter()] = vote->getIsUpVote();
            votes.push_back(vote);
            return true;
        }
    }
    void addTag(string name)
    {
        tags.push_back(new Tag(tags.size() + 1, name));
    }
    vector<Tag *> getTags()
    {
        return tags;
    }
    unordered_map<User *, int> getVotesMap()
    {
        return votesmap;
    }
    void showAnswers()
    {
        if (answers.size() != 0)
            cout << "Answers:- " << endl;
        for (auto &ans : answers)
        {
            cout << ans->getId() << ". " << ans->getContent() << " by " << ans->getAuthor()->getName() << endl;
            ans->showComments();
        }
    }
    void showComments()
    {
        if (comments.size() != 0)
            cout << "Comments:- " << endl;
        for (auto &comment : comments)
        {
            cout << "        " << comment->getId() << ". " << comment->getContent() << " by " << comment->getAuthor()->getName() << endl;
        }
    }
};

class Stackoverflow
{
private:
    vector<User *> users;
    vector<Question *> questions;
    unordered_map<string, User *> name_user_map;

public:
    void postQuestion(string name, string title, string content, vector<string> tags)
    {
        User *author = name_user_map[name];
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
            question->showAnswers();
            question->showComments();
        }
    }
    void postAnswer(string name, int questionId, string content)
    {
        User *author = name_user_map[name];

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
    void showAnswer(int questionId)
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
    void addCommentOnQuestion(string name, int questionId, string content)
    {
        User *author = name_user_map[name];

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
    void addCommentOnAnswer(string name, int questionId, int answerId, string content)
    {
        User *author = name_user_map[name];

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
    void upVoteOnQuestion(int questionId, string name, bool isupvote)
    {
        User *voter = name_user_map[name];

        for (auto &question : questions)
        {
            if (question->getId() == questionId)
            {
                Vote *new_vote = new Vote(voter, isupvote);
                bool check = question->addVote(new_vote);
                if (!check)
                {
                    if (question->getVotesMap()[voter] == 1 && isupvote == 0)
                    {
                        question->getAuthor()->decReputation(1);
                    }
                    if (question->getVotesMap()[voter] == 0 && isupvote == 1)
                    {
                        question->getAuthor()->incReputation(1);
                    }
                    cout << "You Already Voted!" << endl;
                    return;
                }
                if (isupvote)
                {
                    question->getAuthor()->incReputation(1);
                    cout << voter->getName() << " upvoted on " << question->getTitle() << endl;
                }
                else
                {
                    question->getAuthor()->decReputation(1);
                    cout << voter->getName() << " downvoted on " << question->getTitle() << endl;
                }
                return;
            }
        }
        cout << "No Question found with id: " << questionId << endl;
    }
    void upVoteOnAnswer(int questionId, int answerId, string name, bool isupvote)
    {
        User *voter = name_user_map[name];
        for (auto &question : questions)
        {
            if (question->getId() == questionId)
            {
                for (auto &answer : question->getAnswers())
                {
                    if (answer->getId() == answerId)
                    {
                        Vote *new_vote = new Vote(voter, isupvote);
                        bool check = answer->addVote(new_vote);
                        if (!check)
                        {
                            if (answer->getVotesMap()[voter] == 1 && isupvote == 0)
                            {
                                answer->getAuthor()->decReputation(1);
                            }
                            if (answer->getVotesMap()[voter] == 0 && isupvote == 1)
                            {
                                answer->getAuthor()->incReputation(1);
                            }
                            cout << "You Already voted!!" << endl;
                            return;
                        }
                        if (isupvote)
                        {
                            answer->getAuthor()->incReputation(1);
                            cout << voter->getName() << " upvoted on " << answer->getContent() << endl;
                        }
                        else
                        {
                            answer->getAuthor()->decReputation(1);
                            cout << voter->getName() << " downvoted on " << answer->getContent() << endl;
                        }
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
    void addUser(string name)
    {
        User *new_user = new User(users.size() + 1, name);
        name_user_map[name] = new_user;
        users.push_back(new_user);
    }
    void displayInfo(string name)
    {
        User *author = name_user_map[name];
        author->displayInfo();
    }
    void showAllUsers()
    {
        for (auto &user : users)
        {
            cout << user->getId() << ". " << user->getName() << " Reputation: [" << user->getReputation() << "] " << endl;
        }
    }
};
int main()
{
    Stackoverflow st;
    st.addUser("luffy");
    st.addUser("hyogoro");
    st.addUser("Captain kid");
    st.addUser("Nami");
    st.addUser("zoro");
    st.addUser("killer");

    st.postQuestion("luffy", "Advanced armament haki", "how to use it , i have seen rayleigh using it.", {"One Piece", "Haki"});
    cout << "Show All Questions: " << endl;
    st.postAnswer("hyogoro", 1, "just let your haki flow in your fist.");
    st.postAnswer("Captain kid", 1, "u can't u monkey!");

    st.showAnswer(1);
    st.addCommentOnQuestion("Captain kid", 1, "Shut up you stupid monkey!");
    st.addCommentOnAnswer("luffy", 1, 1, "Thanks hyogoro!");
    st.upVoteOnQuestion(1, "Nami", 1);
    st.upVoteOnQuestion(1, "zoro", 1);
    st.upVoteOnQuestion(1, "Captain kid", 1);

    st.upVoteOnAnswer(1, 1, "killer", 1);
    st.searchQuestionBasedOnTag("One Piece");
    st.searchQuestionBasedOnUser("luffy");
    st.displayInfo("luffy");
    st.upVoteOnAnswer(1, 2, "killer", 1);
    st.upVoteOnQuestion(1, "killer", 0);
    st.showAllQuestions();
    st.showAllUsers();
}