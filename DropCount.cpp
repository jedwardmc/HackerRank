#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class DropCount {
    int id;                 /* unique identifier for tree */
    string type;            /* the name of the tree */
    int pos;                /* the position of the tree */
    int quantity;           /* the quantity of fruit on the tree */
    
public:
    void setID(int i) { id = i; }
    void setType(string n) { type = n; }
    void setPos(int p) { pos = p; }
    void setQuantity(int q) { quantity = q; }
    int getID() const { return id; }
    string getType() const { return type; }
    int getPos() const { return pos; }
    int getQuantity() const { return quantity; }
};

int ppi, qqi;              /* integer forms of pp and qq */
int tcount;                /* tcount is the number of trees */
DropCount *dc_ptr;         /* global pointer to the dropcount class */
bool gl;                   /* status variable for fruit tree creation */
bool pl;                   /* status variable for print lock */
bool s;                    /* status variable for the loops */
char k;                    /* keyboard character pointer */

void getMenu() {
    printf("Welcome to the drop count program!\n\n");
    printf("Press the following keys to:\n");
    printf("\t G - create new fruit\n");
    printf("\t P - print summary of fruit\n");
    printf("\n Or press any key to quit...\n");
}

void glfunc() {
    
    FILE *db;
    char affirm;
    string tt;
    string pp;
    string qq;
    
    /*** for each instance increment tcount ***/
    tcount++;
    
    while(gl) {
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        printf("\nCreating a new tree...\n\n");
        
        /*** create a new drop count object ***/
        dc_ptr = new DropCount;
        
        /*** ask the user for a name ***/
        printf("Enter the name of the tree: ");
        getline(cin, tt);

        
        /*** check whether the user put in a name ****/
        if (tt.length() == 0) {
            printf("Error: you must enter a name!\n");
            continue;
        }
    
        printf("Enter the position of the tree: ");
        getline(cin, pp);
        
        /*** check whether the position input is not zero ***/
        if (pp.length() == 0) {
            printf("Error: you must enter a position integer!\n");
            continue;
        }
        
        /*** as usual we need to check whether the user entered something bad ***/
        try {
            ppi=stoi(pp);
        } catch(exception ppe) {
            printf("Error: you must enter an integer not a string.\n");
            continue;
        }
        
        printf("Enter the quantity of fruit: ");
        getline(cin, qq);
        
        /*** first check whether the quantity is not equal to zero ***/
        if (qq.length() == 0) {
            printf("Error: you must enter the quantity of fruit!\n");
            continue;
        }
    
        /*** then check whether the user entered an integer ***/
        try {
            qqi=stoi(qq);
        } catch (exception qqe) {
            printf("Error: you must enter an integer not a string.\n");
            continue;
        }
        
        /*** finally confirm everything is good with the user ***/
        
        printf("All good? (Y/N)\n");
        cin >> affirm;
        
        /*** close the loop and either go back to the main loop ***/
        if (affirm=='Y') {
            
            /*** tell the user what happened ***/
            printf("\n Adding the tree to the database...\n\n");
            
            /*** put the information into pointer ***/
            
            dc_ptr->setID(tcount);
            dc_ptr->setType(tt);
            dc_ptr->setPos(ppi);
            dc_ptr->setQuantity(qqi);
    
            /*** write the data to file ***/
            
            db = fopen ("db.txt", "w+");
            
            fprintf(db, "ID->%d Type->%s Pos->%d Quant->%d", dc_ptr->getID(), dc_ptr->getType().c_str(),
                                                        dc_ptr->getPos(), dc_ptr->getQuantity());
            
            fclose(db);
            /*** once this is done close the loop ***/
            gl=false;
        } else if (affirm=='N') {
            printf("\n Returning back to entry prompt...\n\n");
            gl=true;
        }
    }
    
    gl=false;
    
    
}


int main() {
    
   s = true;   /*** set the status bool to true ***/
    
    while (s) {
        getMenu();
        cin >> k;
        
        if (k == 'Q') s=gl=false;
        if (k == 'G') gl=true; glfunc();
    }
    
    return 0;
}
