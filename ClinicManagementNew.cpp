#include <string>
#include <iostream>
using namespace std;
class Prescription;
class Patient{
    protected:
    string name; //atributes
    int ID;
    int age;
    string revisitDate;
    Prescription* prescription;
    public:
    Patient(string n, int id, int a): name(n), ID(id), age(a) {}
    void displayInfo(){ //prints patient's info
        cout << "Patient name: " << name << ", ID: " << ID << ", Age: " << age << endl;
    }
    void scheduleAppointment(){ //basic appointment scheduling
        cout<<"Regular patients can schedule appointments."<<endl;
    }
    string getName() { //retrieves patient's name
         return name;
    }
    void setRevisitDate(string date) { //sets new visit date
        revisitDate=date;
    }
    string getRevisitDate() {
        return revisitDate;
    }
    void setPrescription(Prescription* p){
        prescription = p;
    }
    Prescription* getPrescription() {
        return prescription;
    }
};
class SpecializedPatient : public Patient{
    protected:
    string conditionType; //adds special condition details
    public:
    SpecializedPatient(string n, int id, int a , string ctype): Patient(n, id, a), conditionType(ctype) {
    }
    void displayInfo(){ //displays patient's info including condition
        cout << "Specialized Patient name: " << name << ", ID: " << ID << ", Age: " << age << ", Condition Type: " << conditionType << endl;
    }
    void scheduleAppointment(){ //specialized appointment scheduling
        cout<<"Specialized patients requires check up every x months."<<endl;
    }
};
class Doctor;
class Appointment{
    string date,time,reason,status; //atributes
    Patient* patient;
    Doctor* doctor;
    public:
    Appointment(string d, string t, string r, Patient* p, Doctor* doc): date(d), time(t), reason(r), patient(p), doctor(doc), status("Available") {}
    void displayInfo(); //prints appointment details
    void updateStatus(string newStatus){ //updates appointment status
        status = newStatus;
    }
    double appointmentCost(){ //cost of each appointment
        if(status == "Completed") return 100.0;
        else if(status == "Available")
        return 0.0;
    }
};
class Doctor{
    string name;
    int ID;
    string specialty;
    Appointment* appointments[5];
    int count;
    public:
    Doctor(string n, int id, string spec): name(n), ID(id), specialty(spec), count(0) {}
    void AssignAppointment(Appointment* a){ //links appointment to doctor
        appointments[count++] = a;
    }
    void displayInfo(){ //displays doctor's info
        cout<<"Name: "<<name<<", ID: "<<ID<<", Special Field: "<<specialty<<endl;
        cout<<"Appointments: "<<endl;
        for (int i=0; i<count; i++){
            appointments[i]->displayInfo();
        }
    }
    string getName() {
         return name;
    }
};
void Appointment::displayInfo(){ //prints appointment details
    cout<<"Date: "<<date<<", Time: "<<time<<", Reason: "<<reason<<", Patient: "<<patient->getName()<<", Doctor: "<<doctor->getName()<<", Status: "<<status<<endl;
    cout<<"Cost: "<<appointmentCost()<< " $"<<endl;
    if(status=="Completed"){
    cout<<"Revisit Date: "<<patient->getRevisitDate()<<endl;
    }
}
class Prescription{
    string medication,dosage,instructions;
    public:
    Prescription(string m, string d, string i): medication(m), dosage(d), instructions(i) {}
    void displayInfo(){
        cout<<"Prescription: "<<medication<<", Dosage: "<<dosage<<", Instructions: "<<instructions<<endl;
    }
};
int main(){
    Doctor doctor1("Dr. Slime",420,"Neurology");
    Doctor doctor2("Dr. Pork",1337,"Cardiology");
    Patient patient1("John Roblox",056, 26);
    SpecializedPatient patient2("Jane Minecraft",682, 46,"Obesity");
    patient1.setRevisitDate("15-09-2026");
    patient2.setRevisitDate("09-12-2025");
    patient1.displayInfo();
    patient2.displayInfo();
    patient1.setPrescription(new Prescription("Painkillers", "2 times a day", "After meals"));
    patient2.setPrescription(new Prescription("Weight Loss Pills", "Once a day", "Before breakfast"));
    Appointment a1("08-09-2025", "3:00 PM", "General Checkup", &patient1, &doctor1);
    Appointment a2("09-09-2025", "12:45 PM", "Obesity Checkup", &patient2, &doctor2);
    doctor1.AssignAppointment(&a1);
    doctor2.AssignAppointment(&a2);
    doctor1.displayInfo();
    doctor2.displayInfo();
    a1.updateStatus("Completed");
    a2.updateStatus("Cancelled");
    doctor1.displayInfo();
    patient1.getPrescription()->displayInfo();
    doctor2.displayInfo();
    return 0;
}

