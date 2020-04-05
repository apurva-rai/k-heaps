/* -----------------------------------------------------------------------------
 *
 * File Name:  main.cpp
 * Author: Apurva Rai
 * Assignment:   EECS-560 Lab 7
 * Description:  This program will run the HashTable.h to facilitate the running of the whole program. It will take a filename as a command line argument.
 * Date: April 4, 2020
 *
 ---------------------------------------------------------------------------- */

#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct patient
{

string firstName="";
string lastName="";
int urgency=-1;

};

struct doctor
{

string firstName="";
string lastName="";
int assigned=-1;

};

vector<patient*> patientArray;
int patientArraySize = 0;
vector<doctor*> doctorArray;
int doctorArraySize = 0;

bool patientComparator(patient* i, patient* j){ return (i->urgency > j->urgency); }

void minHeapify(int i)
{

int smallest = i;
int left = 3*i + 1;
int middle = 3*i + 2;
int right = 3*i + 3;

  if(left < doctorArraySize && doctorArray[left]->assigned < doctorArray[smallest]->assigned) smallest = left;

  if(middle < doctorArraySize && doctorArray[middle]->assigned < doctorArray[smallest]->assigned) smallest = middle;

  if(right < doctorArraySize && doctorArray[right]->assigned < doctorArray[smallest]->assigned) smallest = right;

  if(smallest != i)
  {

    swap(doctorArray[i], doctorArray[smallest]);

    minHeapify(smallest);

  }

}

void maxHeapify(int i)
{

int largest = i;
int left = 3*i + 1;
int middle = 3*i + 2;
int right = 3*i + 3;

  if(left < patientArraySize && patientArray[left]->urgency > patientArray[largest]->urgency) largest = left;

  if(middle < patientArraySize && patientArray[middle]->urgency > patientArray[largest]->urgency) largest = middle;

  if(right < patientArraySize && patientArray[right]->urgency > patientArray[largest]->urgency) largest = right;

  if(largest != i)
  {

    swap(patientArray[i], patientArray[largest]);

    maxHeapify(largest);

  }

}

void minHeapSort()
{

  for(int i =  doctorArraySize/2 -1; i >= 0; i--) minHeapify(i);

  for(int i = doctorArraySize -1; i >= 0; i--)
  {

    swap(doctorArray[0],doctorArray[i]);
    minHeapify(0);

  }

}

void maxHeapSort()
{

  for(int i =  patientArraySize/2 -1; i >= 0; i--) maxHeapify(i);

  for(int i = patientArraySize -1; i >= 0; i--)
  {

    swap(patientArray[0],patientArray[i]);
    maxHeapify(0);

  }

}

bool addDoctor(doctor* d)
{

  if(doctorArraySize == 0)
  {

    doctorArray.resize(doctorArraySize+1);
    doctorArray[0] = d;
    doctorArraySize++;
    return true;

  }

  for(int i = 0; i < doctorArraySize; i++)
  {

    if((d->firstName == doctorArray[i]->firstName) && (d->lastName == doctorArray[i]->lastName)) return false;

  }

  int newParentIndex = floor(((float)(doctorArraySize)-1.0)/3.0);
  int newChildIndex = 3*newParentIndex + (((doctorArraySize-1)%3)+1);

  doctorArray.resize(doctorArraySize+1);
  doctorArray[newChildIndex] = d;
  doctorArraySize++;

  minHeapSort();

  return true;

}

bool addPatient(patient* p)
{

  if(patientArraySize == 0)
  {

    patientArray.resize(patientArraySize+1);
    patientArray[0] = p;
    patientArraySize++;
    return true;

  }

  for(int i = 0; i < patientArraySize; i++)
  {

    if((p->firstName == patientArray[i]->firstName) && (p->lastName == patientArray[i]->lastName)) return false;

  }

  int newParentIndex = floor(((float)(patientArraySize)-1.0)/3.0);
  int newChildIndex = 3*newParentIndex + (((patientArraySize-1)%3)+1);

  patientArray.resize(patientArraySize+1);
  patientArray[newChildIndex] = p;
  patientArraySize++;

  maxHeapSort();

  return true;

}



int main(int argc, char* argv[])
{

  	if(argc != 1)
  	{

  	std::cout<<"\nIncorrect number of parameters!\n\n";

  	}

  	else
  	{

      ifstream inputDoctors, inputPatients;

      inputDoctors.open("doctors.txt");
      inputPatients.open("patients.txt");

      if( !(inputDoctors.is_open()) || !(inputPatients.is_open()) )
      {

      cout<<"\nWrong file name.\n\n";
      throw(runtime_error("Invalid file name.") );

      }

      while(true)
      {

      string temp= "",first="",last="",numString="";
  		int num=0,i=0;

      inputDoctors >> temp;

  		if(inputDoctors.eof()) break;

        while(temp[i]!= ',')
        {

          first+=temp[i];
          i++;

        }
        i++;
        while(temp[i]!= ',')
        {

          last+=temp[i];
          i++;

        }
        i++;
        while(temp[i]!= '\0')
        {

          numString+=temp[i];
          i++;

        }


      num = stoi(numString);

      doctor* newDoc = new doctor;
      newDoc->firstName = first;
      newDoc->lastName = last;
      newDoc->assigned = num;

      addDoctor(newDoc);

      }

      while(true)
      {

      string temp= "",first="",last="",numString="";
  		int num=0,i=0;

      inputPatients >> temp;

  		if(inputPatients.eof()) break;

        while(temp[i]!= ',')
        {

          first+=temp[i];
          i++;

        }
        i++;
        while(temp[i]!= ',')
        {

          last+=temp[i];
          i++;

        }
        i++;
        while(temp[i]!= '\0')
        {

          numString+=temp[i];
          i++;

        }


      num = stoi(numString);

      patient* newP = new patient;
      newP->firstName = first;
      newP->lastName = last;
      newP->urgency = num;

      addPatient(newP);

      }

      int option=0;

      while(option != 3)
      {

        system("clear");
        cout << ".―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n\nHospital Patient & Doctor Management System\n\n1. Patient Management\n2. Doctor Assignment\n3. Exit\n\n>";

        cin >> option;

        while(option > 3 || option < 1)
        {

          cout << "\nPlease select a valid option:\n";
          cin >> option;

        }

        system("clear");

        if(option == 1)
        {

          while(option != 9)
          {

            //system("clear");
            cout << "\n\n\n.―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n\nPatient Management System\n\n\t1.  New Patient\n\t2.  Treat Patient\n\t3.  Change Urgency\n\t4.  Next Patient\n\t5.  Last Patient\n\t6.  Patient Token\n\t7.  Patient Count\n\t8.  Patient Report\n\t9.  Go Back To Menu\n\nPlease choose your option:\n>";

            cin >> option;

            while(option > 9 || option < 1)
            {

              cout << "\nPlease select a valid option:\n";
              cin >> option;

            }

            if(option == 1)
            {

              patient* tempP = new patient;
              cout << "\n>Enter patient's first name:\n>";
      				cin >> tempP->firstName;
              cout << ">Enter patient's last name:\n>";
      				cin >> tempP->lastName;
              cout << ">Enter patients urgency:\n>";
      				cin >> tempP->urgency;
              if(addPatient(tempP)) cout << ">New patient record added.\n";
              else cout << ">Patient was not added.\n";

            }
            else if(option == 2)
            {

              if(patientArraySize == 0)
              {

                cout << "\n>No patients left!\n";
                continue;

              }

              cout << "Highest priority patient successfully treated. Below are details:\n>";
              cout << patientArray[0]->firstName << "," << patientArray[0]->lastName << "," << patientArray[0]->urgency << "\n";

              delete patientArray[0];

                for(int i = 0; i < patientArraySize; i++)
                {

                  patientArray[i] = patientArray[i+1];

                }

                patientArraySize--;
                patientArray.resize(patientArraySize);

                maxHeapSort();


            }
            else if(option == 3)
            {

              string first="",last="";
              int i = 0, newUrgency=-1;

              if(patientArraySize == 0)
              {

                cout << "\n>No patients left!\n";
                continue;

              }

              cout << "\n>Enter patient's deatils to change urgency:";
              cout << "\n>First name: ";
              cin >> first;
              cout << ">Last name: ";
              cin >> last;

              for(i = 0; i < patientArraySize; i++)
              {

                if((first == patientArray[i]->firstName) && (last == patientArray[i]->lastName)) break;

              }

              if(i == patientArraySize)
              {

                cout << "\n>Patient does not exist.\n";
                continue;

              }

              cout << ">Current details of this patient are: " << patientArray[i]->firstName << "," << patientArray[i]->lastName << "," << patientArray[i]->urgency;
              cout << "\n>Enter new urgency level: ";
              cin >> newUrgency;
              patientArray[i]->urgency = newUrgency;

              maxHeapSort();

              cout << ">The patient record is updated.\n";

            }
            else if(option == 4)
            {

              cout << ">Next patient: " << patientArray[0]->firstName << "," << patientArray[0]->lastName << "," << patientArray[0]->urgency << "\n";

            }
            else if(option == 5)
            {

              int tempMin = 0;

              for(int i =0; i < patientArraySize; i++)
              {

                if(patientArray[i]->urgency <= patientArray[tempMin]->urgency) tempMin = i;

              }

              cout << ">Last patient: " << patientArray[tempMin]->firstName << "," << patientArray[tempMin]->lastName << "," << patientArray[tempMin]->urgency << "\n";

            }
      			else if(option == 6)
      			{

              string first="",last="";
              int i = 0;

              if(patientArraySize == 0)
              {

                cout << "\n>No patients left!\n";
                continue;

              }

              cout << "\n>Enter patient's deatils to change urgency:\n>";
              cout << "\n>First name: ";
              cin >> first;
              cout << ">Last name: ";
              cin >> last;

              vector<patient*> tempArray;
              tempArray.resize(patientArraySize);

              for(int i = 0; i < patientArraySize; i++)
              {

                patient* tempP = new patient;
                tempP->firstName = patientArray[i]->firstName;
                tempP->lastName = patientArray[i]->lastName;
                tempP->urgency = patientArray[i]->urgency;
                tempArray[i] = tempP;

              }

              sort(tempArray.begin(),tempArray.end(), patientComparator);

              for(i =0; i < patientArraySize; i++)
              {

                if((tempArray[i]->firstName == first) && (tempArray[i]->lastName == last)) break;

              }

              for(int j = 0; j < patientArraySize; j++)
              {

                delete tempArray[j];

              }

              cout << ">Patient token: " << i+1 << "\n";

      			}
      			else if(option == 7)
      			{

      				cout << ">Current patient count is: " << patientArraySize << "\n";

      			}
      			else if(option == 8)
      			{

              cout << ">Current patient's report:\n";

              for(int i = 0; i < patientArraySize; i++)
              {

                cout << patientArray[i]->firstName << "," << patientArray[i]->lastName << "," << patientArray[i]->urgency << "\n";


              }

      			}

      		}

        }
        else if(option == 2)
        {

          while(option != 10)
          {

            cout << "\n\n.―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\n\nDoctor Assignment System\n1.  New Doctor\n2.  Update Patients\n3.  Remove Doctor\n4.  Next Available Doctor\n5.  Check Availability\n6.  Total Doctor Count\n7.  Available Doctors Count\n8.  Available Doctor Report\n9.  Busy Doctors List\n10. Go Back to Menu\n\n>";

            cin >> option;

            while(option > 10 || option < 1)
            {

              cout << "\nPlease select a valid option:\n";
              cin >> option;

            }

            if(option == 1)
            {

              doctor* tempP = new doctor;
              cout << ">Enter doctor details:\n>";
              cout << "First name: ";
              cin >> tempP->firstName;
              cout << ">Last Name: ";
              cin >> tempP->lastName;
              tempP->assigned = 0;
              if(addDoctor(tempP)) cout << ">A new doctor is added and available.\n";
              else cout << ">Doctor was not added.\n";

            }
            else if(option == 2)
            {

              string first="",last="";
              char status='\0';
              int i = 0, newAssigned=-1;

              if(doctorArraySize == 0)
              {

                cout << "\n>No patients left!\n";
                continue;

              }

              cout << "\n>Enter doctor's deatils to change assigned:";
              cout << "\n>First name: ";
              cin >> first;
              cout << ">Last name: ";
              cin >> last;

              for(i = 0; i < doctorArraySize; i++)
              {

                if((first == doctorArray[i]->firstName) && (last == doctorArray[i]->lastName)) break;

              }

              cout << ">Current details of this doctor are: " << doctorArray[i]->firstName << "," << doctorArray[i]->lastName << "," << doctorArray[i]->assigned;

              cout << "\n>Increase or reduce patient count [i/r]: ";
              cin >> status;

              while(status != 'i' && status != 'I' && status != 'r' && status != 'R')
              {

                cout << "\n>Input a proper letter!\n>";
                cin >> status;

              }

              if(status == 'i' || status == 'I')
              {

                cout << "\nIncrease by how much?\n>";
                cin >> newAssigned;

                if(newAssigned < 0) throw runtime_error("You are increasing so assign a positive number.");

                while((newAssigned+doctorArray[i]->assigned) > 25)
                {

                  cout << "\nDoctors cannot handle more than 25 patients!\n>";
                  cin >> newAssigned;

                }

                doctorArray[i]->assigned+=newAssigned;

              }

              if(status == 'r' || status == 'R')
              {

                cout << "\nReduce by how much?\n>";
                cin >> newAssigned;

                if(newAssigned > 25) throw runtime_error("You cannot decrease by more than the doctor can handle.");

                while((newAssigned+doctorArray[i]->assigned) < 0)
                {

                  cout << "\nDoctors cannot have less than 0 patients!\n>";
                  cin >> newAssigned;

                }

                doctorArray[i]->assigned-=newAssigned;

              }

              cout << ">The doctor's record is updated.\n";

            }
          else if(option == 3)
          {

            if(doctorArraySize == 0)
            {

              cout << "\n>No doctors left!\n";
              continue;

            }

            cout << "Doctor with lowest patient count has been removed. Below are details:\n>";
            cout << doctorArray[0]->firstName << "," << doctorArray[0]->lastName << "," << doctorArray[0]->assigned << "\n";

            delete doctorArray[0];

              for(int i = 0; i < doctorArraySize; i++)
              {

                doctorArray[i] = doctorArray[i+1];

              }

              doctorArraySize--;
              doctorArray.resize(doctorArraySize);

              minHeapSort();

          }
          else if(option == 4)
          {

            cout << ">Next available doctor: " << doctorArray[0]->firstName << " " << doctorArray[0]->lastName << "\n";

          }
          else if(option == 5)
          {

            string first="",last="";
            int i = 0;

            if(doctorArraySize == 0)
            {

              cout << "\n>No patients left!\n";
              continue;

            }

            cout << "\n>Enter doctor's details to check availability:";
            cout << "\n>First name: ";
            cin >> first;
            cout << ">Last name: ";
            cin >> last;

            for(i = 0; i < doctorArraySize; i++)
            {

              if((first == doctorArray[i]->firstName) && (last == doctorArray[i]->lastName)) break;

            }

            if(doctorArray[i]->assigned >= 22) cout << ">The doctor is not available.\n";
            else cout << ">The doctor is available.\n";

          }
    			else if(option == 6)
    			{

            cout << ">There are " << doctorArraySize << " total doctors\n";

    			}
    			else if(option == 7)
    			{

            int total = 0;

            for(int i = 0; i < doctorArraySize; i++)
            {

              if(doctorArray[i]->assigned < 22) total++;

            }

            cout << "> There are " << total << " doctors available.\n";

    			}
    			else if(option == 8)
    			{

            cout <<">The available doctors are:\n";

            for(int i = 0; i < doctorArraySize; i++)
            {

              if(doctorArray[i]->assigned < 22)
              cout << doctorArray[i]->firstName << "," << doctorArray[i]->lastName << "," << doctorArray[i]->assigned << "\n";

            }

    			}
          else if(option == 9)
          {

            cout <<">Doctors not available at this time are:\n";

            for(int i = 0; i < doctorArraySize; i++)
            {

              if(doctorArray[i]->assigned >= 22)
              cout << doctorArray[i]->firstName << "," << doctorArray[i]->lastName << "," << doctorArray[i]->assigned << "\n";

            }


          }

    		}

        }

  		cout <<">Bye Bye!\n\n";

   	  }

    }

    for(int i = 0; i < doctorArraySize; i++) delete doctorArray[i];

    for(int i = 0; i < patientArraySize; i++) delete patientArray[i];

    return(0);
}
