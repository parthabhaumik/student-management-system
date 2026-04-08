#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
class Student{
public:
string name;
string roll;
float rating;
Student(string n,string r,float rat){
    name = n;
    roll = r;
    rating = rat;
}   
};
void updateRatings(float&Ra,float&Rb,int result){
    float Ea = 1/(1+pow(10,(Rb-Ra)/400.0));
     float Eb = 1/(1+pow(10,(Rb-Ra)/400.0));
    float k=32;
    if(result==1){
        Ra = Ra+k*(1-Ea);
        Rb = Rb+k*(0-Eb);
    } else if (result == 2){
        Ra = Ra+k*(0-Ea);
        Rb = Rb+k*(1-Eb);
    } else if (result == 0){
        Ra = Ra + k * (0.5 - Ea);
        Rb = Rb + k * (0.5 - Eb);
    }
}
void savedata(vector<Student>&database){
    ofstream outfile("student.txt");
    for(const auto& s:database){
        outfile<<s.name<<" "<<s.roll<<" "<<s.rating<<"\n";
    }
}
void loadFromDatabase(vector<Student>&database){
    ifstream inFile("student.txt");
    if(inFile.is_open()){
string n,r;
float rat;
while(inFile>>n>>r){
    if(!(inFile>>rat)){
        break;
    }
    database.push_back(Student(n,r,rat));
}
inFile.close();
    }
}

    int main(){
 vector<Student>database;
loadFromDatabase(database);
    const string GREEN = "\033[32m";
    const string RED = "\033[31m";
    const string BLUE = "\033[94m";//bright
    const string YELLOW = "\033[33m";
    const string RESET = "\033[0m";
    string secretsalt = "@#P123";
    string password = "p99";
    cout<<BLUE<<"WELCOME TO STUDENT DATABASE!"<<RESET<<"\n";
    string pass;
    cout<<"Enter Password: ";
cin>>pass;
string finalpass = password + secretsalt;
if(finalpass == pass + secretsalt){
    cout<<GREEN<<"ACCESS GRANTED"<<RESET<<"\n";
} else {
cout<<RED<<"WRONG PASSWORD, PLEASE TRY AGAIN!"<<RESET<<"\n";
return 0;
}
int choice;
while(true){
    cout<<"What you want to do?"<<"\n";
    cout<<YELLOW<<"1.Add Student | 2.Show List | 3.Delet Student | 4.Update Rating | 5.Exit"<<RESET<<"\n";
    cin>>choice;
    if(choice == 1){
        string n;
        string r;
        float rat;
        cout<<"Enter name: ";
        cin.ignore();
        getline(cin,n);
        cout<<"Enter roll: ";
        cin>>r;
    database.push_back(Student( n,r,1200.0));
    savedata(database);
    cout<<GREEN<<"Your data has been saved."<<RESET<<"\n";
} else if(choice == 2){
    if(database.empty()){
        cout<<RED<<"There's no database yet."<<RESET<<"\n";
    } else {
sort(database.begin(),database.end(),[](const Student& a,const Student& b){
    return a.rating>b.rating;
});
cout<<"---Student Ranking---"<<"\n";
for(const auto& s : database){
    cout<<"Name: "<<s.name<<" | Roll: "<<s.roll<<" | Rating: "<<fixed<<setprecision(1)<<s.rating<<"\n";
}
}
} else if(choice == 3) {
    string r;
    cout<<"Which student you want to delet?\nEnter roll: ";
    cin>>r;
    bool found= false;
    for(int i=0;i<database.size();i++){
        if(database[i].roll == r){
            database.erase(database.begin()+i);
            savedata(database);
            found = true;
            break;
        }
    }
        if(found){
        cout<<GREEN<<"Deleted!"<<RESET<<"\n";
        } else {
        cout<<RED<<"Not Found!"<<RESET<<"\n";
        } 
    } else if(choice == 4){
        string r1,r2;
        cout<<"Enter the first student's roll: ";
        cin>>r1;
        cout<<"Enter the second student's roll: ";
        cin>>r2;
        int indexA = -1 , indexB = -1;
        for(int i=0;i<database.size();i++){
            if(database[i].roll == r1)
            indexA = i;
            if(database[i].roll == r2)
            indexB = i;
        }
        if(indexA != -1 && indexB != -1){
            int winner;
            cout<<"Result?(1: "<<database[indexA].name<<", 2: "<<database[indexB].name<<", 0: Draw):";
            cin>>winner;
            updateRatings(database[indexA].rating,database[indexB].rating,winner);
            savedata(database);
            cout<<GREEN<<"Rating updated successfully!"<<RESET<<"\n";
        } else {
            cout<<RED<<"Not found! cheak the roll again!"<<RESET<<"\n";
        }

    } else if(choice == 5){
        cout<<"Exiting...."<<"\n";
    break;

} else {
    cout<<RED<<"Invalid Option!"<<RESET<<"\n";
}
}
return 0;
    }
