#include<iostream>
#include<ctype.h>
#include<iomanip>

using namespace std;
int PLAN = 0;
int CUSTOMER  = 0;
int POSITION = 0;

class TrainingPlan{
    string name;
    int session;
    float feesPerWeek;
    float feesPerMonth;
    public:
        void swap(TrainingPlan &p1, TrainingPlan &p2){
            TrainingPlan swapped = p1;
            p1 = p2;
            p2 = swapped;
        }
        int partition(TrainingPlan arr[], int low, int high){
            TrainingPlan pivot = arr[high];
            int i = (low-1);
            for(int j=low; j<=high; j++){
                if(arr[j].getFeesPerWeek()<pivot.getFeesPerWeek()){
                    i++;
                    swap(arr[i], arr[j]);
                }
            }
            swap(arr[i+1], arr[high]);
            return (i+1);
        }
        void quickSort(TrainingPlan arr[], int low, int high){
            if(low < high){
                int pi = partition(arr, low, high);
                quickSort(arr, low, pi-1);
                quickSort(arr, pi+1, high);
            }
        }
        TrainingPlan(){
            this->name = "";
            this->session = 0;
            this->feesPerMonth = 0;
            this->feesPerWeek = 0;
        }
        TrainingPlan(string n, int s, float FPW, float FPM, TrainingPlan plans[]){
            this->name = n;
            this->session = s;
            this->feesPerWeek = FPW;
            this->feesPerMonth = FPM;
            PLAN++;
            quickSort(plans, 0, PLAN);
        }
        void setPlan(TrainingPlan plans[]){
            cout<<"Enter plan name : ";
            cin.get();
            getline(cin, this->name);
            cout<<"Enter sesion per week : ";
            cin>>this->session;
            feeLabel:
            cout<<"Enter fees per week(enter 0 if you consider adding fees per month) : ";
            cin>>this->feesPerWeek;
            cout<<"Enter fees per month(enter 0 if fees per week is already inputted) : ";
            cin>>this->feesPerMonth;
            // error checking 
            if(this->feesPerMonth > 0 && this->feesPerWeek > 0) {
                cout<<"You entered both values greather than 0.\n";
                cin.get();
                goto feeLabel;
            }
            cout<<"Successfully created a training plan("<<this->name<<")!\n";
            cin.get();
            PLAN++;
            quickSort(plans, 0, PLAN);
        }
        void updatePlan(){
            cout<<"Plan name("<<this->name<<") : \n";
            cout<<"Enter sessions per week ("<<this->session<<") : ";
            cin>>this->session;
            feeLabel:
            cout<<"Enter fees per week ("<<this->feesPerWeek<<") : ";
            cin>>this->feesPerWeek;
            cout<<"Enter fees per month ("<<this->feesPerMonth<<") : ";
            cin>>this->feesPerMonth;
            // error checking 
            if(this->feesPerMonth > 0 && this->feesPerWeek > 0) {
                cout<<"You entered both values greather than 0.\n";
                cin.get();
                goto feeLabel;
            }
            cout<<"Successfully updated the training plan("<<this->name<<")!\n";
            cin.get();
        } 
        // getter
        string getPlanName() {return this->name;}
        float getFeesPerWeek() {return this->feesPerWeek;}
        float getFeesPerMonth() {return this->feesPerMonth;}
        int getSessionsPerWeek() {return this->session;}
        void displayPlan(){
            cout<<setw(20)<<this->name
                <<setw(20)<<this->session
                <<setw(15)<<this->feesPerWeek
                <<setw(15)<<this->feesPerMonth;
        }
};
class Customer{
    string name;
    TrainingPlan trainingPlan;
    float currentWeight;
    // 0 - no private, 1 - online, 2 - offline
    int privateHours[4][5];
    string learntPoses[10];
    int learntPosesCount;
    float cost;
    public:
        Customer(){
            this->name = "";
            this->currentWeight = 0;
            this->cost = 0;
            this->learntPosesCount = 0;
            for(int i=0; i<4; i++)
                for(int j=0; j<5; j++) {
                    this->privateHours[i][j] = 0;
                }
        }
        Customer(string n, TrainingPlan tp, float w, int h[4][5]){
            this->name = n;
            this->trainingPlan = tp;
            this->currentWeight = w;
            this->cost = 0;
            for(int i=0; i<4; i++)
                for(int j=0; j<5; j++) {
                    this->privateHours[i][j] = h[i][j];
                }
            CUSTOMER++;
        }
        string setCustomer(TrainingPlan plans[]){
            int planIndex = 0;
            cout<<"Enter customer name : ";
            cin.get();
            getline(cin, this->name);

            trainingPlanLabel:
            cout<<"Enter training plan - Available plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > PLAN) goto trainingPlanLabel;
            cin>>planIndex;
            this->trainingPlan = plans[planIndex-1];

            cout<<"Enter current weight : ";
            cin>>this->currentWeight;
            // private hour adding
            for(int i=0; i<4; i++){
                cout<<"Enter"<<i+1<<" th/st week private hours(0 - no private, 1 - online, 2 - offline) : \n";
                for(int j=0; j<5; j++){
                    privateHourLabel:
                    cout<<"Week "<<i+1<<"Day "<<j+1<<" : ";
                    cin>>this->privateHours[i][j];
                    if(this->privateHours[i][j] < 0 || this->privateHours[i][j] > 2) goto privateHourLabel;
                }
            }
            CUSTOMER++;
            this->learntPosesCount = 0;
            return this->trainingPlan.getPlanName();
        }
        string updateCustomer(TrainingPlan plans[]){
            int planIndex = 0;
            cout<<"Customer name("<<this->name<<") : \n";

            trainingPlanLabel:
            cout<<"Enter training plan - Available plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > PLAN) goto trainingPlanLabel;
            cin>>planIndex;
            this->trainingPlan = plans[planIndex-1];

            cout<<"Enter current weight(kg) : ";
            cin>>this->currentWeight;

            this->learntPosesCount = 0;
            return this->trainingPlan.getPlanName();
        }
        void displayPoses(){
            cout<<setw(30)<<"Learnt poses : ";
            for(int i=0; i<this->learntPosesCount; i++){
                cout<<this->learntPoses[i];
                if(i+1!=this->learntPosesCount) cout<<" ,";
            }
        }
        void addLearntPoses(string poses[]){
            char learnt = 'y';
            int ind = 0;
            int learntInd = 0;
            cout<<"Already learnt poses? (y/n) : ";
            cin>>learnt;
            if(learnt=='y') {
                for(unsigned int i=0; i<poses->length(); i++){
                    cout<<"("<<i+1<<")"<<poses[i];
                    if(i+1 != poses->length()) cout<<" , ";
                }
                while(true){
                    char more = 'y';
                    cout<<"\nEnter pose index : ";
                    cin>>ind;
                    cout<<"Got more?(y/n) : ";
                    cin>>more;
                    this->learntPosesCount++;
                    this->learntPoses[learntInd] = poses[ind-1];
                    learntInd++;
                    if(more!='y') break;
                }
            }
            cout<<endl;
        }
        float getFinalCost(){
            int count = learntPosesCount;
            if(learntPosesCount > 5) count = 5;
            this->cost = 0;
            if(trainingPlan.getFeesPerMonth()!=0) this->cost += this->trainingPlan.getFeesPerMonth();
            else this->cost += this->trainingPlan.getFeesPerWeek()*4;
            
            for(int i=0; i<4; i++)
                for(int j=0; j<5; j++) {
                    if(this->privateHours[i][j]==1) cost += 15000;
                    else if(this->privateHours[i][j]==2) cost += 17000;
                }
            return this->cost - (this->cost*count)/100;
        }
        float getCost() {
            this->cost = 0;
            if(trainingPlan.getFeesPerMonth()!=0) this->cost += this->trainingPlan.getFeesPerMonth();
            else this->cost += this->trainingPlan.getFeesPerWeek()*4;
            
            for(int i=0; i<4; i++)
                for(int j=0; j<5; j++) {
                    if(this->privateHours[i][j]==1) cost += 15000;
                    else if(this->privateHours[i][j]==2) cost += 17000;
                }
            return this->cost;
        }
        void displayCustomer(){
            int online = 0, offline = 0;
            for(int i=0; i<4; i++)
                for(int j=0; j<5; j++) {
                    if(this->privateHours[i][j]==1) online++;
                    else if(this->privateHours[i][j]==2) offline++;
                }
            cout<<setw(20)<<this->name
                <<setw(20)<<this->trainingPlan.getPlanName()
                <<setw(10)<<this->currentWeight
                <<setw(20)<<this->learntPosesCount
                <<setw(15)<<online
                <<setw(15)<<offline
                <<setw(15)<<this->getFinalCost();
        }
        void displayCustomerDetails(){
            int online = 0, offline = 0;
            for(int i=0; i<4; i++)
                for(int j=0; j<5; j++) {
                    if(this->privateHours[i][j]==1) online++;
                    else if(this->privateHours[i][j]==2) offline++;
                }
            cout<<setw(30)<<"Customer name : "<<setw(20)<<name<<endl
                <<setw(30)<<"Weight : "<<setw(20)<<this->currentWeight<<endl
                <<setw(30)<<"Training plan : "<<setw(20)<<this->trainingPlan.getPlanName()<<endl;
            this->displayPoses();
            cout<<endl;

            cout<<setw(30)<<"Sessions per week : "<<setw(20)<<this->trainingPlan.getSessionsPerWeek();
            if(this->trainingPlan.getFeesPerMonth()!=0) {
                cout<<setw(20)<<this->trainingPlan.getFeesPerMonth();
            }
            else {
                cout<<setw(20)<<this->trainingPlan.getFeesPerWeek()*4;
            }
            cout<<endl;
            cout<<setw(30)<<"Private (Online-15000) : "
                <<setw(20)<<online<<setw(20)<<15000*online<<endl
                <<setw(30)<<"Private (Offline-17000) : "    
                <<setw(20)<<offline<<setw(20)<<17000*offline<<endl
                <<setw(30)<<"DISCOUNT (%) : "   
                <<setw(20)<<this->learntPosesCount<<setw(20)<<this->getCost()*this->learntPosesCount/100<<endl
                <<setw(30)<<"Total Cost : "<<setw(20)<<""<<setw(20)<<getFinalCost()<<endl;
            cin.get();
        }
};
class Position{
    string positionName;
    int poseCount;
    public:
        string poseType[10];
        string poseName[10];
        Position(){
            this->positionName = "";
            this->poseCount = 0;
        }
        Position(string name, string type[10], string names[10], int pc){
            this->poseCount = pc;
            this->positionName = name;
            for(int i=0; i<poseCount; i++){
                this->poseType[i] = type[i];
                this->poseName[i] = names[i];
            }
            POSITION++;
        }
        void addPosition(){
            cout<<"Position name : "<<this->positionName<<endl;
            cout<<"Positions \n";
            for(int i=0; i<poseCount; i++) {
                cout<<poseName[i];
                if(i+1 != poseCount) cout<<" , ";
                else cout<<endl;
            }
            if(poseCount == 10) {
                cout<<"10 poses already added\n";
                cin.get();
                return;
            }
            char more = 'y';
            while(true){
                if(poseCount==10) break;
                cin.get();
                cout<<"Enter position name("<<poseCount+1<<") : ";
                getline(cin,this->poseName[poseCount]);
                cout<<"Enter position type("<<poseCount+1<<") : ";
                getline(cin,this->poseType[poseCount]);
                cout<<"Successfully added("<<poseName[poseCount]<<")\n";
                poseCount++;

                moreLabel:
                cout<<"Add more?(y/n) : ";
                cin>>more;
                if(more=='n') break;
            }
            cin.get();
        }
        void createPosition(){
            POSITION++;
            cout<<"Enter position name : ";
            cin.get();
            getline(cin,this->positionName);
            this->poseCount = 0;
            addPosition();
        }
        void displayPosition(){
            cout<<setw(20)<<this->positionName<<endl;
            for(int i=0; i<poseCount; i++){
                cout<<setw(25)<<""
                    <<setw(30)<<this->poseType[i]
                    <<setw(30)<<this->poseName[i]
                    <<endl;
            }
        }
};
void displayTrainingPlans(TrainingPlan plans[]);
void displayYogaPositions(Position poses[]);
void displayCustomers(Customer customers[]);

int main(){
    int menuCode;
    
    Position poses[5];
    string basicPoseType[10] = 
        {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose",
        "Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string basicPoseNames[10] = 
        {"Archer Pose","Dolphin Pose","Frog Pose","Fallen Triangle","Big Toe Pose","Lion Pose",
        "Airplane Pose","Side Lunge","Side Reclining","Bird Dog Pose"};
    Position pose1("BASIC",basicPoseType,basicPoseNames,10);
    
    string imPoseType[10] = 
        {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose",
        "Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string imPoseNames[10] = 
        {"Downward Facing Pose","Mountain Pose","Warrior Pose","Traingle Triangle","Low Lunge",
        "Tree Pose","Plank Pose","Bridge Lunge","Staff Pose","Cobbler's Pose"};
    Position pose2("INTERMEDIATE",imPoseType,imPoseNames,10);
    
    poses[0] = pose1;
    poses[1] = pose2;
    
    TrainingPlan plans[7];
    TrainingPlan basicMonth("BASIC",3,0,100000,plans);
    TrainingPlan basic("BASIC",3,25000,0,plans);
    TrainingPlan inter("INTERMEDIATE",3,35000,0,plans);
    TrainingPlan advan("ADVANCED",2,50000,0,plans);
    plans[0] = advan;
    plans[1] = inter;
    plans[2] = basic;
    plans[3] = basicMonth;

    Customer customers[50];
    int h1[4][5] = {{0,1,0,1,2},{1,2,0,0,0},{0,0,0,2,2},{0,0,0,1,1}};
    int h2[4][5] = {{0,0,0,1,2},{1,0,0,0,1},{0,0,0,1,2},{2,0,0,1,1}};
    int h3[4][5] = {{0,0,0,1,0},{1,2,0,0,0},{0,0,0,2,2},{0,0,0,1,1}};
    int h4[4][5] = {{0,1,0,1,1},{1,2,0,0,1},{0,1,0,2,2},{0,0,0,1,1}};
    int h5[4][5] = {{0,1,0,1,0},{1,2,0,0,0},{0,0,0,2,2},{1,0,0,1,1}};
    Customer c1("Han Myo Htet",plans[0],55,h1);
    Customer c2("Myo Min Thu",plans[0],60,h2);
    Customer c3("Thiha",plans[1],56,h3);
    Customer c4("Min Thu kha",plans[1],66,h4);
    Customer c5("Ye Htet Naing",plans[1],48,h5);
    customers[0] = c1;
    customers[1] = c2;
    customers[2] = c3;
    customers[3] = c4;
    customers[4] = c5;

    menuLabel:
    system("clear");
    cout<<"\n\n\n\n\n==============================================================\n"
        <<setw(50)<<"Welcome from Amazing Sport Yoga System!\n"
        <<"==============================================================\n";
    cin.get();
    system("clear");
    cout<<"\n1. Training plan menu\n2. Yoga poses menu\n3. Customers menu\n0. Quit program\n";
    cin>>menuCode;
    if(menuCode==1) {
        trainingPlanScreenLabel:
        system("clear");
        int trainingPlanMenuCode = 0;
        cout<<"1. Add a training plan."
            <<"\n2. Show all training plans."
            <<"\n3. Update a training plan."
            <<"\n0. Return to main screen.\n";
        cin>>trainingPlanMenuCode;
      
        if(trainingPlanMenuCode < 0 || trainingPlanMenuCode > 3) goto trainingPlanScreenLabel;
        //Quit to main menu
        if(trainingPlanMenuCode == 0) goto menuLabel;
        //Create a plan
        else if(trainingPlanMenuCode == 1) {
            plans[PLAN].setPlan(plans);
            cin.get();
        }
        //Show all plans
        else if(trainingPlanMenuCode == 2) {
            displayTrainingPlans(plans);
            cin.get();
            cin.get();
        }
        //Update a certain plan
        else if(trainingPlanMenuCode == 3) {
            int index = 0;
            displayTrainingPlans(plans);
            cout<<"Enter number to update : ";
            cin>>index;
            plans[index-1].updatePlan();
            cin.get();
        }
        goto trainingPlanScreenLabel;
    } 
    else if(menuCode==2){
        yogaPoseScreenLabel:
        system("clear");
        int yogaPoseScreenCode = 0;
        cout<<"1. Add a yoga plan."
            <<"\n2. Display yoga plans."    
            <<"\n3. Add yoga poses."    
            <<"\n0. Return to main screen.\n";
        cin>>yogaPoseScreenCode;
        if(yogaPoseScreenCode < 0 || yogaPoseScreenCode > 3) goto yogaPoseScreenLabel;
      
        //Quit to main menu
        if(yogaPoseScreenCode == 0) goto menuLabel;
        //Add a new yoga
        else if(yogaPoseScreenCode == 1) {
            poses[POSITION].createPosition();
            cin.get();
        }
        //Display yoga plans
        else if(yogaPoseScreenCode == 2) {
            displayYogaPositions(poses);
            cin.get();
            cin.get();
        }
        //Add yoga poses
        else if(yogaPoseScreenCode == 3) {
            int index = 0;
            displayYogaPositions(poses);
            cout<<"\nEnter yoga plan index to add : ";
            cin>>index;
            poses[index-1].addPosition();
            cin.get();
        }
        goto yogaPoseScreenLabel;
    }
    else if(menuCode==3){
        customerScreenLabel:
        system("clear");
        int customerScreenCode = 0;
        cout<<"1. Register a new customer." 
            <<"\n2. Update customer info."  
            <<"\n3. View all customers."    
            <<"\n4. Calculate costs for the customer."  
            <<"\n0. Return to main screen. \n";
        cin>>customerScreenCode;
        if(customerScreenCode < 0 || customerScreenCode > 4) goto customerScreenLabel;
      
        //Quit to main menu
        if(customerScreenCode == 0) goto menuLabel;
        //Register a new customer
        else if(customerScreenCode == 1) {
            string planName = customers[CUSTOMER].setCustomer(plans);
            if(planName == "INTERMEDIATE") customers[CUSTOMER-1].addLearntPoses(basicPoseNames);
            else if(planName == "ADVANCED") customers[CUSTOMER-1].addLearntPoses(imPoseNames);
            customers[CUSTOMER-1].displayCustomerDetails();
            cin.get();
        }
        //Update customers
        else if(customerScreenCode == 2) {
            int index = 0;
            displayCustomers(customers);
            cout<<"Enter number to update : ";
            cin>>index;
            string planName = customers[index-1].updateCustomer(plans);
            if(planName == "INTERMEDIATE") customers[CUSTOMER-1].addLearntPoses(basicPoseNames);
            else if(planName == "ADVANCED") customers[CUSTOMER-1].addLearntPoses(imPoseNames);
            cin.get();
        }
        //Display all customers
        else if(customerScreenCode == 3) {
            displayCustomers(customers);
            cin.get();
            cin.get();
        }
        else if(customerScreenCode == 4) {
            int index = 0;
            displayCustomers(customers);
            cout<<"Enter number to calculate costs : ";
            cin>>index;
            customers[index-1].displayCustomerDetails();
            cin.get();
        }
        goto customerScreenLabel;
    }
    else if(menuCode==0) return 0;
    else goto menuLabel;
}

void displayTrainingPlans(TrainingPlan plans[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Plan name"
        <<setw(20)<<"Session per week"
        <<setw(15)<<"Fees per week"
        <<setw(15)<<"Fees per month"
        <<endl;
    for(int i=0; i<PLAN; i++) {
        cout<<setw(5)<<i+1;
        plans[i].displayPlan();
        cout<<endl;
    }
}

void displayYogaPositions(Position poses[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Position names"
        <<setw(30)<<"Pose type"
        <<setw(30)<<"Pose name"
        <<endl;
    for(int i=0; i<POSITION; i++) {
        cout<<setw(5)<<i+1;
        poses[i].displayPosition();
        cout<<endl;
    }
}
void displayCustomers(Customer customers[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Customer name"
        <<setw(20)<<"Training plan"
        <<setw(10)<<"Weight"
        <<setw(20)<<"Learnt poses count"
        <<setw(15)<<"Online hour"
        <<setw(15)<<"Offline hour"
        <<setw(15)<<"Total cost"
        <<endl;
    for(int i=0; i<CUSTOMER; i++) {
        cout<<setw(5)<<i+1;
        customers[i].displayCustomer();
        cout<<endl;
    }
}