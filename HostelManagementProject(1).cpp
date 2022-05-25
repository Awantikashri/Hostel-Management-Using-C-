/* Program To Manage Hostel.
    The Hostel in this program has 1 Mess and 2 Blocks- Attached Washroom & Non Attahed washroom.
    Each Block has 5 Floors and 10 Rooms in each Floor.
    Hostel and Blocks have Staff and Students.

    Basic Functions of Program ( Overview )
        - Login For Manager :  Manager can View Rooms,register new Student,allot Room and Update Fees.
        - Login For Warden :  Warden can View Rooms, manage staff,register new Student and allot Room.

    Other Features Of Program
        * Encrypts password of Manager and Warden in the file
        * Automatically assigns Room Number with given floor and total no of rooms(Eg : 101-1st room is 1st floor,302 - 2nd room in 3rd Floor)
        * Assigns unique ID to each registered student ( sn )
*/

#include <iostream>
#include<stdio.h>
#include <cstdlib>
#include<fstream>
#include<math.h>
#include <stdexcept>
#define displaywidth 70

using namespace std;

class UserException
{
public:
    (7)
    int id;
    string error_msg;
    UserException(int id,string error_msg)
    {
        this->error_msg = error_msg;
        this->id=id;
    }
    void putMessage()
    {
        cout<<"Error "<<id<<"\t"<<error_msg<<endl;
    }
};

class InvalidChoice: public UserException
{
public:
    InvalidChoice():UserException(01,"Invalid Choice.")
    {}  
};

class InvalidData:public UserException
{
public:
    InvalidData(string error_msg):UserException(02,error_msg)
    {}
};

class Date
{
private:
    int d,m,y;
public:
    Date()
    {}
    Date(int d,int m,int y)
    {
        this->d = d;
        this->m = m;
        this->y = y;
    }
    void putDate()
    {
        cout<<d<<"/"<<m<<"/"<<y<<endl;
    }
};
class Student
{
public:
    int id;
    string name;
    string address;
    string college;
    string degree;
    int year;
    friend class Date;

    Student():id(0),name(" ")
    {}
    Student(int id,string name,string address,string college,string degree,int year,Date dateOfAdmission)
    {
        this->id = id;
        this->name = name;
        this->address = address;
        this->degree = degree;
        this->dateOfAdmission = dateOfAdmission;
        this->year = year;
    }
    void putStudent()
    /*Displays details of student */
    {
        cout<<"ID: "<<id<<"\tName: "<<name<<"\tAddress:"<<address<<"\tDate Admitted: "<<endl;
        dateOfAdmission.putDate();
        cout<<"College Details:\t";
        cout<<college<<"Degree: "<<degree<<"\tYear: "<<year<<endl;
        cout<<"\n------------------------------------------------\n";
    }
};

class Staff
{
public:

    float salary;
    int id;
    string name;

    Staff():id(0)
    {}
    Staff(int id,string name)
    {
        this->id = id;
        this->name = name;
    }
    void putStaff()
    /*Dispalys staff details*/
    {
        cout<<"ID: "<<id<<"\tName: "<<name;
    }

};

class Warden:public Staff
{
public:
    Warden()
    {}
    Warden(int id,string name):Staff(id,name)
    {
        this->salary= 190000;
    }
};

class Manager:public Staff
{
public:
    string shift;
    Manager():shift(" ")
    {}
    Manager(int id,string name,string shift):Staff(id,name)
    {
        this->shift = shift ;
        salary =  120000;
    }
    void putStaff()
    {
        Staff::putStaff();
        cout<<"\tSHIFT : "<<shift;
    }
};

class Helper:public Staff
{
public:
    string shift;
    Helper():shift(" ")
    {}
    Helper(int id,string name,string shift):Staff(id,name)
    {
        this->shift = shift ;
        salary =  60000;
    }
    void putStaff()
    {
        Staff::putStaff();
        cout<<"\tSHIFT : "<<shift;
    }

};

class Security:public Staff
{
    public:
    string shift;
    Security():shift(" ")
    {}
    Security(int id,string name,string shift):Staff(id,name)
    {
        this->shift = shift ;
        salary =  45000;
    }
    void putStaff()
    {
        Staff::putStaff();
        cout<<"\tSHIFT : "<<shift;
    }
};

class Bed
{
public:
    int id;
    int status;
    float feesGiven;
    Student s; //Bed has Student

    Bed():id(0),status(0)
    {}
    Bed(int id)
    {
        this->id = id;
        status = 0;
        /*status = 0 indicates bed is not occupied*/
    }
    void addStudent(Student s)
    /*Gives bed to the Student s*/
    {
        this->s = s;
        status = 1;
        /*status = 1 indicates bed is occupied*/
        this->feesGiven = 0;
    }
    void putBed()
    //Displays details of available bed
    {
        if(status==0)
            cout<<"| "<<id<<" |\t"; //If bed is available show it's ID otherwise don't
        else
            cout<<"|   |\t";
    }
    void manageStudentFees(float feesGiven)
    /*Updates the fees details of student */
    {
        this->feesGiven += feesGiven;
        cout<<"Fees is updated.";
    }

};

class Room
{
public:
    Bed b[3]; //Room has 3 Bed
    int id; //id is the Room Number of Room

    Room():id(0)
    {}
    Room(int id)
    {
        this->id=id;
        Bed b1(0),b2(1),b3(2);
        b[0]=b1;
        b[1]=b2;
        b[2]=b3;
    }
    void allotBed(int bedID,Student s)
    /*Gives bed b with ID= bedID to the Student s*/
    {
        b[bedID].addStudent(s);
    }
    void putRoom()
    /*Displays details of Room No and its available beds*/
    {
        cout<<id<<"\t";
        b[0].putBed();
        b[1].putBed();
        b[2].putBed();
    }

};

class Block
{
public:
    int id;             //id is block number of Block
    int noOfFloor;      //# of floors in block
    int noOfRooms;      //# of rooms in each floor
    float fees;

    Room *room;//Block has Room

    /*Staff in Block*/
    Manager managers[3];
    Helper helpers[6];
    Security blockSecurity[2];


    Block():id(0)
    {}
    Block(int id,int nF,int nR,Manager managers[],Helper helpers[],Security blockSecurity[])
    {
        this->id = id;
        noOfFloor = nF;
        noOfRooms = nR;
        for(int i=0 ;i<3 ;i++)
        {
            this->managers[i]=managers[i];
        }
        for(int i=0 ;i<6 ;i++)
        {
            this->helpers[i]=helpers[i];
        }
         for(int i=0 ;i<2 ;i++)
        {
            this->blockSecurity[i]=blockSecurity[i];
        }

    }
    int findRoomIndex(int roomID)
    /*Finds the index i of room from the given room Number*/
    {
        for(int i=0;i<noOfRooms*noOfFloor;i++)
        {
            if(roomID == room[i].id)
                return i;
        }
        return -1;
    }
    void allotRoom(int roomID,int bedID,Student s)
    /*Gives a room with room#= roomID and bed#=bedID to a Student s*/
    {
        int i;
        i=findRoomIndex(roomID);
        room[i].allotBed(bedID,s);
    }
    void putBlock()
    /*Displays complete details of block*/
    {
      cout<<"ID : "<<id<<"\tFloors : "<<noOfFloor<<"\tROOMS : "<<noOfRooms<<endl;
      cout<<"\n________________( AVAILABLE ROOMS )_________________\n";
      cout<<"Room#\tBed0\tBed1\tBed2\n";
        for(int i=0;i<noOfFloor*noOfRooms;i++)
        {
            room[i].putRoom();
            cout<<endl;
        }
    }
    void putBlockStaff()
    /*Displays details of Block Staffs*/
    {
      cout<<"____________STAFF IN THE BLOCK_____________\n";
      cout<<"MANGERS :\n";
      for(int i=0;i<3;i++)
      {
        managers[i].putStaff();
        cout<<endl;
      }
      cout<<"............................................\n";
      cout<<"HELPERS:\n";
      for(int i=0;i<6;i++)
      {
        helpers[i].putStaff();
        cout<<endl;
      }
      cout<<"............................................\n";
      cout<<"BLOCK SECURITY:\n";
      for(int i=0;i<2;i++)
      {
        blockSecurity[i].putStaff();
        cout<<endl;
      }
    }

};
class AttachedWSBlock:public Block
{
public:
    AttachedWSBlock()
    {}
    AttachedWSBlock(int id,int nF,int nR,Manager managers[],Helper helpers[],Security blockSecurity[]):Block(id,nF,nR,managers,helpers,blockSecurity)
    {
        this->fees = 55000;
        /* Fees for Rooms with attached washroom is Rs.55000 */

        room = new Room[nF*nR];
        /* Creating rooms with the given #Floors and #RoomsInEachFloor */

        int roomcount=-1;

        for(int i=1;i<=nF;i++)
        {
            for(int j=1;j<=nR;j++)
            {
                roomcount++;
                Room r((i*100)+j);
                /*Creating Room r with room ID = 100*i + j (101-110, 201-210.....) */

                room[roomcount]=r;
                /*Storing details of r in Block's Room */
            }
        }
    }
};
class NonAttachedWSBlock:public Block
{
    public:
    NonAttachedWSBlock()
    {}
    NonAttachedWSBlock(int id,int nF,int nR,Manager managers[],Helper helpers[],Security blockSecurity[]):Block(id,nF,nR,managers,helpers,blockSecurity)
    {
        this->fees = 35000;
        /* Fees for Rooms with no attached washroom is Rs.35000 */

        room = new Room[nF*nR];
        /* Creating rooms with the given #Floors and #RoomsInEachFloor */

        int roomcount=-1;
        for(int i=1;i<=nF;i++)
        {
            for(int j=1;j<=nR;j++)
            {
                roomcount++;
                Room r((i*100)+j);
                /*Creating Room r with room ID = 100*i + j (101-110, 201-210.....) */

                room[roomcount]=r;
                /*Storing details of r in Block's Room */
            }
        }
    }
};
class Mess
{
    public:
    int id; //Mess Number of the mess

    /*Staff in Mess */
    Manager manager;
    Helper helpers[3];

    Mess()
    {}
    Mess(int id,Manager manager,Helper helpers[])
    {
        this->id=id;
        this->manager=manager;
        for(int i=0;i<3;i++)
        {
            this->helpers[i]=helpers[i];
        }
    }
    void putMess()
    /* Display Complete Mess details */
    {
        cout<<"\n=================== MESS ===========================\n";
        cout<<"MESS #:"<<id<<endl;;
        cout<<"______Manager______\n";
        manager.putStaff();
        cout<<"______Helpers_______\n"<<endl;
        for(int i=0;i<3;i++)
        {
            helpers[i].putStaff();
        }
        cout<<"\n===================================================\n";

    }

};
class Hostel
{
public:
    int id; //Unique identification no. of Hostel
    string name; //Hostel's Name

    /* Hostel has Block */
    AttachedWSBlock ab;
    NonAttachedWSBlock nab;

    /* Hostel has Staff */
    Security hostelSecurity[4];
    Warden warden;

    /* Hostel has Mess */
    Mess mess;

    Hostel()
    {}
    Hostel(int id,string name,AttachedWSBlock ab,NonAttachedWSBlock nab,Warden warden,Security hostelSecurity[],Mess m)
    {
        this->id = id;
        this->name = name ;
        this->ab = ab;
        this->nab = nab;
        for(int i=0;i<4;i++)
            {
                this->hostelSecurity[i]=hostelSecurity[i];
            }
        this->warden = warden;
        this->mess=m;
    }
    void allotABlock(int blockID,int roomID,int bedID,Student s)
    /* To allot Attached WR Block to a Student s */
    {
        ab.allotRoom(roomID,bedID,s);
    }

    void allotNABlock(int blockID,int roomID,int bedID,Student s)
    /* To allot NonAttached WR Block to a Student s */
    {
         nab.allotRoom(roomID,bedID,s);
    }

    void putHostelRoom()
    /* Display Details of Rooms available in Block*/
    {
        cout<<"\n___________________ATTACHED WASHROOM BLOCK________________________\n";
        ab.putBlock();
        cout<<"\n___________________NON ATTACHED WASHROOM BLOCK________________________\n";
        nab.putBlock();
    }
    void putHostelDetail()
    /* To display Details of Hostel , it's Staff and Mess */
    {
        cout<<"\n======================= "<<name<<" Hostel =================================\n";
        cout<<"\t|________WARDEN_________|\n";
        warden.putStaff();
        cout<<endl;
        cout<<"\t|_____HOSTEL__SECURITY__|"<<endl;
        for(int i=0;i<4;i++)
            {
                hostelSecurity[i].putStaff();
                cout<<endl;
            }
        cout<<"========================= MESS =============================\n"<<endl;
        mess.putMess();
        cout<<"------------------------------------------------------------\n";
    }
};


int sn=-1;  //student's count


Student registerStudent()
/*To register new Student  */
{
    string sname,saddress,scollege,sdegree,date;
    int d,m,y;
    int year;

    sn++;

    cout<<"Enter Name of Student\n";
    cin>>sname;

    cout<<"Enter Address of Student\n";
    cin>>saddress;

    cout<<"Enter College Name ( Eg: KLETech )\n";
    cin>>scollege;

    cout<<"Enter Degree(B.Tech/B.Arch/B.Com/M.Com/B.Pharma) and current Year( 1/2/3/4 )\n";
    cin>>sdegree>>year;

    cout<<"Enter Date of Registration( Eg: 12/05/2020 )\n";
    cin>>d>>m>>y;
    Date dateOfAdmission(d,m,y);

    Student s(sn,sname,saddress,scollege,sdegree,year,date);

    cout<<"Student Registered! with ID: "<<sn<<endl;
    return s;
}


Hostel allotHostelRoom(Student s,Hostel h)
/* To allot a room in a hostel to a new-registered student */
{
    int ch,roomNo,bed,roomIndex;
    cout<<"Enter 1 for AttachedWSBlock 2 for NonAttachedWSBlock\n";
    try
    {
        cin>>ch;
        if(ch<1 or ch>2)
            throw InvalidChoice();
        else
        {
            cout<<"Enter Room Number\n";
            cin>>roomNo;
            if(ch==1)
            {
                try
                {
                    /* Find index of given room number */
                   roomIndex=h.ab.findRoomIndex(roomNo);
                   if(roomIndex>=0 and roomIndex<=h.nab.noOfFloor*h.nab.noOfRooms and roomNo>100 and roomNo<100*h.ab.noOfFloor)
                   {
                        h.ab.room[roomIndex].putRoom();
                        cout<<"SELECT BED\n";
                        cin>>bed;
                        /* Check if the given bed# is valid */
                        if(bed>=0 && bed<=2)
                            h.allotABlock(0,roomNo,bed,s);
                        else
                            cout<<"Invalid Bed No. Room Can't be alotted. Try Again\n";
                   }
                   else
                    /* If the room No entered is not present in Database */
                   {
                        throw InvalidData("Entered Room No is not valid! Try Again\n");
                   } 
                }
                catch(InvalidData& id_error)
                {
                    id_error.putMessage();
                }       
            }
            if(ch==2)
            {
                try
                {
                    /* Find index of given room number */
                   roomIndex=h.nab.findRoomIndex(roomNo);
                   if(roomIndex>=0 and roomIndex<=h.nab.noOfFloor*h.nab.noOfRooms and roomIndex>=0 and roomNo>100 and roomNo<100*h.nab.noOfFloor)
                   {
                        h.nab.room[roomIndex].putRoom();
                        cout<<"SELECT BED\n";
                        cin>>bed;
                        /* Check if the given bed# is valid */
                        if(bed>=0 && bed<=2)
                            h.allotNABlock(1,roomNo,bed,s);
                        else
                            cout<<"Invalid Bed No. Room Can't be alotted. Try Again\n";
                   }
                   else
                   {
                        throw InvalidData("Entered Room No is not valid! Try Again\n");
                   } 
                }
                catch(InvalidData& id_error)
                {
                    id_error.putMessage();
                }
            }
        }
    }
    catch(InvalidChoice& ic_error)
    {
        ic_error.putMessage();
    }
    return h;
}

void displayAllStudent(Hostel h)
{
    cout<<"=================== AttachedWSBlock =======================\n";
    cout<<"|________________________________________________________|\n";
    for(int i=0;i<=h.ab.noOfRooms*h.ab.noOfFloor;i++)
    /* Check each rooms in each floor of attached wr block*/
    {
        for(int j=0;j<3;j++)
        {
            /* If the room is occupied display details of student who has occupied */
            if(h.ab.room[i].b[j].status==1)
                h.ab.room[i].b[j].s.putStudent();
        }
    }
    cout<<"=================== NonAttachedWSBlock  =======================\n";
    cout<<"|________________________________________________________|\n";
    for(int i=0;i<=h.nab.noOfRooms*h.nab.noOfFloor;i++)
    /* Check each rooms in each floor of non-attached wr block*/
    {
        for(int j=0;j<3;j++)
        {
            /* If the room is occupied display details of student who has occupied */
            if(h.nab.room[i].b[j].status==1)
                h.nab.room[i].b[j].s.putStudent();
        }
    }
}


int findStudentRoom(Hostel h,int s_id,int block_id)
/* Find room index of room occupied by student with id=s_id in Hostel h */
{
    if(block_id==1) //For Attached Washroom Block
    {
        for(int i=0;i<h.ab.noOfFloor*h.ab.noOfRooms;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(h.ab.room[i].b[j].status==1)
                {
                    if(h.ab.room[i].b[j].s.id==s_id)
                    {
                    return i; /*If matching room index is found*/
                    }
                }
            }
        }
    }
    if(block_id==2) //For Non-Attached Washroom Block
    {
        for(int i=0;i<h.nab.noOfFloor*h.nab.noOfRooms;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(h.nab.room[i].b[j].status==1)
                {
                    if(h.nab.room[i].b[j].s.id==s_id)
                    {
                    return i; /*If matching room index is found*/
                    }
                }
            }
        }
    }

    return -1; /*If no matching room index is found*/
}
int findStudentBed(int s_id,Hostel h,int r,int block_id)
/*To find bed# of a student from given Hostel h,Room r, Block_id */
{
    if(block_id == 1)//For Attached Washroom Block
    {
        for(int i=0;i<3;i++)
        {
            if(h.ab.room[r].b[i].status == 1)
            {
                if(h.ab.room[r].b[i].s.id == s_id)
                {
                    return i; /*If matching bed id is found*/
                }

            }
        }
    }
    if(block_id == 2)//For Non-Attached Washroom Block
    {
        for(int i=0;i<3;i++)
        {
            if(h.nab.room[r].b[i].status == 1)
            {
                if(h.nab.room[r].b[i].s.id == s_id)
                {
                    return i; /*If matching bed id is found*/
                }

            }
        }
    }
    return -1;/*If no matching bed# is found*/
}
void displayFeesDetails(Hostel h,int r,int b,int block)
/*To display Fees Details of student who occupies Hostel h,room index r,bed no b,block id=block*/
{
    if(block==1)//Attached WR block
    {
        cout<<"======================= STUDENT ==============================\n";
        /* Display Student's Detail */
        h.ab.room[r].b[b].s.putStudent();

         /* Display Room's Detail */
        cout<<"________________ROOM DETAILS__________________\n";
        cout<<"Room Type : 3A\tRoom#: "<<h.ab.room[r].id<<"\tBed#:"<<h.ab.room[r].b[b].id<<endl;

        /* Displays Fees information of student who has occupied that bed */
        cout<<"________________FEES DETAILS__________________\n";
        cout<<"Amount Paid: Rs. "<<h.ab.room[r].b[b].feesGiven<<"\tBalance :"<<h.ab.fees-h.ab.room[r].b[b].feesGiven<<endl;
    }
    if(block==2)//Non-Attached WR block
    {
        cout<<"======================= STUDENT ==============================\n";
        /* Display Student's Detail */
        h.nab.room[r].b[b].s.putStudent();

         /* Display Room's Detail */
        cout<<"________________ROOM DETAILS__________________\n";
        cout<<"Room Type : 3A\tRoom#: "<<h.nab.room[r].id<<"\tBed#:"<<h.nab.room[r].b[b].id<<endl;

        /* Displays Fees information of student who has occupied that bed */
        cout<<"________________FEES DETAILS__________________\n";
        cout<<"Amount Paid: Rs. "<<h.nab.room[r].b[b].feesGiven<<"\tBalance :"<<h.nab.fees-h.ab.room[r].b[b].feesGiven<<endl;
    }
}
void updatefees(Hostel h,int r,int b,int bl)
/* To update feesGiven by the student who has occupied block bl,room r and bed b*/
{
    float amt,new_bal;

    cout<<"Enter amount to update\n";
    cin>>amt;
    if(bl==1)//For attached wr block
    {
        /*Check for Validation of entered amount */
        if(amt>h.ab.fees || amt<=0)
            cout<<"Error! Not a valid Amount\n";
        else
        {
            h.ab.room[r].b[b].manageStudentFees(amt);

            /* Check for validation of updated fees amount new_bal */
            new_bal=h.ab.fees - h.ab.room[r].b[b].feesGiven;
            if(new_bal > h.ab.fees)
            {
                cout<<"Amount is exceeding Room rate\n";
                h.ab.room[r].b[b].manageStudentFees(-1*amt);
            }
            else
                cout<<"New Balance is "<<new_bal<<endl;
        }
    }
    if(bl==2)//For Non-attached wr block
    {
        /*Check for Validation of entered amount */
        if(amt>h.nab.fees || amt<=0)
            cout<<"Error! Not a valid Amount\n";
        else
        {
            h.nab.room[r].b[b].manageStudentFees(amt);

            /* Check for validation of updated fees amount new_bal */
            new_bal=h.nab.fees - h.nab.room[r].b[b].feesGiven;
            if(new_bal > h.ab.fees)
            {
                cout<<"Amount is exceeding Room rate\n";
                h.nab.room[r].b[b].manageStudentFees(-1*amt);
            }
            else
                cout<<"New Balance is "<<new_bal<<endl;
        }
    }
}
Hostel manageStudentFees(Hostel h)
/* To Display and Update Fees Details of Student in Hostel h*/
{
    int ch,id,bedid,newch;
    int room,bed;

    cout<<"Enter Student ID\n";
    cin>>id;

    cout<<"Enter (1)AttachedWSBlock (2)NonAttachedWSBlock\n";
    cin>>ch;
    if(ch==1)
    {
        /* Find Hostel,Room,Bed of student with id=id */
        room=findStudentRoom(h,id,1);

        /*If no matching student is found */
        if(room==-1)
            return h;

        bed=findStudentBed(id,h,room,1);

        /*If no matching student is found */
        if(bed==-1)
            return h;

        displayFeesDetails(h,room,bed,1);

        /* Check for update fees */
        cout<<"Do you wish to update Balance? (1)Yes (2)No\n";
        cin>>newch;
        if(newch==1)
            updatefees(h,room,bed,1);
         else
            return h;

    }
    else if(ch == 2)
    {
        /* Find Hostel,Room,Bed of student with id=id */
        room=findStudentRoom(h,id,2);

        /*If no matching student is found */
        if(room==-1)
            return h;

        bed=findStudentBed(id,h,room,2);

        /*If no matching student is found */
        if(bed==-1)
            return h;

        displayFeesDetails(h,room,bed,2);

        /* Check for update fees */
        cout<<"Do you wish to update Balance? (1)Yes (2)No\n";
        cin>>newch;
        if(newch==1)
            updatefees(h,room,bed,2);
         else
            return h;
    }
    else
    {
        cout<<"Invalid Choice\n";
    }
    return h;
}

Hostel hostelManagerLogin(Hostel h)
{
    Student s;
    cout<<"\n----------.---------- * * MANAGER PORTAL * * -----------.----------.\n";
    int ch;
    while(1)
    {
        try
        {
            cout<<"\n\n\t___________SELECT___________\n\t(1)DISPLAY ALL Rooms\n\t(2)Register New Student\n\t(3)MANAGE Existing Student\n\t(4)EXIT\n";
            cin>>ch;
            if(ch>0 and ch<5)
            {
                switch(ch)
                {
                    case 1: /*Display List of available rooms in Hostel*/
                            h.putHostelRoom();
                            break;

                    case 2: /* Take Details of new Student s */
                            s=registerStudent();

                            /* Allot Hostel h to Student s*/
                            h=allotHostelRoom(s,h);
                            break;

                    case 3:/* Mange existing students */
                            cout<<"\n\n\t___________SELECT___________\n\t(1)DISPLAY All Registered Students\n\t(2)MANAGE Particular Student\n\t(3)EXIT\n";
                            int choice;
                            cin>>choice;
                            switch(choice)
                            {
                                case 1:/* Display all the Students who have occupied beds in Hostel h */
                                        displayAllStudent(h);
                                        break;

                                case 2:/* Display and Update Fees paid by student */
                                        h=manageStudentFees(h);
                                        break;

                                case 3: exit(0);

                                default:cout<<"..................! Invalid choice !...................\n";
                                        return h;

                            }
                            break;

                    case 4:return h;
                }
            }
            else
            {
                throw InvalidChoice();
            }

        }
        catch(InvalidChoice& ic_error)
        {
            ic_error.putMessage();
        }
        catch(...)
        {
            cout<<"Error!";
            return h;
        }
    }
return h;
}

Hostel wardenLogin(Hostel h)
/* Warden Portal */
{
    Student s;
    int ch;
    cout<<"\n________________________* * WARDEN PORTAL * * __________________________\n";
    while(1)
    {
        cout<<"\n\n\t___________SELECT___________\n\t(1)DISPLAY Hostel Rooms\n\t(2)DISPLAY Hostel Staff and Mess Staff\n\t(3)DISPLAY All Registered Students\n\t(4)Register New Student\n\t(5)EXIT\n";
        cin>>ch;
        switch(ch)
        {
            case 1:/* Display All rooms of Hostel h */
                    h.putHostelRoom();
                    break;

            case 2:/* Display Hostel and Mess Details */
                    h.putHostelDetail();
                    /*Display AB Staff Details */
                    cout<<"n___________________ATTACHED WASHROOM BLOCK________________________\n";
                    h.ab.putBlockStaff();
                    /*Display NAB Staff Details */
                    cout<<"n___________________NON ATTACHED WASHROOM BLOCK________________________\n";
                    h.nab.putBlockStaff();
                    break;

            case 3:/* Display all the Students who have occupied beds in Hostel h */
                    displayAllStudent(h);
                    break;

            case 4:/* Take Details of new Student s */
                    s=registerStudent();

                    /* Allot Hostel h to Student s */
                    h=allotHostelRoom(s,h);
                    break;

            case 5: return h;

            default: cout<<"!.......!Invalid Choice!.......!\n";
        }
    }
    return h;
}

void selectChoice()
{
    cout<<"\n\t____________________  SELECT  ____________________\n\t(1)HOSTEL MANAGER LOGIN\n\t(2)HOSTEL WARDEN LOGIN\n\t(3)EXIT\n";
}
void welcomePage()
{
    for(int i=0;i<displaywidth;i++)
        cout<<"-";
    cout<<"\n\n\t\t\tWELCOME TO HOSTEL MANAGEMENT SYSTEM";
    cout<<"\n\n\t\t-*-----*------*-----*------*-------*------*-----*-";
    cout<<"\n\n\n";
    for(int i=0;i<displaywidth;i++)
        cout<<"-";
}

Hostel createHostelDatabase()
{
    /* Creating Warden */
    Warden hw(01,"Komal");

    /* Creating Managers */
    Manager mab[3],mnab[3];
    Manager abm1(1,"Sarita","Evening"),abm2(2,"Padma","Morning"),abm3(3,"Rashi","Evening"),nabm1(4,"Kokila","Morning"),nabm2(5,"Gopi","Evening"),nabm3(6,"Baljeet","Evening");
    mab[0] = abm1;mab[1] = abm2;mab[2] = abm3;mnab[0] = nabm1;mnab[1] = nabm2;mnab[2] = nabm3;

    /* Creating Security */
    Security sh[4],snab[2],sab[2];
    Security s1(1,"Sadiqua","Night"),s2(2,"Lalita","Morning"),s3(3,"Manisha","Evening"),s4(4,"Rita","Morning"),s5(5,"Pavan","Morning"),s6(6,"Kumar","Evening"),s7(7,"Rajesh","Evening"),s8(8,"KamalNath","Morning");
    snab[0] = s1;snab[1] = s2;sab[0] = s3;sab[1] = s4;sh[0] = s5;sh[1] = s6;sh[2] = s7;sh[3] = s8;

    /* Creating Helpers */
    Helper hab[6],hnab[6],mh[3];
    Helper h1(1,"Pramila","Night"),h2(2,"Lakshmi","Morning"),h3(3,"Mala","Evening"),h4(4,"Geeta","Morning"),h5(5,"Sita","Morning"),h6(6,"Kusum","Evening"),h7(7,"Prema","Evening"),h8(8,"Kritika","Morning"),h9(9,"Rekha","Morning"),h10(10,"Sushma","Morning"),h11(11,"Jaya","Morning"),h12(12,"Nirma","Morning");
    hab[0] = h1;hab[1] = h2;hab[2] = h3;hab[3] = h8;hab[4] = h9;hab[5] = h10;hnab[0] = h4;hnab[1] = h5;hnab[2] = h6;hnab[3] = h7;hnab[4] = h11;hnab[5] = h12;mh[0]=h1;mh[1]=h2;mh[2]=h3;

    /* Creating Mess */
    Mess m(11,mab[1],mh);

    /* Creating Attached Washroom Block */
    AttachedWSBlock ab(0,5,10,mab,hab,sab);

    /* Creating Non-Attached Washroom Block */
    NonAttachedWSBlock nab(1,5,10,mnab,hnab,snab);

    /* Creating Hostel*/
    Hostel h(0,"Sarasawati",ab,nab,hw,sh,m);

    return h;
}

class LoginManager{
/* Login for Manager */
public:

    LoginManager()
    {}

    void login(Hostel h)
    {
        cout << "\n____________MANAGER LOGIN________\nEnter Your Username: ";
        cin >> userNameAttempt;
        userName = getfile("/Users/avantikashrivastava/Documents/Sublime/SEM4/userr.txt");


        if(userNameAttempt==userName)
            /* If entered username is present in records */
        {
            cout << "Enter Your Password: ";
            cin >> passWordAttempt;

            passWord = getfile("/Users/avantikashrivastava/Documents/Sublime/SEM4/password.txt");
            cout<<passWord;

            /* If entered password belongs to user  */
            if(passWordAttempt==passWord)
            {
                /* Open Manager's Portal */
                h=hostelManagerLogin(h);

            }

            /* If entered password does not belong to user  */
            else
            {
                cout<<"Sorry ! The password doesn't match\n"<<endl;
            }
        }

        /* If entered username is not present in records */
        else
        {
            cout<<"Sorry ! The User doesn't exist\n\n"<<endl;
            login(h);
        }
    }

    string getfile(const char* p_file)
       /* Read File Function */
    {
        string line;
        fstream file;

        int eChar;

        file.open(p_file, ios::in);
        while(1)
           {
               file>>eChar;  //function ovverwriting

               if(eChar == 0) //if char is 0 , which means we are at the end
               {
                     file.close();

                     return line;
               }

               line += (char)decrypt (eChar);
           }
    }

    void savefile(string p_line, const char* p_fileName)
    {
        fstream file;
        file.open(p_fileName , ios::out);

        for(int i=0; i < p_line.length() ; i++ )
        {
            file << encrypt(p_line[i]);
            file << "\n";
        }

        file <<"0"  ; //signifies we finished that word
        file.close();
    }

    int encrypt(int p_letter)
    {
        return powf(p_letter , 3);
    }
    int decrypt(int p_letter)
    {
        return powf(p_letter , 1/3.f);
    }
    private:
        string passWord; // "grapejuice"
        string userName; // "user@email.com"
        string userNameAttempt;
        string passWordAttempt;
        bool accessGranted;
};
class WardenManager
/* Login for Warden*/
{
public:
    WardenManager()
    {}

    void login(Hostel h)
    {
        cout << "\n____________WARDEN LOGIN________\nEnter Your Username: ";
        cin >> userNameAttempt;

        userName = getFile("/Users/avantikashrivastava/Documents/Sublime/SEM4/warden.txt");

        /* If entered username is present in records */
        if(userNameAttempt == userName)
        {
            cout << "Enter Your Password: ";
            cin >> passWordAttempt;

            passWord = getFile("/Users/avantikashrivastava/Documents/Sublime/SEM4/wpass.txt");

            /* If entered password belongs to user  */
            if(passWordAttempt == passWord)
            {
                /* Open Warden's Login Portal */
                h=wardenLogin(h);
            }
            /* If entered password does not belong to user  */
            else
            {
                cout <<"Sorry ! The password doesn't match"<< endl;
                login(h);
            }
        }
        else
        {
            cout << "Sorry ! The User doesn't exist\n\n";
            login(h);
        }
    }
    string getFile(const char* p_fileName)
    /* Read File Function */
    {
        string line;
        fstream file;

        file.open(p_fileName, ios::in);
        if(file.is_open())
        {
            getline(file, line);
        }
        file.close();

        return line;
    }
private:
    string passWord; //= "warden12";
    string userName; //= "warden@email.com";
    string userNameAttempt;
    string passWordAttempt;
    bool accessGranted;

};
int main()
{
    Hostel h;

    /* Login Objects */
    WardenManager w;
    LoginManager loginManagerObj;

    welcomePage();

    /* Create Hostel's Database */
    h=createHostelDatabase();

    int ch;
    while(1)
        {

            selectChoice();
            try                           //exception handling for wrong choice
            {
                cout<<"Enter Your Choice\n";
                cin>>ch;
                if(ch<=0 or ch>3) throw InvalidChoice(); //if the user enters a choice not given in the menu, program throws error
            switch(ch)
            {

                case 1:/* Manager Login */
                        loginManagerObj.login(h);
                        break;

                case 2:/* Warden Login */
                        w.login(h);
                        break;

                case 3: exit(0);


                break;
            }
            }

            catch (InvalidChoice& ic_error )    //catches the value thrown and prints the message
            {
                ic_error.putMessage();
            }


        }
    return 0;
}
/* END OF PROGRAM */
