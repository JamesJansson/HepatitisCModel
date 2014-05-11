class InjectingNetworkClass {
    int NumberOfGroups;
    float RateOfGroupChange;


    EventClass CurrentlyUsing;
    EventClass SharingGroup;//This is connected to a InjectingGroupClass that manages sharing activities
public:
    RemovePeople();//go through and remove people who are no longer injectors from groups
    AddPeople(); // at random to the sharing groups


};

class InjectingGroupClass {
    int NumberOfPeople;
    int ListOfPeople[];
    PointersToIndividuals;



public:

    SharingEvent();//(PointersToIndividuals)
    RemovePeople();

};
