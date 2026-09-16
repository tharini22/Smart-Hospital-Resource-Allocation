#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_PATIENTS 100
float calcConsultationCost(int selectedSpecialty,const float consultationFee[]);
float calcWaitTime(int selectedSpecialty,const int queueCount[],const int consultationTime[]);
float calcEmergencySurcharge(int urgency,float consultationCost);
float calcWardCost(int selectedWard,int admittedDays,const float wardDailyBedRate[]);
float calcGrossTotal(float consultationCost,float emergencySurcharge,float wardCost);
float calcAgeSubsidy(int age,float grossTotal);
float calcFinalPayable(float grossTotal,float ageSubsidyDiscount);
void sortPatientByPriority(int patients,char patientsName[][50],int patientAge[],int patientUrgency[],int patientSpecialty[],int patientAdmitted[],int patientWard[],int patientDays[]);
int main()

{   char patientName[60];
    int age;
    int urgency;
    int selectedSpecialty;
    int admitted;
    int selectedWard;
    int admittedDays;

    char patientsName[MAX_PATIENTS][50];
    int patientAge[MAX_PATIENTS];
    int patientUrgency[MAX_PATIENTS];
    int patientSpecialty[MAX_PATIENTS];
    int patientAdmitted[MAX_PATIENTS];
    int patientWard[MAX_PATIENTS];
    int patientDays[MAX_PATIENTS];

    int patients;

    float patientConsultationCost[MAX_PATIENTS];
    int patientWaitTime[MAX_PATIENTS];
    float patientEmergencySurcharge[MAX_PATIENTS];
    float patientWardCost[MAX_PATIENTS];
    float patientGrossTotal[MAX_PATIENTS];
    float patientAgeSubsidyDiscount[MAX_PATIENTS];
    float patientFinalPayable[MAX_PATIENTS];

    float consultationCost;
    int waitTime;
    float emergencySurcharge;
    float wardCost;
    float grossTotal;
    float ageSubsidyDiscount;
    float finalPayable;
    const int specialtyId[4]={1,2,3,4};
    const char specialtyName[4][30]={"General Practice(OPD)","Paediatrics","Cardiology","Neurology"};
    const float consultationFee[4]={1500.00,2500.00,4500.00,5000.00};
    const int consultationTime[4]={15,20,30,30};
    const int dailyPatientCap[4]={30,20,12,10};
    const int wardID[4]={1,2,3,4};
    const char wardName[4][30]={"General ward","Paediatric ward","Surgical ward","ICU (Intensive Care Unit)"};
    const float wardDailyBedRate[4]={3000.00,6000.00,12000.00,25000.00};
    const int totalBedCapacity[4]={20,10,10,5};

    int queueCount[4]={0};
    int i;

    printf("Smart Hospital & Resource Allocation System\n\n");


    printf("Enter number of patients : ");
    scanf("%d",&patients);

    for(i=0;i<patients;i++)
    {
        printf("\nEnter patient name: ");
        scanf("%s", patientsName[i]);
        printf("Enter age: ");
        scanf("%d",&patientAge[i]);
        printf("Enter urgency (1-Normal,2-Urgent,3-Critical): ");
        scanf("%d",&patientUrgency[i]);
        if(patientUrgency[i] < 1 || patientUrgency[i] > 3)
        {
            printf("Invalid urgency!\n");
        }
        printf("Enter specialty ID: ");
        scanf("%d",&patientSpecialty[i]);
        if(patientSpecialty[i] < 1 || patientSpecialty[i] > 4)
        {
            printf("Invalid specialty ID!\n");
        }
        printf("Is the patient admitted to ward? (1-Yes,0-No): ");
        scanf("%d",&patientAdmitted[i]);
        if(patientAdmitted[i]==1)
        {
            printf("Enter ward ID (1 to 4): ");
            scanf("%d",&patientWard[i]);
            if(patientWard[i] < 1 || patientWard[i] > 4)
            {
                printf("Invalid ward ID!\n");
            }
            printf("Enter number of days admitted: ");
            scanf("%d",&patientDays[i]);
            if(patientDays[i] <= 0)
            {
                printf("Invalid number of admitted Days!\n");
            }

        }


    }



    sortPatientByPriority(patients,patientsName,patientAge,patientUrgency,patientSpecialty,patientAdmitted,patientWard,patientDays);
    printf("\nPatients in priority order: \n");
    printf("-------------------------------------------------------------------\n");
    printf("%-5s %-20s %-10s\n","No","patient name","urgency");
    printf("-------------------------------------------------------------------\n");

    for(i=0;i<patients;i++)
    {
        printf("%-5d %-20s %-10d\n",i+1,patientsName[i],patientUrgency[i]);
    }
    printf("-------------------------------------------------------------------\n");

    printf("\nDoctor Specialties\n\n");

    printf("%-4s  %-25s %-12s    %-10s    %-5s\n","Specialty ID","Specialty Name","Base Consultation Fee","Consultation Time/Patient","Daily Patient Cap\n");
    for(i=0;i<4;i++)
    {
        printf("\t%-4d %-25s %-12.2f\t\t\t%-10d\t\t\t%-5d\n",specialtyId[i],specialtyName[i],consultationFee[i],consultationTime[i],dailyPatientCap[i]);
    }

    printf("\nHospital Wards\n\n");
    printf("\t%-10s %-30s %-15s %-10s\n","Ward ID","Ward Name","Daily Bed Rate","Total Bed Capacity");
    for(i=0;i<4;i++)
    {
        printf("\t%-10d %-30s %-15.2f %-10d\n ",wardID[i],wardName[i],wardDailyBedRate[i],totalBedCapacity[i]);
    }

    int bedOccupancy[4][20]={0};

    for(i=0;i<patients;i++)
    {
        patientConsultationCost[i]=calcConsultationCost(patientSpecialty[i],consultationFee);

    }

    for(i=0;i<patients;i++)
    {
        patientWaitTime[i]=calcWaitTime(patientSpecialty[i],queueCount,consultationTime);
        queueCount[patientSpecialty[i]-1]++;

    }

    for(i=0;i<patients;i++)
    {
        patientEmergencySurcharge[i]=calcEmergencySurcharge(patientUrgency[i],patientConsultationCost[i]);
    }

    for(i=0;i<patients;i++)
    {
        if(patientAdmitted[i]==1)
        {
           patientWardCost[i]=calcWardCost(patientWard[i],patientDays[i],wardDailyBedRate);
        }
        else
        {
            patientWardCost[i]=0;
        }
    }

    for(i=0;i<patients;i++)
    {
        patientGrossTotal[i]=calcGrossTotal(patientConsultationCost[i],patientEmergencySurcharge[i],patientWardCost[i]);
    }

    for(i=0;i<patients;i++)
    {
        patientAgeSubsidyDiscount[i]=calcAgeSubsidy(patientAge[i],patientGrossTotal[i]);
    }

    for(i=0;i<patients;i++)
    {
        patientFinalPayable[i]=calcFinalPayable(patientGrossTotal[i],patientAgeSubsidyDiscount[i]);
    }
    return 0;
}


float calcConsultationCost(int selectedSpecialty,const float consultationFee[])
{
    return consultationFee[selectedSpecialty-1];
}

float calcWaitTime(int selectedSpecialty,const int queueCount[],const int consultationTime[])
{
    int time;
    time=queueCount[selectedSpecialty-1]*consultationTime[selectedSpecialty-1];

    return time;
}

float calcEmergencySurcharge(int urgency,float consultationCost)
{
    float charge;
    if(urgency==1)
    {
        charge=0;
    }
    else if(urgency==2)
    {
        charge=consultationCost*0.20;
    }
    else
    {
        charge=consultationCost*0.50;
    }
    return charge;
}

float calcWardCost(int selectedWard,int admittedDays,const float wardDailyBedRate[])
{
    float cost;
    if(admittedDays==0)
    {
        cost=0;
    }
    else
    {
        cost=admittedDays*wardDailyBedRate[selectedWard-1];
    }
    return cost;
}

float calcGrossTotal(float consultationCost,float emergencySurcharge,float wardCost)
{
    float total;
    total=consultationCost+emergencySurcharge+wardCost;
    return total;
}

float calcAgeSubsidy(int age,float grossTotal)
{
    float discount;
    if(age < 5 || age > 65)
    {
        discount = grossTotal*0.15;
    }
    else
    {
        discount = 0;
    }
    return discount;
}

float calcFinalPayable(float grossTotal,float ageSubsidyDiscount)
{
    float amount;
    amount = grossTotal - ageSubsidyDiscount;
    return amount;
}

void sortPatientByPriority(int patients,char patientsName[][50],int patientAge[],int patientUrgency[],int patientSpecialty[],int patientAdmitted[],int patientWard[],int patientDays[])
{
    int i,j;
    int temp;
    char tempName[50];

    for(i=0;i<patients-1;i++)
    {
        for(j=0;j<patients-i-1;j++)
        {
            if(patientUrgency[j]<patientUrgency[j+1])
            {
                temp=patientUrgency[j];
                patientUrgency[j]=patientUrgency[j+1];
                patientUrgency[j+1]=temp;

                strcpy(tempName,patientsName[j]);
                strcpy(patientsName[j],patientsName[j+1]);
                strcpy(patientsName[j+1],tempName);

                temp=patientAge[j];
                patientAge[j]=patientAge[j+1];
                patientAge[j+1]=temp;

                temp=patientSpecialty[j];
                patientSpecialty[j]=patientSpecialty[j+1];
                patientSpecialty[j+1]=temp;

                temp=patientAdmitted[j];
                patientAdmitted[j]=patientAdmitted[j+1];
                patientAdmitted[j+1]=temp;

                temp=patientWard[j];
                patientWard[j]=patientWard[j+1];
                patientWard[j+1]=temp;

                temp=patientDays[j];
                patientDays[j]=patientDays[j+1];
                patientDays[j+1]=temp;

            }
        }
    }
}

