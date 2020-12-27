#include <stdio.h>

#define MAX_STATES 50

struct States {
    int curState;
    char input;
    int nextState;
};
struct States arr[MAX_STATES]; //global variable

int fsmDef(FILE *def);

int fsmInputs(int a, FILE *inp);

int fsmProcess(int cur2, int b,struct States FSM[b], char input);

int test_fsmProcess();

int main(int argc, char *argv[]) {
    FILE *def; //definition of the fsm
    FILE *inp; //input stream
    int i;
    if (argc == 3) {
        def = fopen(argv[1], "r");
        inp = fopen(argv[2], "r");

        printf("processing FSM definition file %s\n", argv[1]);

        i = fsmDef(def);
        if (i == 0) {
            printf("did not process FSM file correctly\n");
            return (-1);
        }

        printf("starting fsm testing\n");
        if (test_fsmProcess()!=0){
            printf("test failed\n");
            return (-1);
        }
        else{
            printf("fsm tested successfully\n");
        }
        printf("FSM has %d transitions\n", i);
        printf("processing FSM inputs file %s\n", argv[2]);
        fsmInputs(i, inp);

        fclose(def);
        fclose(inp);

    } else {
        printf("incorrect number of files input on command line\n");
        return (-1);
    }
    return (0);
}

int fsmDef(FILE *def) {
    int c = 0;
    // assigns 3 variables to structure
    while (fscanf(def, "%d:%c>%d", &arr[c].curState, &arr[c].input, &arr[c].nextState) != EOF) {
        c += 1;
    }
    return (c); //number of transitions
}
int fsmProcess(int cur2, int b,struct States FSM[b], char input){
    int k;
    //b is the number of transitions in the FSM
    for (k = 0; k < b; k++) {
        //loops through the FSM to find the correct state to transition to with the given input
        if (FSM[k].curState == cur2 && (input == FSM[k].input)) {
            printf("input %c transitions from state %d to state %d \n", input, cur2, FSM[k].nextState);
            cur2 = FSM[k].nextState;
            break;
        }
    }
    //returns state that it transitioned to
    return cur2;
}
int fsmInputs(int a, FILE *inp) {
    char line2[256];
    int j = 0;
    int cur = 0;
    // loops through inputs in the file changing states using the fsmProcess function
    while(fscanf(inp,"%c",line2)!=EOF){
        cur=fsmProcess(cur, a, arr, line2[0]);
        j++;
    }
    printf("after %d steps, state machine finished successfully at state %d", j, cur);
    return (0);
}
int test_fsmProcess(){
    //creates mini fsm and tests that fsmProcess processes inputs correctly with that fsm
    struct States test[3];
    test[0].input='a';
    test[0].curState=0;
    test[0].nextState=3;

    test[1].input='b';
    test[1].curState=1;
    test[1].nextState=2;

    test[2].input='c';
    test[2].curState=2;
    test[2].nextState=0;
    int length= sizeof test;
    int e,j,k;

    e=fsmProcess(0, length,test,'a');
    j=fsmProcess(1,length,test,'b');
    k=fsmProcess(2,length,test,'c');
    if ((e==3) && (j==2) && (k==0)){
        return 0;
    }
    else {
        return -1;
    }
}
