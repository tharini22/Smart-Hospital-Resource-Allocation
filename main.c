#include <stdio.h>
#include <stdlib.h>
float calcConsultationCost(int selectedSpecialty,const float consultationFee[]);
float calcWaitTime(int selectedSpecialty,const int queueCount[],const int consultationTime[]);
float calcEmergencySurcharge(int urgency,float consultationCost);
float calcWardCost(int selectedWard,int admittedDays,const float wardDailyBedRate[]);
int main()
{   char patientName[60];
    int age;
    int urgency;
    int selectedSpecialty;
    int admitted;
    int selectedWard;
    int admittedDays;
    float consultationCost;
    int waitTime;
    float emergencySurcharge;
    float wardCost;
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

    printf("\nEnter patient name: ");
    scanf("%s", patientName);
    printf("Enter age: ");
    scanf("%d",&age);
    printf("Enter urgency (1-Normal,2-Urgent,3-Critical): ");
    scanf("%d",&urgency);
    if(urgency < 1 || urgency > 3)
    {
        printf("Invalid urgency!\n");
    }
    printf("Enter specialty ID: ");
    scanf("%d",&selectedSpecialty);
    if(selectedSpecialty < 1 || selectedSpecialty > 4)
    {
        printf("Invalid specialty ID!\n");
    }
    printf("Is the patient admitted to ward? (1-Yes,0-No): ");
    scanf("%d",&admitted);

    if(admitted==1)
    {
        printf("Enter ward ID (1 to 4): ");
        scanf("%d",&selectedWard);
        if(selectedWard < 1 || selectedWard > 4)
        {
            printf("Invalid ward ID!\n");
        }
        printf("Enter number of days admitted: ");
        scanf("%d",&admittedDays);
        if(admittedDays <= 0)
        {
            printf("Invalid number of admitted Days!\n");
        }
    }
    else
    {   selectedWard = 0;
        admittedDays = 0;
    }

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

    consultationCost=calcConsultationCost(selectedSpecialty,consultationFee);

    waitTime=calcWaitTime(selectedSpecialty,queueCount,consultationTime);
    queueCount[selectedSpecialty-1]++;

    emergencySurcharge = calcEmergencySurcharge(urgency,consultationCost);

    wardCost = calcWardCost(selectedWard,admittedDays,wardDailyBedRate);






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
