#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int Index = 0; // Global Index count for marking Subscribers for unsubscribing, a sequential identity value;

class Subscriber_Parent{ // Subscriber Parent Class
    public:
    int Index; // To take the index from publisher to be found later on
    virtual void Event_Handler(int &Parameter){// Event Handler. Can be declared not as a complete virtual function (=0) i.e Abstract class to make Parent subscriber respond to Event Occurances
    // For direct parent class, effective set of Event response(s) can be written here.
    }
};

class Publisher{ // Publisher Class
    int Parameter; // One or more parameters according to requirement(s)
    vector <Subscriber_Parent*> Subscriber_Array; // Vector container of Subscriber_Parent* (pointer type), pointer instead of actual object class is necessary to extend virtual functions

    public:
    Publisher(){ // Default Constructor
        this-> Parameter = 0;
    }

    void Set_Parameter(int Parameter){ // Setter Method for parameter(s)
        this-> Parameter = Parameter;
    }

    int Get_Parameter(){ // Getter Method for parameter(s)
        return this-> Parameter;
    }

    void Event_Occurance(int &Parameter){ // The Event that will notify the subscriber(s)
        cout << "Event has occurred and checking for subscribers" << endl << endl;
        if(!Subscriber_Array.empty()){ // If SUBSCRIBERS are PRESENT then it will trigger their Event Handlers.
            cout << "Subscribers are present and are now responding" << endl << endl;
            for(int i=0; i<Subscriber_Array.size(); i++){ // An ITERATOR would be nice but I could not get them to work properly for pointer to pointer while accessing elements
                this-> Subscriber_Array[i] -> Event_Handler(this -> Parameter); // Calling the Event Handlers of the subscribers from the Subscriber array of the Publisher.
            }
        }
    }

    void operator+=(Subscriber_Parent *Subscriber){ // Overloaded += operator for Subscribing
        Subscriber_Array.push_back(Subscriber);
    }

    void operator-=(Subscriber_Parent *Subscriber){ // Overloaded -= operator for Unsubscribing
        for(int i=0; i < this->Subscriber_Array.size(); i++){
            if(this->Subscriber_Array[i]->Index == Subscriber->Index){
                this->Subscriber_Array.erase(Subscriber_Array.begin()+i);
            }
        }
    }

    ~Publisher(){ // Destructor
        if(!Subscriber_Array.empty()) Subscriber_Array.clear(); // Cleared the vector array
    }
};

class Subscriber_One : public Subscriber_Parent{ // Subscriber type ONE with independent response.
    void Event_Handler(int &Parameter){ // Subscriber type ONE event response
        cout<< this->Index << " Indexed Subscriber_TYPE_One has responded and successfully received the Parameter = " << Parameter << endl << endl;
    }
    public:
    Subscriber_One(){ // Default constructor that takes Index from Global Scope (::) to mark itself
        this-> Index = ::Index;
        ::Index++;
    }
};

class Subscriber_Two : public Subscriber_Parent{ // Subscriber type TWO with independent response. Any number of subscribers can be added.
    void Event_Handler(int &Parameter){ // Subscriber type ONE event response
        cout<< this->Index << " Indexed Subscriber_TYPE_Two has responded and successfully received the Parameter = " << Parameter << endl << endl;
    }
    public:
    Subscriber_Two(){ // Default constructor that takes Index from Global Scope (::) to mark itself
        this-> Index = ::Index;
        ::Index++;
    }
};

int main(){
    int Parameter = 10;
    Subscriber_Parent *A,*B,*C; // Three different subscribers
    A = new Subscriber_One;
    B = new Subscriber_Two;
    C = new Subscriber_One;
    Publisher Pub; // Creating a new Publisher called Pub
    Pub+=A; // Subscribing A to Pub
    Pub+=B; // Subscribing B to Pub
    Pub+=C; // Subscribing C to Pub
    Pub.Set_Parameter(Parameter); // Setting up publisher Parameter(s).
    Pub.Event_Occurance(Parameter); // Event Occurrence.
    Pub-=B; // Unsubscribing B from Pub
    cout << "A subscription removal has occurred" << endl << endl;
    Pub.Event_Occurance(Parameter); // Reoccurring the event
    cin.ignore();
    return 0;
}
