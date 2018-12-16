/**
Project : Airport Management System.
Authors : Himanshu Jaju and Shubham Chandra
*/

// Header Files Required.
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

// For loop macros
#define FOR(i,a,b)      for(i=a;i<b;i++)
#define RFOR(i,a,b)     for(i=b-1;i>=0;i--)

// scanf macros
#define GI(x)           scanf("%d",&x);
#define GS(x)           scanf("%s",x);
#define GSLN(x)         gets(x);

// macros for airplane status.
#define NOT_AVAILABLE   0
#define SECURITY_CHECK  1
#define BOARDING        2
#define DEPARTED        3
#define DELAYED         4
#define CANCELLED      -1

//macros for user status.
#define CHECKED_IN            1
#define CANCELLED            -1

// structure for time.
typedef struct
{
      int hour;
      int mins;
} Time;

// structure for airplane
typedef struct a
{
      char company[100];
      char type[100];
      char number[100];
      Time boarding_time;
      Time departure_time;
      char destination[100];
      int status;
      int terminal;
      struct a* link;
} airplane;

// structure for passenger
typedef struct
{
      char first_name[100];
      char second_name[100];
      char flight_no[100];
      int status;
      double luggage;
} passenger;

airplane* flights = NULL; // linked list.

passenger*  users = NULL; // dynamic array.
int max_capacity = 1,capacity = 1;

// Function related to airplanes at the airport.
void add_airplane();
airplane* create_node();
void change_status_airplane();
void insert_flight(airplane*);
void display_airplanes();
void remove_airplanes();
void change_terminal();
void change_time();
void airline_operation();
void display_flight(airplane*);
airplane* search_flight(char[]);
void delete_node(airplane**,airplane*);

// Functions related to passenger.
void add_passenger();
void change_passenger_status();
void passenger_details();
void passenger_operation();
void upgrade_max_capacity();

// Other functions.
void show_menu(int);
void main_menu();
void airplane_menu();
void passenger_menu();
int choice();

// Main Driver Function
int main()
{
      users = (passenger*) malloc(sizeof(passenger));
      while(1) show_menu(0);
      return 0;
}

// Shows Menu
void show_menu(int id)
{
      switch(id)
      {
            case 0 : main_menu();return;
            case 1 : airplane_menu();break;
            case 2 : passenger_menu();break;
            case 3 : exit(0);
            default : printf("Wrong choice!\n");main_menu();return;
      }
      return;
}

void main_menu()
{
      printf("\n***********MAIN MENU***************");
      printf("\n1. Flight Related Menu (Search, Display, Add, Change Existing)");
      printf("\n2. Passenger Related Menu (Add, Display, Change Status)");
      printf("\n3. Exit");
      printf("\nMain> ");

      int k = choice();
      show_menu(k);
}

void airplane_menu()
{
      printf("\n********FLIGHT MENU************\n");
      printf("1. Display Current Flights\n");
      printf("2. Add New Flight\n");
      printf("3. Change Flight Status\n");
      printf("4. Change Flight Timing\n");
      printf("5. Change Flight Terminal\n");
      printf("6. Remove Flight\n");
      printf("Press any other digit to go back...");
      printf("\nFlight> ");

      int k = choice();
      if(k>=1 && k<=6)
      {
            airline_operation(k);
            show_menu(1);
      }
}

void passenger_menu()
{
      printf("\n********PASSENGER MENU************\n");
      printf("1. Display Passenger Details\n");
      printf("2. Add New Passenger\n");
      printf("3. Change Passenger Status\n");
      printf("Press any other digit to go back...");
      printf("\nPassenger> ");

      int k = choice();
      if(k>=1 && k<=3)
      {
            passenger_operation(k);
            show_menu(2);
      }
}

int choice()
{
      int k;
      GI(k);
      return k;
}

void airline_operation(int choice)
{
      switch(choice)
      {
            case 1: display_airplanes(); break;
            case 2: add_airplane(); break;
            case 3: change_status_airplane(); break;
            case 4: change_time(); break;
            case 5: change_terminal(); break;
            case 6: remove_airplanes(); break;
      }
}

airplane* create_node()
{
      airplane* newptr = (airplane*) malloc(sizeof(airplane));
      newptr->link = NULL;
      return newptr;
}

void insert_flight(airplane* ptr)
{
      if(flights == NULL)
      {
            flights = ptr;
            return ;
      }
      airplane* i = flights;
      while(i->link != NULL) i = i->link;
      i->link = ptr;
}

void add_airplane()
{
      airplane* newptr = create_node();

      printf("Enter company name : ");
      char ch;
      scanf("%c",&ch);
      gets(newptr->company);
      printf("Enter Airbus type : ");
      gets(newptr->type);
      printf("Enter Flight ID : ");
      gets(newptr->number);
      printf("Enter Destination : ");
      gets(newptr->destination);
      printf("Enter Boarding Time in HH:MM format : ");
      scanf("%d:%d",&newptr->boarding_time.hour,&newptr->boarding_time.mins);
      printf("Enter Departure Time in HH:MM format : ");
      scanf("%d:%d",&newptr->departure_time.hour,&newptr->departure_time.mins);

      newptr->status = 0;
      newptr->terminal = -1;

      insert_flight(newptr);

      printf("Flight Has Been Added! You can alter the status and terminal from the flight menu!\n");
}

void delete_node(airplane** start,airplane* node)
{
      // node is present in start linked list.
      airplane* temp; // to free the space.
      if(*start == node)
      {
            temp = *start;
            *start = (*start)->link;
      }
      else
      {
            airplane* x = *start;
            while(x->link != node) x = x->link;
            temp = x->link;
            x->link = temp->link;
      }
      free(temp);
}

void remove_airplanes()
{
      printf("\n**********Remove A Flight**********\n");
      printf("Enter Flight ID : ");
      char abc[100];
      scanf("%s",abc);
      airplane* srch = search_flight(abc);
      if(srch == NULL)
            printf("Incorrect Flight Id\n");
      else
            delete_node(&flights,srch);
}

void change_time()
{
      printf("\n********Change Flight Timing*************\n");
      printf("Enter Flight ID : ");
      char abc[100];
      scanf("%s",abc);
      airplane* srch = search_flight(abc);
      if(srch == NULL)
            printf("Incorrect Flight Id\n");
      else
      {
            printf("New Departure Time> Hours : ");
            int hr = choice();
            printf("New Departure Time> Minutes : ");
            int mm = choice();
            srch->departure_time.hour = hr;
            srch->departure_time.mins = mm;
      }
}

void change_terminal()
{
      printf("\n********Change Flight Terminal*************\n");
      printf("Enter Flight ID : ");
      char abc[100];
      scanf("%s",abc);
      airplane* srch = search_flight(abc);
      if(srch == NULL)
            printf("Incorrect Flight Id\n");
      else
      {
            printf("Enter Terminal Number : ");
            int k = choice();
            srch->terminal = k;
      }
}

void change_status_airplane()
{
      printf("\n********Change Flight Status*************\n");
      printf("Enter Flight ID : ");
      char abc[100];
      scanf("%s",abc);
      airplane* srch = search_flight(abc);
      if(srch == NULL)
            printf("Incorrect Flight Id\n");
      else
      {
            printf("1. Security Checking\n2. Boarding\n3. Departed\n4. Delayed\n5. Cancelled\n6.Not available\nAny other digit to go back..\nStatus> ");
            int k = choice();
            if(k>=1 && k<=6)
            {
                  if(k == 5) k = -1;
                  else if(k == 6) k = 0;
                  srch->status = k;
            }
      }
}

airplane* search_flight(char num[])
{
      airplane* temp = flights;
      while(temp != NULL)
      {
            if(!strcmp(temp->number,num)) break;
            temp = temp->link;
      }
      return temp;
}

void display_flight(airplane* a)
{
      printf("\n");
      printf("Company : %s\nID : %s\nDeparture : %02d:%02d\nDestination : %s\n",a->company,a->number,a->departure_time.hour,a->departure_time.mins,a->destination);
      printf("Status : ");
      switch(a->status)
      {
            case -1:printf("CANCEL");break;
            case 0: printf("NA");break;
            case 1: printf("SEC CHK");break;
            case 2: printf("BOARD");break;
            case 3: printf("DEPART");break;
            case 4: printf("DELAY");break;
      }
      printf("\nTerminal : %d\n",a->terminal);
}

void display_airplanes()
{
      printf("\n*************FLIGHTS*************\n");
      if(flights == NULL)
      {
            printf("No flights on display yet!\n");
            return;
      }
      airplane* start = flights;
      while(start!=NULL)
      {
            display_flight(start);
            start = start->link;
      }
}

void passenger_operation(int choice)
{
      switch(choice)
      {
            case 1: passenger_details(); break;
            case 2: add_passenger(); break;
            case 3: change_passenger_status(); break;
      }
}

void upgrade_max_capacity()
{
      realloc(users,sizeof(passenger)*2*max_capacity);
      max_capacity*=2;
}

void add_passenger()
{
      if(capacity == max_capacity) upgrade_max_capacity();
      printf("Passenger ID : %d\n",capacity);
      printf("Passenger Details> ");
      printf("Enter First Name : ");
      scanf("%s",users[capacity].first_name);
      printf("Passenger Details> ");
      printf("Enter Last Name : ");
      scanf("%s",users[capacity].second_name);
      printf("Passenger Details> ");
      printf("Enter Flight Number : ");
      scanf("%s",users[capacity].flight_no);
      printf("Passenger Details> ");
      printf("Enter Luggage Weight : ");
      scanf("%lf",&users[capacity].luggage);
      users[capacity].status = CHECKED_IN;
      if(search_flight(users[capacity].flight_no) != NULL)
            capacity++;
      else
            printf("Wrong Flight Number! Re fill the data correctly\n");
}

void change_passenger_status()
{
      printf("\n*******Change Passenger Status*********\n");
      printf("Enter Passenger ID : ");
      int k = choice();
      if(k>=capacity || k<1)
      {
            printf("Invalid choice!\n");
            return;
      }
      printf("1. Change status to Checked In\n2. Change status to cancelled\nAny Other Digit To Go back\nStatus>");
      int p = choice();
      switch(p)
      {
            case 1: users[k].status = CHECKED_IN;break;
            case 2: users[k].status = CANCELLED;break;
            default: return;
      }
}

void passenger_details()
{
      printf("\n*******Passenger Details*********\n");
      printf("Enter Passenger ID : ");
      int k = choice();
      if(k>=capacity || k<1)
      {
            printf("Invalid choice!\n");
            return;
      }
      printf("Passenger Details.... \n");
      printf("Name : %s %s\n",users[k].first_name,users[k].second_name);
      printf("Flight : %s\n",users[k].flight_no);
      printf("Luggage : %.3lf\n",users[k].luggage);
      printf("Status : ");
      int x = users[k].status;
      if(x == CHECKED_IN) printf("Checked In");
      else printf("Cancelled");
      printf("\n");
}
