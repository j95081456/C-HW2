#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>

using namespace std;
using std::string;

class people{
    private:
        int row , col , DAY , state ,touched ;
        int A[4];
        string NAME , condition;
    public: 
        people(/*int r , int c , int cond , int day , string name*/);
        void set(int r , int c , string cond , int day , string name , int s , int t);
        void setday(int d);
        void setstate(int s);
        void settouched(int t);
        void setcondition(string s);
        void setlabel(int i ,int v);
        int getday();
        int getrow();
        int getcol();
        int getstate();
        int gettouched();
        int check(int a, int b ,int c, int d);
        string getcondition();
        string getname();
};
people::people(/*int r , int c , int cond , int day , string name*/){
    /*row = r;
    col = c;
    condition = cond;
    day = day;
    name = name;*/
};
void people::set(int r , int c , string cond , int day , string name , int s , int t){
    row = r;
    col = c;
    condition = cond;
    DAY = day;
    NAME = name;
    state = s;
    touched = t;
};
void people::setday(int d){
    DAY = d;
};
void people::setstate(int s){
    state = s;
};
void people::settouched(int t){
    touched = t;
};
void people::setcondition(string s){
    condition = s;
};
void people::setlabel(int i , int v){
    A[i] = v;
};
int people::getday(){
    return DAY;
};
int people::getrow(){
    return row;
};
int people::getcol(){
    return col;
};
int people::getstate(){
    return state;
};
int people::gettouched(){
    return touched;
};
int people::check(int a, int b ,int c, int d){
    return 16*(A[3]&a) + 8*(A[2]&b) + 4*(A[1]&c) + (A[0]&d);
    //return 16*A + 8*B + 4*C +D;
};
string people::getcondition(){
    return condition;
};
string people::getname(){
    return NAME;
};

void infection(people ***matrix , int ROW , int COL);
int ICUdetect(people ***matrix , int ROW , int COL);

queue <int> touchedr;
queue <int> touchedc;
queue <int> ICU;
int r1 , c1;

int main(){
    int icu , outputday , n ;
    cin >> r1 >> c1 >> icu >> outputday ;
    cin >> n;
    int day[n];
    int row[n];
    int col[n];
    float death = 0;
    string name[n];
    string condition[n];
    for (int i = 0 ; i < n ; i++){
        cin >> day[i] >> row[i] >> col[i] >> name[i] >> condition[i];
    }
    int index = 0;
    int nowday = 0;
    int c = 0;
    int temp = 0; //record new number of people
    //int temp1 = 0; 
    int count = 0;
    int numofsick = 0; 
    people *person = new people[n];
    //people *matrix[r1][c1] = {{0} , {0} }; // initial
    //people *matrix = new people [r1][c1]{0};
    people** tmp = new people*[r1*c1];
    people*** matrix = new people**[r1];;
    //people ICU = new people();
    for (int i = 0; i < r1; i++) matrix[i] = tmp + (c1 * i);
    while(nowday != outputday){
        int RR ,CC ;
        while(!touchedr.empty()){
            count = 0;
            RR = touchedr.front();
            CC = touchedc.front();
            touchedr.pop();
            touchedc.pop();
            matrix[RR][CC]->setcondition("Sick");
            matrix[RR][CC]->setday(14);
            int nsick1 = ICUdetect(matrix , RR , CC);
            /*if( nsick1 >= 2 && ( ICU.size() < icu )){
                        ICU.push(0);
                        matrix[RR][CC]->set(0 , 0 , "ICU" , 0 , matrix[RR][CC]->getname(), 0 , 0);
                        matrix[RR][CC]->setcondition("ICU");
                        matrix[RR][CC] = 0;
                }
            else {*/
                infection(matrix , RR , CC);
                matrix[RR][CC]->settouched(0);
            //}
        }
        //cout << "13nowday" << nowday << endl;
        temp = index;
        //cout << "input new person" << endl;
        while(day[index] == nowday){  // put new people
            c = 0;
            if(condition[index] == "Sick"){
                c = 14 ;
            }
            person[index].set(row[index] , col[index] , condition[index] , c , name[index] , 0 , 0);  // 0: state , 0:touched
            for(int i = 0; i < 4; i++){person[index].setlabel(i,0); }
            matrix[ row[index] ][ col[index] ] = &person[index];
            index++;
        }
        int R , C ;
        for (int i = temp; i < index ; i++){
            R = person[i].getrow();
            C = person[i].getcol();
            if(person[i].getcondition() == "Sick"){
                int nsick = ICUdetect(matrix , R , C);
                /*if( nsick >= 2 && ( ICU.size() < icu )){
                        //cout << matrix[R][C]->getname() << "ICU" << endl;
                        ICU.push(index);
                        matrix[R][C]->set(0 , 0 , "ICU" , 0 , matrix[R][C]->getname(), 0 , 0);
                        matrix[R][C]->setcondition("ICU");
                        matrix[R][C] = 0;
                }
                else*/ infection(matrix , person[i].getrow() , person[i].getcol());
            }
            if(person[i].getcondition() == "Healthy"){  // detect new healthy people will be sick?
                if(matrix[R][C]->gettouched() == 0){
                for (int i = 0; i < 4; i++){
                    if(R != r1 - 1){
                        if (matrix[R+1][C] != 0){
                            if(matrix[R+1][C]->getcondition() == "Sick"){
                                touchedr.push(R); // store index
                                touchedc.push(C);
                                matrix[R][C]->settouched(1);
                                break;
                            }
                        }
                    }
                    if(C != c1 - 1){
                        if (matrix[R][C+1] != 0){
                            if(matrix[R][C+1]->getcondition() == "Sick"){
                                touchedr.push(R); // store index
                                touchedc.push(C);
                                matrix[R][C]->settouched(1);
                                break;
                            }
                        }
                    }
                    if(C != 0){
                        if (matrix[R][C-1] != 0){
                            if(matrix[R][C-1]->getcondition() == "Sick"){
                                touchedr.push(R); // store index
                                touchedc.push(C);
                                matrix[R][C]->settouched(1);
                                break;
                            }
                        }
                    }
                    if(R != 0){
                        if (matrix[R-1][C] != 0){
                            if(matrix[R-1][C]->getcondition() == "Sick"){
                                touchedr.push(R); // store index
                                touchedc.push(C);
                                matrix[R][C]->settouched(1);
                                break;
                            }
                        }
                    }
                }
            }  
        }
        //index++;
        }
        for(int i = 0; i < index; i++){
            if (person[i].getday()>28 ){
                if( ICU.size() < icu){
                    ICU.push(i);
                    matrix[person[i].getrow()][person[i].getcol()] = 0;
                    person[i].set(0 , 0 , "ICU" , 0 , person[i].getname(), 0 , 0);
                    person[i].setcondition("Healthy");
                }
            }
        }
        for(int j = 0; j < index; j++){
            if ( (person[j].getrow() != 0 && person[j].getrow() != r1 - 1) && (person[j].getcol() != 0 && person[j].getcol() != c1 - 1) ){
                if(person[j].getcondition() != "ICU"){
                    numofsick = 0;
                    int R3 = person[j].getrow();
                    int C3 = person[j].getcol();
                    if(R3 < r1 - 1){
                        if (matrix[R3+1][C3] != 0){
                                if(matrix[R3+1][C3]->getcondition() == "Sick"){
                                    numofsick++;
                                }
                            }
                    }
                    if(C3 < c1 - 1){
                        if (matrix[R3][C3+1] != 0){
                                if(matrix[R3][C3+1]->getcondition() == "Sick"){
                                    numofsick++;
                                }
                            }
                    }
                    if(C3 > 0){
                        if (matrix[R3][C3-1] != 0){
                                if(matrix[R3][C3-1]->getcondition() == "Sick"){
                                    numofsick++;
                                }
                            }
                    }
                    if(R3 > 0){
                        if (matrix[R3-1][C3] != 0){
                                if(matrix[R3-1][C3]->getcondition() == "Sick"){
                                    numofsick++;
                                }
                            }
                    }
                if (numofsick ==4 ){ person[j].setstate( person[j].getstate()+1 ); }
                if (person[j].getstate() >= 7 && person[j].getcondition() != "death"){
                    matrix[R3][C3] = 0;       
                    death++;         
                    person[j].setcondition("death"); // matrix[R3][C3] = 0
                }
            }
            }
        }

        for(int j = 0; j < index; j++){
            if(person[j].getcondition() == "Sick"){
                person[j].setday( person[j].getday() -1 );
                if(person[j].getday() == 0){
                    person[j].setcondition("Healthy");
                    person[j].setstate(0);
                    person[j].settouched(0);
            }
        }
        //cout << person[j].getname() << " condition:" << person[j].getcondition() << " day:" << person[j].getday() <<" state:" <<person[j].getstate()<<" touched:" << person[j].gettouched()<<endl;
        }
        //cout << "ICU:" << ICU.size() << endl;
        //cout << "nowday" << nowday << endl;
        nowday++;
    }
    //cout << person[11].getcol();
    int output = 0;
    float rate = 100*(n-death)/n ; 
    //cout << "death:" <<death << endl;
    printf("%1.2f",rate);
    cout << '%' << endl;
    //cout << "rate:" << rate << endl;
    for(int i = 0; i < r1 ; i++){
        for(int j = 0; j < c1; j++){
            if( matrix[i][j] != 0 ){
                if( output == 0){
                    cout << matrix[i][j]->getname();
                    output++;
                }
                else{
                    cout << " " << matrix[i][j]->getname(); 
                }
            }
        }
    }
}

void infection(people ***matrix , int ROW , int COL){
        int rr , cc ;
        rr = ROW;
        cc = COL;
        if(ROW < r1 - 1){
            if(matrix[ ROW + 1 ][ COL + 0 ] != 0){ 
                if( matrix[rr + 1][cc + 0]->getcondition() == "Healthy" ){
                    if( matrix[rr + 1][cc + 0]->gettouched() != 1){
                        matrix[rr + 1][cc + 0]->settouched(1);
                        touchedr.push(rr+1);
                        touchedc.push(cc);
                    }    
                }
                if( matrix[rr + 1][cc + 0]->getcondition() == "Sick" ){
                    if(matrix[rr + 1][cc]->check(1,0,0,0) != 16){
                        matrix[rr + 1][cc + 0]->setday( matrix[rr + 1][cc + 0]->getday() +7 );
                        matrix[rr][cc]->setday( matrix[rr][cc]->getday() +7 );
                        matrix[rr][cc]->setlabel(0,1);
                    }
                }   
            }
        }
        if(COL < c1 - 1){
            if(matrix[ ROW + 0 ][ COL + 1 ] != 0){  
                if( matrix[rr + 0][cc + 1]->getcondition() == "Healthy" ){
                    if( matrix[rr + 0][cc + 1]->gettouched() != 1){
                        matrix[rr + 0][cc + 1]->settouched(1);
                        touchedr.push(rr);
                        touchedc.push(cc+1);
                    }        
                }
                if( matrix[rr + 0][cc + 1]->getcondition() == "Sick" ){
                    if(matrix[rr + 0][cc + 1]->check(0,1,0,0) != 8 ){
                        matrix[rr + 0][cc + 1]->setday( matrix[ rr + 0 ][ cc + 1 ]->getday() +7 );
                        matrix[rr][cc]->setday( matrix[rr][cc]->getday() +7 );
                        matrix[rr][cc]->setlabel(1,1);
                    }    
                }   
            }
        }
        if(COL > 0){
            if(matrix[ ROW + 0 ][ COL - 1 ] != 0){  
                if( matrix[rr + 0][cc - 1]->getcondition() == "Healthy" ){
                    if( matrix[rr + 0][cc - 1]->gettouched() != 1){
                        matrix[rr + 0][cc - 1]->settouched(1);
                        touchedr.push(rr);
                        touchedc.push(cc-1);
                    }        
                }
                if( matrix[rr + 0][cc - 1]->getcondition() == "Sick" ){
                    if(matrix[rr + 0][cc - 1]->check(0,0,1,0) != 4 ){
                        matrix[rr + 0][cc - 1]->setday( matrix[ rr + 0 ][ cc - 1 ]->getday() +7 );
                        matrix[rr][cc]->setday( matrix[rr][cc]->getday() +7 );
                        matrix[rr][cc]->setlabel(2,1);
                    }
                }   
            }
        }
        if(ROW > 0){
            if(matrix[ ROW - 1 ][ COL + 0 ] != 0){ 
                if( matrix[rr - 1][cc + 0]->getcondition() == "Healthy" ){
                    if( matrix[rr - 1][cc + 0]->gettouched() != 1){
                        matrix[rr - 1][cc + 0]->settouched(1);
                        touchedr.push(rr-1);
                        touchedc.push(cc);
                    }        
                }
                if( matrix[rr - 1][cc + 0]->getcondition() == "Sick" ){
                    if(matrix[rr - 1][cc + 0]->check(0,0,0,1) != 1 ){
                        matrix[rr - 1][cc + 0]->setday( matrix[ rr - 1 ][ cc + 0 ]->getday() +7 );
                        matrix[rr][cc]->setday( matrix[rr][cc]->getday() +7 );
                        matrix[rr][cc]->setlabel(3,1);
                    }
                }   
            }
        }
    }
int ICUdetect(people ***matrix , int ROW , int COL){
    int rr , cc ;
    int sick = 0;
        rr = ROW;
        cc = COL;
        if(ROW < r1 - 1){
            if(matrix[ ROW + 1 ][ COL + 0 ] != 0){ 
                if( matrix[rr + 1][cc + 0]->getcondition() == "Sick" ){
                    sick++;   
            }
        }
        }
        if(COL < c1 - 1){
            if(matrix[ ROW + 0 ][ COL + 1 ] != 0){  
                if( matrix[rr + 0][cc + 1]->getcondition() == "Sick" ){
                    sick++;    
                }   
            }
        }
        if(COL > 0){
            if(matrix[ ROW + 0 ][ COL - 1 ] != 0){  
                if( matrix[rr + 0][cc - 1]->getcondition() == "Sick" ){
                    sick++;
                }   
            }
        }
        if(ROW > 0){
            if(matrix[ ROW - 1 ][ COL + 0 ] != 0){ 
                if( matrix[rr - 1][cc + 0]->getcondition() == "Sick" ){
                    sick++;
                }   
            }
        }
        return sick;
}
