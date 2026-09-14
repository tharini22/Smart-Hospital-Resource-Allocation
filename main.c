#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int specialtyId[4]={1,2,3,4};
    const char specialtyName[4][30]={"General Practice(OPD)","Paediatrics","Cardiology","Neurology"};
    const float consultationFee[4]={1500.00,2500.00,4500.00,5000.00};
    const int consultationTime[4]={15,20,30,30};
    const int dailyPatientCap[4]={30,20,12,10};
    const int wardID[4]={1,2,3,4};
    const char wardName[4][30]={"General ward","Paediatric ward","Surgical ward","ICU (Intensive Care Unit)"};
    const float dailyBedRate[4]={3000.00,6000.00,12000.00,25000.00};
    const int totalBedCapacity[4]={20,10,10,5};
    int i;
    printf("Smart Hospital & Resource Allocation System\n\n");

    printf("Doctor Specialties\n\n");

    printf("%-4s  %-25s %-12s    %-10s    %-5s\n","Specialty ID","Specialty Name","Base Consultation Fee","Consultation Time/Patient","Daily Patient Cap\n");
    for(i=0;i<4;i++)
    {
        printf("\t%-4d %-25s %-12.2f\t\t\t%-10d\t\t\t%-5d\n",specialtyId[i],specialtyName[i],consultationFee[i],consultationTime[i],dailyPatientCap[i]);
    }

    printf("\nHospital Wards\n\n");
    printf("\t%-10s %-30s %-15s %-10s\n","Ward ID","Ward Name","Daily Bed Rate","Total Bed Capacity");
    for(i=0;i<4;i++)
    {
        printf("\t%-10d %-30s %-15.2f %-10d\n ",wardID[i],wardName[i],dailyBedRate[i],totalBedCapacity[i]);
    }

    int bedOccupancy[4][20]={0};




    return 0;
}
