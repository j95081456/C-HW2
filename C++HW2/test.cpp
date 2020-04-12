#include <iostream>

using namespace std;
class matrix;

int function(matrix puzzle[] , matrix map , int n , int puzzleterms[] , int mapterms, const int num);
int match(matrix a, matrix b , int terms1 ,int terms2);
int flag = 0;
int restart = 0;

class element {
    friend matrix;
    private : int col ,row ;
    //public : int col , row ;
};
class matrix{
    private : element elementAR[300] ;
              int rows , cols , terms ;
              int state_r = 0, state_c = 0;
    public : //matrix (int r , int c , int b);
             matrix();
             int getrow (int b);
             int getcol (int b);
             int getrows();
             int getcols();
             int get_terms();
             int get_state_r();
             int get_state_c();
             void setrc(int r , int c );
             void set_terms(int b);
             void set(int r ,int c ,int b);
             void set_state_rc(int r ,int c);
             void add(matrix a);

};
matrix::matrix(){
    //elemantAR[b].row = r;
    //elemantAR[b].col = c;
};
void matrix::set(int r , int c , int b){
    elementAR[b].row = r;
    elementAR[b].col = c;
};
void matrix::setrc(int r , int c ){
    rows = r;
    cols = c;
};
void matrix::set_terms(int b){
    terms = b;
};
void matrix::set_state_rc(int r ,int c){
    state_r = r;
    state_c = c;
};
void matrix::add(matrix a){
    for (int i = 0; i < a.get_terms() ; i++){
        //cout << terms << endl;
        elementAR[terms + i].row = a.getrow(i);
        elementAR[terms + i].col = a.getcol(i);
    }
    terms = terms + a.get_terms();
    //cout << terms << endl;
};
int matrix::get_terms(){
    return terms;
};
int matrix::getrows(){
    return rows;
};
int matrix::getcols(){
    return cols;
};
int matrix::getrow(int b){
    return elementAR[b].row;
};
int matrix::getcol(int b){
    return elementAR[b].col;
};
int matrix::get_state_r(){
    return state_r;
};
int matrix::get_state_c(){
    return state_c;
};

int main(){
    //matrix * puzzle = new matrix[10];
    int n,r,c;
    char piece;
    cin >> n ;
    //matrix * puzzle = new matrix[n];
    matrix puzzle[n];
    int b ;
    for (int i = 0; i < n; i++){
        b = 0;
        cin >> c;
        cin >> r;
        puzzle[i].setrc(r,c);
        for (int j = 0; j < r ; j++){
            
            for (int k = 0; k < c; k++){
                cin >> piece ;
                if (piece == 'O'){
                   puzzle[i].set(j,k,b);
                   b++;
                }
              //  cout << b << j << k << endl ;
            }
        }
        puzzle[i].set_terms(b);
    }
    int n1,r1,c1;
    char piece1;
    cin >> n1;
    //matrix * map = new matrix[n1];
    matrix map[n1] ;
    int b1;
    for (int i = 0; i < n1; i++){
        b1 = 0;
        cin >> c1;
        cin >> r1;
        map[i].setrc(r1 , c1);
        for (int j = 0; j < r1 ; j++){
            
            for (int k = 0; k < c1; k++){
                cin >> piece1 ;
                if (piece1 == 'O'){
                   map[i].set(j,k,b1);
                   b1++;
                }
                //cout << b1 << j << k << endl ;
            }
        }
        map[i].set_terms(b1);
      //  cout << map[i].getrow(0) << " qqqqq " << map[i].getcol(0) << endl ;
    }
    /*for (int i = 0; i < 6 ; i++){
        cout << map[0].getrow(i) << " qqqqq " << map[0].getcol(i) << endl ;
    }*/
    int mapcols,maprows;
    int puzzlecols[n] , puzzlerows[n];
    int mapterms ;
    int puzzleterms[n];
    int result;
    for (int i = 0; i < n ; i++){
        puzzleterms[i] = puzzle[i].get_terms();
    }
    for (int i = 0; i < n1 ; i++){ // n1 map
        //mapcols = map[i].getcols();
        //maprows = map[i].getrows();
        mapterms = map[i].get_terms(); 
        //cout << "gogo--" << n  << endl ;   
        result = function(puzzle , map[i] ,n ,puzzleterms,mapterms,n );
        //cout << "gogo" << endl ; 
        if (result == 1){
            cout << "Yes" << endl;
        }
        else{ cout << "No" << endl;}
        for (int j = 0; j < n ; j++){  
            for (int i = 0; i < puzzleterms[n-1]; i++){
            // cout << n-1 << endl;
                puzzle[j].set(puzzle[j].getrow(i) - puzzle[j].get_state_r()  , puzzle[j].getcol(i) - puzzle[j].get_state_c(), i ); // shift back
            //  cout << "**********2" << endl;
        }
            puzzle[j].set_state_rc(0,0);
        }       
    }
    
    //cout << puzzle[0].getrow(1) << puzzle[0].getcol(1) ;
}

int match(matrix a, matrix b , int terms1 ,int terms2){ //puzzle  map
    int c = 1;
   // cout << terms1 << " terms " << terms2 << endl;
    for (int i = 0; i < terms1; i++){
        for (int j = 0; j < terms2; j++){
            //cout << a.getrow(i) << a.getcol(i) << "a,b" << b.getrow(j) << b.getcol(j) << endl ;
            if ( (a.getcol(i) == b.getcol(j)) && (a.getrow(i) == b.getrow(j)) ){
                //cout << "not match" << endl;
                c = 0;
                break;
            }
        }
        if (c == 0){break;}
    }
    return c ;
}

int function(matrix puzzle[] , matrix map , int n , int puzzleterms[] , int mapterms ,const int num){ // n number of puzzle
    if ( n == 0 ){
        /*if (flag == 0) {
            cout << "gogo1" << endl ; 
            return 0;
            } 
        else*/ return 1;
    }
    else if (n == num+1){
       /// cout << "gogo2" << n << num << endl ; 
        return 0;
    }
    else {
        flag = 0;
        //int stored_j , stored_k;
        //cout << "jjjjjj" << endl ;
        //cout << map.getcol(0) <<"col and row" << map.getrow(0) << endl;
        //flag = match(puzzle[n-1], map, puzzleterms[n-1] , mapterms);
        //cout << "flag" << n-1 << flag << endl ; 
        while (flag == 0) {
           // cout << puzzle[n-1].get_state_r() << puzzle[n-1].get_state_c() << endl ;
            for (int j = puzzle[n-1].get_state_r(); j <= (map.getrows() - puzzle[n-1].getrows()) ; j++){
                for (int k = puzzle[n-1].get_state_c(); k <= (map.getcols() - puzzle[n-1].getcols()); k++){
                    for (int i = 0; i < puzzleterms[n-1]; i++){
                        puzzle[n-1].set(puzzle[n-1].getrow(i) + j, puzzle[n-1].getcol(i) + k , i ); // shift forward
                    }
                   // cout << "puzzle:" << n-1 << "  shift forward" << j << k << endl;
                    flag = match(puzzle[n-1], map, puzzleterms[n-1] , mapterms);
                    /*if ( (puzzle[n-1].get_state_r() == j) && (puzzle[n-1].get_state_c() == k) ){
                        if ( (puzzle[n-1].get_state_r() != 0) && (puzzle[n-1].get_state_c() != 0) ){
                            flag = 0;
                        }
                    }*/
                    if (restart == 1){
                        flag = 0;
                        restart = 0;
                    }
                    //cout << "flag" << flag << endl;
                    //cout << "**********1" << endl;
                    if (flag == 1){/*cout << "ya" << endl;*/
                         puzzle[n-1].set_state_rc(j , k );
                         break;
                    }
                    for (int i = 0; i < puzzleterms[n-1]; i++){
                        //cout << n-1 << endl;
                        puzzle[n-1].set(puzzle[n-1].getrow(i) - j , puzzle[n-1].getcol(i) - k , i ); // shift back
                      //  cout << "**********2" << endl;
                    }
                }
                if (flag == 1){/*cout << "ya2" << endl;*/ break;}    
            }
            if (flag == 1){/*cout << "ya3" << endl;*/ break;}
            else {
                for (int i = 0; i < puzzleterms[n-1]; i++){
                       // cout << n-1 << endl;
                        puzzle[n-1].set(puzzle[n-1].getrow(i) - puzzle[n-1].get_state_r()  , puzzle[n-1].getcol(i) - puzzle[n-1].get_state_c(), i ); // shift back
                      //  cout << "**********2" << endl;
                }
                puzzle[n-1].set_state_rc(0,0);
                map.set_terms(mapterms - puzzle[n].get_terms());
                mapterms = map.get_terms();
                restart = 1;
                return function(puzzle, map , n + 1 , puzzleterms , mapterms , num);
                }
        }
        map.add(puzzle[n-1]);
        mapterms = map.get_terms();
        //cout << "pass" << endl;
        for (int i = 0 ;i < map.get_terms(); i++){
            //cout << map.getrow(i) << map.getcol(i) << endl;
        }
        //cout << "flag" << flag << endl;
        return function(puzzle, map , n-1 , puzzleterms , mapterms , num);
        /*if (returnvalue == 0){
            return function(puzzle, map , n-1 , puzzleterms , mapterms ,state_r , state_c);
        }
        else (return 1;)*/
    }
}