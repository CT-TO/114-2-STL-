#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

struct Student{
    string id;
    string name;
    int score;

    bool operator>(const Student& other){
        return this->score > other.score;
    }

    bool operator<(const Student& other){
        return this->score < other.score;
    }
};

template <class T>
T getMax(T a, T b){
    return (a > b) ? a : b;
}

template <class T>
T getMin(T a, T b){
    return (a < b) ? a : b;
}

//return a new object with passed variable
Student makeStudent(string id, string name, int score){
    Student temp = {id, name, score};
    return temp;
}

//print out the info of the passed Student
void printInfo(const Student out){
    cout<<"Student id: "<<out.id<<", name: "<<out.name<<", score: "<<out.score<<endl;
}

//compare the score of two passed  Student
bool compareScore(const Student S1, const Student S2){
    return(S1.score>S2.score);
}



//main function
int main(){
    vector<Student> stu;                        //vector that stores all students
    vector<Student>::iterator Find;             //temporary stores iterator
    string inpId, inpName;                      //variables that store input id, name
    int inpScore;                               //variable that stores input score
    int highest = 0, lowest = 0, pass, fail;    //variables that store statistics
    double average = 0;                         //variable that stores statistic

    cout<<"Function 1. Add student> "<<endl;
    cout<<"Enter <STOP> to stop this progress."<<endl;

    while(1){
        cout<<"Please enter the id> ";
        cin>>inpId;
        if(inpId == "STOP"){
            break;
        }

        cout<<"Please enter the name of the student> ";
        cin>>inpName;
        if(inpName == "STOP"){
            break;
        }

        cout<<"Please enter the score(only integer)> ";
        cin>>inpScore;
        
        Find = find_if(stu.begin(), stu.end(), [inpId](const Student& s){return s.id == inpId;});   //if a same id already exits
        if(Find!=stu.end()){
            (*Find).name = inpName;
            (*Find).score = inpScore;
        }
        else{
            stu.push_back(makeStudent(inpId, inpName, inpScore));   //if this is a different student, push in stu
        }
    }


    cout<<"\nFunction 2. List all students> "<<endl;
    for(int i = 0; i<stu.size(); i++){
        printInfo(stu[i]);
    }


    cout<<"\nFunction 3. Sort by score> "<<endl;
    sort(stu.begin(), stu.end(), compareScore);


    cout<<"\nFunction 4. Search by id> "<<endl;
    cout<<"Enter <STOP> to stop this progress."<<endl;
    
    while(1){
        cout<<"Please enter the id> ";
        cin>>inpId;
        if(inpId == "STOP"){
            break;
        }

        Find = find_if(stu.begin(), stu.end(), [inpId](const Student& S){return S.id == inpId;});   //if there is a same id

        if(Find != stu.end()){
            cout<<"Student information: "<<endl;
            printInfo(*Find);
        }
        else{
            cout<<"Student id "<<inpId<<" not found"<<endl;
        }
        cout<<endl;
    }


    cout<<"\nFunction 5. Show statistics> "<<endl;
    //highest = (*max_element(stu.begin(), stu.end(), [](const Student& S1, const Student& S2){return S1.score<S2.score;})).score;

    highest = stu[0].score;
    for(Find = stu.begin()+1; Find!=stu.end(); Find++){
        highest = getMax(highest, (*Find).score);
    }

    lowest = (*min_element(stu.begin(), stu.end(),  [](const Student& S1, const Student& S2){return S1.score<S2.score;})).score;
    for(Find = stu.begin(); Find!=stu.end(); Find++){
        average += (*Find).score;
    }
    average /= stu.size();
    
    pass = count_if(stu.begin(), stu.end(), [](const Student& S){return S.score>=60;});
    fail = count_if(stu.begin(), stu.end(), [](const Student& S){return S.score<60;});

    cout<<"Highest: "<<highest<<", lowest: "<<lowest<<endl;
    cout<<"Average: "<<average<<endl;
    cout<<"Passed: "<<pass<<", failed: "<<fail<<endl;

    return 0;
}